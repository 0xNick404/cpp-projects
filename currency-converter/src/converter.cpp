#include <iostream>
#include <string>

#include "converter.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void convert_to_currency(std::string json_str, std::string currency, double amount){
    json parsed = json::parse(json_str);

    double rate = parsed["ttd"][currency];
    double result = rate * amount;

    std::cout << amount << " ttd = " << result << " " << currency << std::endl;
}

// References:
// https://github.com/nlohmann/json – Used for JSON parsing (nlohmann/json library)
