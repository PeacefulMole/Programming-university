#include <iostream>
#include <Main/include/cpp_httplib/httplib.h>
#include <Main/include/nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>

using namespace httplib;
using namespace std;
using json = nlohmann::json;

void Replacement(std::string& data, std::string toSearch, std::string replaceStr) {
    size_t pos = data.find(toSearch);
    while (pos != std::string::npos) {
        data.replace(pos, toSearch.size(), replaceStr);
        pos = data.find(toSearch, pos + replaceStr.size());
    }
}

void gen_response(const Request& req, Response& res) {
    setlocale(LC_CTYPE, "rus");
    string CurrentWeather;
    string Picture;
    float Temp;

    Client cli1("http://worldtimeapi.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res1 = cli1.Get("/api/timezone/Europe/Simferopol");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res1) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res1->status == 200) {
            // В res->body лежит string с ответом сервера
        }
        else {
            std::cout << "Status code: " << res1->status << std::endl;
        }
    }
    else {
        auto err = res1.error();
        std::cout << "Error code: " << err << std::endl;
    }
    json j = json::parse(res1->body);
    int CurrentTime = j["unixtime"];
    cout << CurrentTime << "\n";


    Client cli2("http://api.openweathermap.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res2 = cli2.Get("/data/2.5/forecast?id=524901&appid=b1c53fb5c5c8568523e672a58733c718&lat=44.952116&lon=34.102411&exclude=current,minutely,daily,alerts&units=metric&lang=ru");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res2) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res2->status == 200) {
            // В res->body лежит string с ответом сервера
        }
        else {
            std::cout << "Status code: " << res2->status << std::endl;
        }
    }
    else {
        auto err = res2.error();
        std::cout << "Error code: " << err << std::endl;
    }
    json j2 = json::parse(res2->body);



    for (int i = 0; i < 39;) {
        int time = j2["list"][i]["dt"];
        if (CurrentTime == time) {
            CurrentWeather = j2["list"][i]["weather"][0]["description"]; cout << CurrentWeather << "\n";
            Picture = j2["list"][i]["weather"][0]["icon"]; cout << Picture << "\n";
            Temp = j2["list"][i]["main"]["temp"]; cout << Temp << "\n";
            i = 39;
        } i++;

    }
    ostringstream ost1, ost2;
    ost1 << Temp;
    // Команда set_content задаёт ответ сервера и тип ответа:
    // Hello, World! - тело ответа
    // text/plain - MIME тип ответа (в данном случае обычный текст)

    string template_file_name = "/home/edward/Programming/Lab/01/Main/Main/wether.html";
    ifstream file(template_file_name);
    if (!file.is_open()) { cout << "Не удалось открыть файл\n"; }
    else { cout << "Файл открыт!\n"; }
    string str;                 // Буфер. Тут будет текст файла
    getline(file, str, '\0');   // Читаем все пока не встретим символ '\0'

    file.close();

    Replacement(str, "{hourly[i].weather[0].description}", CurrentWeather);

    Replacement(str, "{hourly[i].weather[0].icon}", Picture);

    Replacement(str, "{hourly[i].temp}", std::to_string(int(std::round(Temp))));


        res.set_content(str, "text/html;charset=utf-8");

}




void gen_response_raw(const Request& req, Response& res) {
    string RawTemp;
    float Picture;
    string RawWeather;
    Client cli1("http://worldtimeapi.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res1 = cli1.Get("/api/timezone/Europe/Simferopol");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res1) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res1->status == 200) {
            // В res->body лежит string с ответом сервера
        }
        else {
            std::cout << "Status code: " << res1->status << std::endl;
        }
    }
    else {
        auto err = res1.error();
        std::cout << "Error code: " << err << std::endl;
    }
    json j = json::parse(res1->body);
    int CurrentTime = j["unixtime"];


    Client cli2("http://api.openweathermap.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res2 = cli2.Get("/data/2.5/forecast?id=524901&appid=b1c53fb5c5c8568523e672a58733c718&lat=44.952116&lon=34.102411&exclude=current,minutely,daily,alerts&units=metric&lang=ru");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res2) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res2->status == 200) {
            // В res->body лежит string с ответом сервера
        }
        else {
            std::cout << "Status code: " << res2->status << std::endl;
        }
    }
    else {
        auto err = res2.error();
        std::cout << "Error code: " << err << std::endl;
    }
    json j2 = json::parse(res2->body);
    json out;
    for (int i = 0; i < 39;) {
        int time = j2["list"][i]["dt"];
        if (CurrentTime = time) {
            out["weather"] = j2["list"][i]["weather"][0]["description"];
            out["temp"] = j2["list"][i]["main"]["temp"];
            i = 39;
        } i++;
    }
         res.set_content(out.dump(), "text/json;charset=utf-8");

    }


int main() {
    Server svr;                    // Создаём сервер (пока-что не запущен)
    svr.Get("/", gen_response); // Вызвать функцию gen_response если кто-то обратиться к корню "сайта"
    svr.Get("/raw", gen_response_raw);// Вызвать функцию gen_response_raw если кто-то обратиться к сырому кэшу сайта
    std::cout << "Start server... OK\n";
    svr.listen("localhost", 3000);
}
