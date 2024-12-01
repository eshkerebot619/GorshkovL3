#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <istream>
#include <vector>
#include "Pipe.h"
#include "CS.h"
#include "GorshkovLab3.2.h"
#include "GasTransportNetwork.h"



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


void displayMenu() {
    cout << endl << "=== Menu ===" << endl
        << "1. Add pipe" << endl
        << "2. Add CS" << endl
        << "3. View all objects" << endl
        << "4. Edit pipe" << endl
        << "5. Edit CS" << endl
        << "6. Filter Pipe" << endl
        << "7. Filter CS" << endl
        << "8. Delete Pipe" << endl
        << "9. Delete CS" << endl
        << "10. Save" << endl
        << "11. Load" << endl
        << "12. Connect CS with pipe" << endl
        << "13. Display Gas Transport Network" << endl
        << "14. Topological Sort of Network" << endl
        << "0. Exit" << endl;
}


int main() {
    map<int, Pipe> pipes;
    map<int, CS> cs;
    bool flag=true;
    Pipe pipe;
    CS CS;
    GasTransportNetwork network;
    int id = 0;
    int csID = 0;
    int fakeID;
    string fileName;
    ofstream outFile;
    ifstream inFile;
    while (flag) {
        displayMenu();
        int choice = inputWhat("Your choice: ", "Integer");
        switch (choice)
        {
        case 1:
            pipe.addPipe(id, pipes);
            break;
        case 2:
            CS.addCS(csID, cs);
            break;
        case 3:
            pipe.displayPipes(pipes);
            CS.showCS(cs);
            break;
        case 4:
            pipe.displayPipes(pipes);
            fakeID = inputWhat("Enter pipe ID to edit: ", "Integer");
            pipe.editPipe(fakeID, pipes);
            break;
        case 5:
            CS.showCS(cs);
            fakeID = inputWhat("Enter CS ID to edit: ", "Integer");
            CS.editCS(fakeID, cs);
            break;
        case 6:
            pipe.filterPipe(pipes);
            break;
        case 7:
            CS.filterCS(csID, cs);
            break;
        case 8:
            pipe.deletePipe(pipes);
            break;
        case 9:
            CS.deleteCS(cs);
            break;
        case 10:
            cout << "Enter file to save: ";
            getline(cin, fileName);
            outFile.open(fileName);
            pipe.saveToFile(outFile, pipes);
            CS.saveToFile(outFile, cs);
            outFile.close();
            break;
        case 11:
            cout << "Enter file to load: ";
            getline(cin, fileName);
            pipe.loadFromFile(fileName, pipes, id);
            CS.loadFromFile(fileName, cs, csID);
            break;
        case 12: { 
            CS.showCS(cs);
            int inCS = inputWhat("Enter ID of input CS: ", "Integer");
            int outCS = inputWhat("Enter ID of output CS: ", "Integer");
            pipe.displayPipes(pipes);
            int diameter = inputWhat("Enter pipe diameter (500, 700, 1000, 1400): ", "Integer");
            if (cs.count(inCS) && cs.count(outCS)) {
                network.connectStations(inCS, outCS, diameter, pipes, id);
            }
            else {
                cout << "Invalid CS IDs provided.\n";
            }
            break;
        }
        case 13: { 
            network.displayNetwork(cs, pipes);
            break;
        }
        case 14: { 
            vector<int> sorted = network.topologicalSort();
            if (!sorted.empty()) {
                cout << "Topological Order: ";
                for (int id : sorted) {
                    cout << id << " ";
                }
                cout << endl;
            }
            break;
        }
        case 0:
            return 0;
        default:
            cout << "Enter number from 0 to 14" << endl;
            break;
        }
    }
}