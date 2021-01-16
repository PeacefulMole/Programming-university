#include <iostream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <exception>

using namespace std;
// в свойствах проекта во вкладке c++/язык нужно поменять стандарт на iso c++ 17 ч
namespace fs = filesystem;
using namespace httplib;
using json = nlohmann::json;

void Replacement(string& data, const string toSearch, const string replaceStr) {//...ФУНКЦИЯ ПЕРЕСТАНОВКИ...
    size_t pos = data.find(toSearch);
    while (pos != string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}
json config;
string ConfigFile = "config.json";
const string WebpageFile = "Hookslist.html";
string webhook_template = R"(
<div class="form-row align-items-center">
    <div class="col">
        <input type="text" value="{Webhook URL}" class="form-control mb-2" disabled>
    </div>
    <div class="col">
        <button type="submit" name="del" value="{Webhook URL}" class="btn btn-danger mb-2">Удалить</button>
    </div>
</div>)";
json GetConfig()//... СОЗДАНИЕ ЛИБО НАХОЖДЕНИЕ КОНФИГ ФАЙЛА...
{
	ifstream config_file(ConfigFile);
	json config;
	if (config_file.is_open())
	{
		cout << "Идет разбитование json.\n";

		config_file >> config;

		cout << "...УСПЕШНО...\n";
		config_file.close();
	}
	else
	{
		fs::path config_path{ ConfigFile };
		if (fs::exists(config_path))
		{
			cout << "...ERROR...\n Файл " << fs::absolute(config_path) << " не удается открыть.\n "
				<< "Проверьте права доступа к этому файлу.\n";
		}
		else
		{
			cout << "...ERROR...\n Файл " << fs::absolute(config_path) << " не существует.\n";
		}
		json return_json;
		return_json["webhooks"] = json::array();
		return return_json;
	}
	return config;
}
void SaveConfig(json config)// ...СОХРАНЕНИЕ КОНФИГ ФАЙЛА...
{
	fs::path config_path{ ConfigFile };
	if (!fs::exists(config_path))
	{
		cout << "Нет файла " << fs::absolute(config_path) << " Создание нового\n";
	}

	ofstream config_file(ConfigFile);
	if (config_file.is_open())
	{
		cout << "Заполнение конфигураций\n";
		config_file << config.dump(4);
		config_file.close();
	}
	else
	{
		cout << "Не удалось создать файл по пути\n " << fs::absolute(config_path) << "!";
	}
}

void gen_responce_weblist(const Request& req, Response& res) {
	ifstream webpage_file(WebpageFile);
	string webpage;
	if (webpage_file.is_open())
	{
		getline(webpage_file, webpage, '\0');
		webpage_file.close();
	}
	else
	{
		fs::path config_path{ WebpageFile };
		if (exists(config_path))
		{
			cout << "...ERROR...\n Файл " << fs::absolute(config_path) << "не удалось открыть. ";
		}
		else
		{
			cout << "...ERROR...\n Файл " << fs::absolute(config_path) << " не существует.\n";
		}
	}
	if (config.empty())
	{
		config = GetConfig();
	}
	string webhook_list;
	if (!config["webhooks"].empty())
	{
		for (auto webhook : config["webhooks"])
		{
			if (webhook.is_string())
			{
				string templ = webhook_template;
				Replacement(templ, "{Webhook URL}", webhook.get<std::string>());
				webhook_list += templ;
			}
			else
			{
				cout << "...ERROR...\n Проверьте конфигурационный файл. "
					<< "Был обнаружен " << webhook << " с неверным типом данных '" << webhook.type_name()
					<< "'. Ожидалась строка." << std::endl;
			}
		}
	}
	Replacement(webpage, "{webhooks_list}", webhook_list);
	res.set_content(webpage, "text/html;charset=utf-8");

}


