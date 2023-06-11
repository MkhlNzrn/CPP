#pragma once

#include "C:\Users\Sandra\Desktop\Curl + Json\json-develop\single_include\nlohmann\json.hpp"

#include <vector>

#include <unordered_map>

#include <iostream>

using namespace std;

class JsonStat {
private:
	unsigned int counter = 0;
	unordered_map<string, vector<double>> medians;
	unordered_map<string, double> middles;

	double getMedian(string &key);

public:
	JsonStat() = default;
	JsonStat(JsonStat &other) = default;
	~JsonStat() = default;

	void printData(nlohmann::json &json);
	void parse(nlohmann::json &json);
	void getStat(nlohmann::json &json);

};

