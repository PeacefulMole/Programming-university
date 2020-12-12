#include <iostream>
#include <string>
#include <fstream>

#include "include/nlohmann/json.hpp"
#include "include/cpp_httplib/httplib.h"

using json = nlohmann::json;
using namespace httplib;

void gen_response(const Request& req, Response& res) {
    std::cout << req.body.c_str();
    std::string str = u8R"(
    {
      "response": {
        "text": "Здравствуйте! Это мы, хороводоведы.",
        "tts": "Здравствуйте! Это мы, хоров+одо в+еды.",
        "buttons": [
            {
                "title": "Надпись на кнопке",
                "payload": {},
                "url": "https://example.com/",
                "hide": true
            }
        ],
        "end_session": false
      },
      "version": "1.0"
    })";
    res.set_content(str, "text/json; charset=UTF-8");
}

int main() {
    Server svr;
    svr.Post("/", gen_response);
    std::cout << "Start server... OK\n";
    svr.listen("localhost", 1234);
}
