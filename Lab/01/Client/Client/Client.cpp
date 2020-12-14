#include <iostream>
#include <cpp_httplib/httplib.h>
using namespace httplib;

int main() {
    // Создаём клиент и привязываем к домену. Туда пойдут наши запросы
    Client cli("http://worldtimeapi.org");
    // Отправляем get-запрос и ждём ответ, который сохраняется в переменной res
    auto res = cli.Get("/api/timezone/Europe/Simferopol");
    // res преобразуется в true, если запрос-ответ прошли без ошибок
    if (res) {
        // Проверяем статус ответа, т.к. может быть 404 и другие
        if (res->status == 200) {
            // В res->body лежит string с ответом сервера
            std::cout << res->body << std::endl;
        }
        else {
            std::cout << "Status code: " << res->status << std::endl;
        }
    }
    else {
        auto err = res.error();
        std::cout << "Error code: " << err << std::endl;
    }//Повторяем тоже самое только уже с погодой и другими переменными
    Client cli2("http://api.openweathermap.org");
    auto res2 = cli2.Get("/data/2.5/forecast?id=524901&appid=3d39302576a79c67051688878116f7c4&lat=44.952116&lon=34.102411&exclude=current,minutely,daily,alerts&units=metric");

    if (res2) {
       
        if (res2->status == 200) {
          
            std::cout << res2->body << std::endl;
        }
        else {
            std::cout << "Status code: " << res2->status << std::endl;
        }
    }
    else {
        auto err2 = res.error();
        std::cout << "Error code: " << err2 << std::endl;
    }
}
