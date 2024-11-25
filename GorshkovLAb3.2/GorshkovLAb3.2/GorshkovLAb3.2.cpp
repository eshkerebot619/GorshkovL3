#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <istream>
#include <vector>
#include "Pipe.h"



using namespace std;

double inputWhat(const string& prompt, const string& sto) {
    string input;
    int value;
    size_t processed_chars;
    while (true) {
        std::cout << prompt;
        getline(cin, input);
        if (sto == "Repair") {
            if (input == "Y" || input == "y") {
                return true;
            }
            else if (input == "N" || input == "n") {
                return false;
            }
            else {
                std::cout << "Enter Y/N" << endl;
            }
        }
        else {
            try {
                if (sto == "Integer") {
                    value = stoi(input, &processed_chars);
                }
                else if (sto == "Double") {
                    value = stod(input, &processed_chars);
                }
                if (processed_chars == input.length() && value >= 0) {
                    return value;
                }
                else {
                    std::cout << "Enter correct number!" << endl;
                }
            }
            catch (...) {
                std::cout << "Enter correct number!" << endl;
            }
        }
    }
}



int main()
{
    
}
