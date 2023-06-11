#define CURL_STATICLIB
#include <iostream>
#include <sstream>
#include "JsonStat.h"
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <vector>
#include <C:\Users\Sandra\Desktop\Curl + Json\json-develop\single_include\nlohmann\json.hpp>
#include "windows.h"
#include <conio.h>


using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

int main() {
	CURL * curl;

	// код ошибки
	CURLcode curlCode;
	string buffer;
	nlohmann::json json;

	curl = curl_easy_init();

	// настраиваем curl
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE); //todo мб и без этого работает
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

	JsonStat jsonStat;
	string a = "";
	string b = "";
	int timer = 0;
	while (true) {
		cin >> a;
		//timer++;
		if (curl) {

			buffer = "";

			// получаем код ошибки и делам запрос
			curlCode = curl_easy_perform(curl);

			// кидаем эксепшн, если код ошибки != коду ошибки, когда все ок
			if (curlCode != CURLE_OK) {
				throw logic_error("Curl curl_easy_perform failed\n");
			}

			json = nlohmann::json::parse(buffer);

			if (json.find("Valute") == json.end()) {
				throw logic_error("Invalid json\n");
			}
			else {
				jsonStat.parse(json);
				jsonStat.printData(json);
				cout << endl;
			}
			Sleep(10000);
			// todo timer

		}
		if (_kbhit()) exit(0);
	}
	jsonStat.getStat(json); //Вывод мидов и медиан
}


