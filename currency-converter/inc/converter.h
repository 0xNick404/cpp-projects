#ifndef _CONVERTER_H
#define _CONVERTER_H

#include <string>
using std::string;

// Function that uses API data to convert amount of TTD to specified currency
void convert_to_currency(string json_str, string currency, double amount);

#endif
