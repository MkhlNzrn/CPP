#include "JsonStat.h"

void JsonStat::parse(nlohmann::json &json) {
	for (auto & valute : json["Valute"]) {
		string key = valute["CharCode"];
		double value = valute["Value"];
		medians[key].push_back(value);
		middles[key] += value;
	}
	counter++;
}

void JsonStat::getStat(nlohmann::json &json) {
	for (auto & valute : json["Valute"]) {
		string key = valute["CharCode"];
		int nominal = valute["Nominal"];
		std::cout << key << " | " << nominal << " | " <<
			middles[key] / (double)counter << " | " << getMedian(key) << endl;
	}
}

double JsonStat::getMedian(string &key) {
	double res = 0;
	if (medians[key].size() % 2 == 0) {
		auto m1 = medians[key].begin() + medians[key].size() / 2;
		auto m2 = medians[key].begin() + medians[key].size() / 2 - 1;
		res = (*m1 + *m2) / 2;
	}
	else {
		auto m = medians[key].begin() + medians[key].size() / 2;
		nth_element(medians[key].begin(), m, medians[key].end());
		res = *m;
	}
	return res;
}

void JsonStat::printData(nlohmann::json &json) {
	for (auto & valute : json["Valute"]) {
		cout << valute["CharCode"] << " | " <<
			valute["Nominal"] << " | " << valute["Value"] << endl;
	}
}