string gen_webhook_page()//ФУНКЦИЯ ДЛЯ СТРАНИЦЫ С ВЭБХУКАМИ
{
	ifstream webpage_file(WebpageFile);
	string webpage;
	if (webpage_file.is_open())
	{
		getline(webpage_file, webpage, '\0');
		webpage_file.close();
	}
	else
	{
		fs::path config_path{ WebpageFile };
		if (fs::exists(config_path))
		{
			cout << "...ERROR...\n Файл " << fs::absolute(config_path) << " не удается открыть.\n ";
		}
		else
		{
			cout << "...ERROR...\n Файла " << fs::absolute(config_path) << " не существует.\n";
		}
		return "";
	}
	if (config.empty())
	{
		config = GetConfig();
	}
	string webhook_list;
	if (!config["webhooks"].empty())
	{
		for (auto webhook : config["webhooks"])
		{
			if (webhook.is_string())
			{
				string templ = webhook_template;
				Replacement(templ, "{Webhook URL}", webhook.get<string>());
				webhook_list += templ;
			}
			else
			{
				cout << "Проверьте конфигурационный файл. "
					<< "Был обнаружен " << webhook << " с типом неверным данных '" << webhook.type_name()
					<< "'. А ожидалась строка.\n" ;
			}
		}
	}
	Replacement(webpage, "{webhooks_list}", webhook_list);
	return webpage;
}

void GetWebhook(const Request& req, Response& res)//...ФУНКЦИЯ GET ЗАПРОСОВ...
{
	res.set_content(gen_webhook_page(), "text/html; charset=UTF-8");
	cout << "\n";
}
void PostWebhook(const Request& req, Response& res)//... ФУНККЦИЯ POST ЗАПРОСОВ...
{
	if (config.empty())
	{
		config = GetConfig();
	}
	if (req.has_param("del"))
	{
		string value = req.get_param_value("del");
		if (value == "")
		{
			cout << "Запрос на удаление пуст\n";
		}
		else
		{
			cout << "получен post параметр del:" << value << "\n";

			if (!config["webhooks"].empty())
			{
				for (auto ptr = config["webhooks"].begin();
					ptr != config["webhooks"].end();
					++ptr)
				{
					if (ptr->is_string() and ptr->get<string>() == value)
					{
						cout << "...ВЕБХУК " << ptr->get<string>()
							<< " УДАЛЕН...\n";
						config["webhooks"].erase(ptr);
						break;
					}
				}
			}
			else
			{
				cout << "Что удалять? тут же ничего нету\n" ;
			}
		}
	}
	else if (req.has_param("set"))
	{
		string value = req.get_param_value("set");
		if (value == "")
		{
			cout << "Вы ничего не ввели, попробуйте использовать клавиатуру\n";
		}
		else
		{
			cout << "Получен параметр set:" << value << "\n";

			if (!config["webhooks"].empty())
			{
				bool webhook_exist = false;
				for (auto ptr = config["webhooks"].begin();
					ptr != config["webhooks"].end();
					++ptr)
				{
					if (ptr->is_string() && ptr->get<string>() == value)
					{
						cout << "Такой вэбхук уже есть, выберите другое имя\n";
						webhook_exist = true;
						break;
					}
				}
				if (!webhook_exist) {
					cout << "...НОВЫЙ ВЭБХУК...\n " << value << ".\n";
					config["webhooks"].push_back(value);
				}
			}
			else
			{
				cout << "...НОВЫЙ ВЭБХУК...\n " << value << ".\n" ;
				config["webhooks"].push_back(value);
			}
		}
	}
	SaveConfig(config);

	res.set_content(gen_webhook_page(), "text/html; charset=UTF-8");
	cout << "\n";
}

enum voice_mode
{
	silent_mode,
	speak_mode
};

enum skill_mode
{
	default_mode,
	help_mode
};

json session_list = json::array();
json default_state_buttons =
{
	{
		{"title", "Помощь"},
		{"hide", true}
	},
};

json speak_mode_button =
{
	{"title", "Говорить"},
	{"hide", true}
};

