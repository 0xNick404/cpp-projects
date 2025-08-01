#include <iostream>
#include <string>
#include <algorithm>
#include <set>

#include "api_client.h"
#include "converter.h"

using namespace std;

int main(){
    //Set of supported currency codes
    set<string> supported_currencies = {"cad", "bsd", "bbd", "eur", "gbp", "gyd", "jmd", "usd"};

    cout << "Base Currency is the Trinidad and Tobago dollar (ttd)\n" << endl;

    // Output of supported currencies with their name and respective currency codes
    cout << "Supported Currencies:\n";
    cout << "Canadian dollar (cad)\n" 
         << "Bahamian dollar (bsd)\n" 
         << "Barbadian dollar (bbd)\n" 
         << "Euro (eur)\n" 
         << "Pound sterling (gbp)\n" 
         << "Guyanese dollar (gyd)\n" 
         << "Jamaican dollar (jmd)\n" 
         << "United States dollar (usd)\n" 
         << endl;

    string currency;
    double amount;

    while(true){
        cout << "Enter target currency (e.g., usd, eur, gbp): ";
        cin >> currency;

        //Transform input to lowercase to compare with set
        transform(currency.begin(), currency.end(), currency.begin(), ::tolower);

        //Compares inputted currency code with supported currency codes in set
        if(supported_currencies.find(currency) != supported_currencies.end()){
            break;
        }
        else{
            cout << "Invalid currency entered. Please enter one from the supported list.\n";
        }

    }

    while(true){
        cout << "Enter amount to convert in ttd: ";
        cin >> amount;

        //Validates input is not a negative number
        if(amount > 0){
            break;
        }
        else{
            cout << "Invalid amount entered. Please enter a positive number only.\n";
        }
    }

    //Function call for latest conversion data
    string currency_data = fetch_currency_data();

    //Function call to convert inputted amount in TTD to the inputted currency
    convert_to_currency(currency_data, currency, amount);

    return 0;
}