json silent_mode_button =
{
	{"title", "Молчать"},
	{"hide", true}
};

json help_state_buttons =
{
	{
		{"title", "Молчать"},
		{"hide", true}
	},
	{
		{"title", "Говорить"},
		{"hide", true}
	},
	{
		{"title", "Помощь"},
		{"hide", true}
	},
	{
		{"title", "Корзина"},
		{"hide", true}
	},
	{
		{"title", "Выйти из помощи"},
		{"hide", true}
	},
	{
		{"title", "Покупка завершена"},
		{"hide", true}
	},
};

json GetConfig();

json gen_response(const string& text,
	const string& tts,
	const json& buttons,
	const json* current_session = nullptr,
	const bool end_session = false)
{
	cout << "...ОТВЕТ ОТПРАВЛЯЕТСЯ...\n";
	json response = {
		{"response", {
			{"buttons", buttons},
			{"end_session", end_session}
		}},
		{"version", "1.0"}
	};
	if (text != "")
	{
		cout << "строка не пуста";
		response["response"]["text"] = text;
	}
	if (current_session != nullptr && (*current_session)["voice_mode"] == speak_mode)
	{
		cout << "режим разговора";
		if (tts != "")
		{
			response["response"]["tts"] = tts;
		}
		response["response"]["buttons"].push_back(silent_mode_button);
	}
	else if (current_session != nullptr && (*current_session)["voice_mode"] == silent_mode)
	{
		response["response"]["buttons"].push_back(speak_mode_button);
		response["response"]["tts"] = "sil <[500]>";
		cout << "режим текста";
	}
	try {
		string bruh = response.dump();
		cout << "Рандомная строка";
		cout << bruh;
	}
	catch (exception& e) { cout << e.what(); }
	
	return response;
	
}
void AliceSkill(const Request& req, Response& res)
{
	cout << "...СКИЛЛ ЗАПУЩЕН...\n";
	json req_json = json::parse(req.body);

	string user_id = req_json["session"]["application"]["application_id"];
	cout << user_id << "\n";
	json response;
	json* cur_session = nullptr;

	for (auto& session : session_list)
	{
		if (session["user_id"] == user_id)
		{
			cur_session = &session;
			cout << "...СЕССИЯ ВОЗОБНОВЛЕНА...\n";
			break;
		}
	}

	if (req_json["session"]["new"].get<bool>())
	{
		if (cur_session == nullptr)
		{
			json session =
			{
				{"user_id", user_id},
				{"skill_mode", default_mode},
				{"voice_mode", silent_mode},
				{"cart", json::array()}
			};
			session_list.push_back(session);
			cur_session = &session_list[session_list.size() - 1];
			cout << "...СЕССИЯ СОЗДАНА...\n";
		}
		
		else
		{
			(*cur_session)["skill_mode"] = default_mode;
			(*cur_session)["voice_mode"] = silent_mode;
		}

		json response = gen_response(
			"Здравствуйте! Я помогу вам с покупками.",
			"Здр+авствуйте! Я помог+у вам с пок+упками.",
			default_state_buttons,
			cur_session);

		res.set_content(response.dump(2), "text/json; charset=UTF-8");
		return;
	}

	if (cur_session == nullptr)
	{
		json response = gen_response(
			"Извините, произошла ошибка",
			"Извин+ите, произошл+а ош+ибка",
			default_state_buttons,
			cur_session,
			true);
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
		return;
	}

	string command = req_json["request"]["command"];
	if ((*cur_session)["skill_mode"] == help_mode)
	{
		// молчать, говорить, помощь, корзина, выйти из помощи, покупка завершена, сумма
		// О чём ещё рассказать?
		string text;
		string tts;

		if (command == "молчать")
		{
			text = "Скажите мне эту фразу и я не буду озвучивать свои сообщения.";
			tts = "Скажите мне эту фразу и я не буду озвучивать свои сообщения.";
		}
		else if (command == "говорить")
		{
			text = "Скажите мне говорить и я буду озвучивать все свои реплики";
			tts = "Скажите мне говорить и я буду озвучивать все свои реплики";
		}
		else if (command == "помощь")
		{
			text = "Это то, где вы сейчас находитесь. "
				"В этом режиме я расскажу вам подробно о своих возможностях.";
			tts = "Это то, где вы сейчас находитесь. "
				"В этом режиме я расскажу вам подробно о своих возможностях.";
		}
		else if (command == "корзина")
		{
			text = "Я запомню, что вы будете добавлять или удалять из корзины.\n"
				"Чтобы добавить что-то, скажите \"Добавить в корзину сыр 5 рублей\".\n"
				"Чтобы удалить что-то, скажите \"Удалить из корзины сыр\".";
			tts = "Я запомню, что вы будете добавлять или удалять из корзины.\n"
				"Чтобы добавить что-то, скажите \"Добавить в корзину сыр 5 рублей\".\n"
				"Чтобы удалить что-то, скажите \"Удалить из корзины сыр\".";
		}
		else if (command == "сумма")
		{
			text = "Я подсчитаю стоимость всех товаров в вашей корзине и назову их общую стоимость.";
			tts = "Я подсчитаю стоимость всех товаров в вашей корзине и назову их общую стоимость.";
		}
		else if (command == "покупка завершена")
		{
			text = "Я передам список ваших покупок веб-хукам, после чего очищу корзину.";
			tts = "Я передам список ваших покупок веб-хукам, после чего очищу корзину.";
		}
		else if (command == "выйти из помощи")
		{
			text = "Выхожу. Нужна будет помощь - обращайтесь.";
			tts = "Выхожу. Нужна будет помощь - обращайтесь.";
			(*cur_session)["skill_mode"] = default_mode;
		}
		else
		{
			text = "С этим я не могу вам помочь.";
			tts = "С +этим я не мог+у вам пом+очь.";
		}

		json response;
		if ((*cur_session)["skill_mode"] == help_mode)
		{
			response = gen_response(text, tts, help_state_buttons, cur_session);
		}
		else
		{
			response = gen_response(text, tts, default_state_buttons, cur_session);
		}
		res.set_content(response.dump(2), "text/json; charset=UTF-8");
	}
	else
	{
		if (command == "молчать")
		{
			string text = "Молчу, молчу";
			string tts;
			(*cur_session)["voice_mode"] = silent_mode;
			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == "говорить")
		{
			string text = "Хорошо.";
			string tts = "Хорош+о.";
			(*cur_session)["voice_mode"] = speak_mode;
			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == "помощь")
		{
			string text =
				"Говорить или молчать. Включает и выключает голосовой режим.\n"
				"Корзина. Позволяет вести список покупок, а так же их совершать.\n"
				"Помощь. Рассказывает о возможностях этого навыка.\n"
				"Совершить покупку. Очищает корзину и сохраняет данные в формате эксель.\n"
				"Сумма. Считает сумму товаров и называет её вам.\n"
				"О чём рассказать подробнее?";
			string tts =
				"Говорить или молчать. Включает и выключает голосовой режим.\n"
				"Корзина. Позволяет вести список покупок, а так же их совершать.\n"
				"Помощь. Рассказывает о возможностях этого навыка.\n"
				"Совершить покупку. Очищает корзину и сохраняет данные в формате эксель.\n"
				"Сумма. Считает сумму товаров и называет её вам.\n"
				"О чём рассказать подробнее?";
			json response = gen_response(
				text,
				tts,
				help_state_buttons,
				cur_session);
			(*cur_session)["skill_mode"] = help_mode;
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == "очистить корзину")
		{
			string text = "Корзина пуста.";
			string tts = "Кориз+ина пуст+а.";
			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);
			(*cur_session).erase("cart");
			(*cur_session)["cart"] = json::array();
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == "что в корзине")
		{
			cout << "cart: " << (*cur_session)["cart"];

			string text;
			string tts;

			if ((*cur_session)["cart"].empty())
			{
				text = "На данный момент ваша корзина пуста.";
				tts = "На данный момент ваша корзина пуста.";
			}
			else
			{
				text = "На данный момент в вашей корзине:";
				for (auto& elem : (*cur_session)["cart"])
				{
					int price = elem["price"].get<int>();

					text += "\n"
						+ elem["item"].get<string>()
						+ " ценой "
						+ to_string(price);

					if (price % 10 == 0)
					{
						text += " рублей,";
					}
					else if (price % 10 == 1)
					{
						text += " рубль,";
					}
					else if (price % 10 < 5 && price % 10 > 0)
					{
						text += " рубля,";
					}
					else
					{
						text += " рублей,";
					}
				}
				text.pop_back();
				tts = text;
			}

			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == "покупка завершена")
		{
			string text = "Заходите ещё!";
			string tts = "Заход+ите ещ+ё!";

			json output =
			{
				{"user_id", user_id},
				{"cart", (*cur_session)["cart"]}
			};

			json config = GetConfig(); // webhooks.cpp

			for (string link : config["webhooks"])
			{
				// Либа не работает с https ссылками.
				Replacement(link, "https://", "http://");

				// Если передали линк без '/' на конце, добавляем его
				if (link.find("http://") != 0)
				{
					cout << "bad link";
					continue;
				}


				// http://
				// 1234567
				const int http_protocol_size = 7;

				// найти первую / после объявления протокола и "//"

				int index = link.find('/', http_protocol_size);
				if (index == string::npos)
				{
					link.push_back('/');
					index = link.length() - 1;
				}

				cout << "test: " << link.substr(0, index);
				cout << "2nd : " << link.substr(index, string::npos).c_str();

				Client cli(link.substr(0, index).c_str());
				cli.Post(link.substr(index, string::npos).c_str(), output.dump(2), "application/json; charset=UTF-8");
			}

			(*cur_session).erase("cart");
			(*cur_session)["cart"] = json::array();

			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session,
				true);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command == "сумма")
		{
			string text = "";
		    string tts = "";

			size_t size = req_json["request"]["nlu"]["tokens"].size();
			int sum = 0;
			for (auto& cart_item : (*cur_session)["cart"])
			{
				sum += cart_item["price"].get<int>();
			}
			if (sum == 0)
			{
				text = "У вас в корзине нет товаров.";
				tts = "У вас в корз+ине нет тов+аров.";
			}
			else
			{
				text = "В общей сумме у вас товаров на " + to_string(sum);
				tts = "В +общей с+умме у вас тов+аров на " + to_string(sum);
				if (sum % 10 == 0)
				{
					text += " рублей.";
					tts += " рубл+ей.";
				}
				else if (sum % 10 == 1)
				{
					text += " рубль.";
					tts += " рубль.";
				}
				else if (sum % 10 < 5 && sum % 10 > 0)
				{
					text += " рубля.";
					tts += " рубл+я.";
				}
				else
				{
					text += " рублей.";
					tts += " рубл+ей.";
				}
			}

			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find("добавить в корзину") == 0 || command.find("добавь в корзину") == 0)
		{
			size_t size = req_json["request"]["nlu"]["tokens"].size();
			string text = "ОК.";
			string tts = "Ок+ей.";
			string item_name;
			int			item_price = 0;
			int			number_index = 0;
			bool			number_index_set = false;

			for (auto entity : req_json["request"]["nlu"]["entities"])
			{
				if (entity["type"].get<string>() == "YANDEX.NUMBER")
				{
					number_index = entity["tokens"]["start"];
					cout << entity["value"].type_name();
					//if (entity["value"].type() == json::value_t::number_integer)
					//{
					int val = entity["value"];
					cout << "Инфо: цена " << val;
					if (val < 0)
					{
						text = "Цена не может быть отрицательной.";
						tts = "Цен+а не м+ожет б+ыть отриц+ательной.";
					}
					else if (val == 0)
					{
						text = "Ну кто же вам продаст что-то за бесплатно?";
						tts = "Ну кто же вам прод+аст чт+о то за беспл+атно?";
					}
					else
					{
						item_price = val;
					}
					//}
					number_index_set = true;
					break;
				}
			}
			if (size == 3)
			{
				text = "Пожалуйста, расскажите, что добавить в корзину.";
				tts = "Пож+алуйста, расскаж+ите, что доб+авить в корз+ину.";
			}
			else if (!number_index_set)
			{
				text = "Пожалуйста, укажите цену товару.";
				tts = "Пож+алуйста, укаж+ите ц+ену тов+ару.";
			}
			else if (number_index == 3)
			{
				text = "Покажуйста, укажите название товара.";
				tts = "Пож+алуйста, укаж+ите назв+ание тов+ара.";
			}
			else
			{
				for (int i = 3; i < number_index; ++i)
				{
					item_name += req_json["request"]["nlu"]["tokens"][i].get<std::string>();
					item_name += " ";
				}
				item_name.pop_back();
				json item = {
					{"item",  item_name},
					{"price", item_price}
				};
				(*cur_session)["cart"].push_back(item);
			}

			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);

			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else if (command.find("удалить из корзины") == 0 || command.find("удали из корзины") == 0
			|| command.find("убрать из корзины") == 0 || command.find("убери из корзины") == 0)
		{
			cout << (*cur_session)["cart"];
			size_t size = req_json["request"]["nlu"]["tokens"].size();

			string text;
			string tts;
			string item_name = "";

			for (int i = 3; i < size; ++i)
			{
				cout << req_json["request"]["nlu"]["tokens"][i].get<string>();
				item_name += req_json["request"]["nlu"]["tokens"][i].get<string>();
				item_name += " ";
			}
			bool found_item = false;
			int	item_index = 0;

			if (item_name == "")
			{
				text = "Ну вы хоть скажите, что собираетесь убирать.";
				tts = "Ну вы хоть скаж+ите, что собир+аетесь убир+ать.";
			}
			else
			{
				item_name.pop_back();
				for (auto& cart_item : (*cur_session)["cart"])
				{
					if (cart_item["item"].get<string>() == item_name)
					{
						found_item = true;
						break;
					}
					++item_index;
				}
				if (!found_item)
				{
					cout << "Инфо: такой предмет не был найден";
					text = "Такого в вашей корзине нету";
					tts = "Так+ого в в+ашей корз+ине н+ету.";
				}
				else
				{
					cout << "Инфо: Нашли такой предмет";
					text = "Удалила.";
					tts = "Удал+ила";
					(*cur_session)["cart"].erase((*cur_session)["cart"].begin() + item_index);
					cout << "Инфо: Удалили предмет";
				}
			}
			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);
			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
		else
		{
			string text = "Я не знаю такую команду.";
			string tts = "Я не зн+аю так+ую ком+анду.";

			json response = gen_response(
				text,
				tts,
				default_state_buttons,
				cur_session);

			res.set_content(response.dump(2), "text/json; charset=UTF-8");
		}
	}

	// Сохранить сессии в файл

	cout;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	setlocale(LC_CTYPE, "rus");
	Server srv;

	srv.Get("/webhooks", GetWebhook);
	srv.Post("/webhooks", PostWebhook);

	// Яндекс будет посылать периодические запросы, а так же запросы при изменении состояния чатов.
	srv.Post("/alice", AliceSkill);

	cout << "...СЕРВЕР ЗАПУЩЕН...\n"
		<< "Адрес: localhost:1234\n"
		<< "Управление вэбхуками по адресу: localhost:1234/webhooks\n"
		<< "Алиса будет работать по адресу: localhost:1234/alice.\n";

	srv.listen("localhost", 1234);
}