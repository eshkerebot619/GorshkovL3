#include "Pipe.h"
#include "GorshkovLab3.2.h"


using namespace std;

Pipe::Pipe()
{
    name = "Arthur";
    length = 100;
    diameter = 200;
    inRepair = true;
}

Pipe::Pipe(string n, int l, int d, bool r)
{
    name = n;
    length = l;
    diameter = d;
    inRepair = r;
}

void Pipe::addPipe(int& id, map<int, Pipe>& pipes)
{
    ++id;
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    length = inputWhat("Enter length: ", "Double");
    diameter = inputWhat("Enter diameter: ", "Double");
    inRepair = inputWhat("Is the pipe being repaired? (Y/N):  ", "Repair");
    
    pipes[id] = { name, length, diameter, inRepair };
}

void Pipe::displayPipes(map<int, Pipe> pipes) const
{
    for (const auto& pipe : pipes) {
        cout << "Pipe ID: " << pipe.first << pipe.second;
    }
}

void Pipe::deletePipe(map<int, Pipe>& pipes)
{
    displayPipes(pipes);
    int delID = inputWhat("Enter ID: ", "Integer");
    if (pipes.erase(delID)) {
        cout << "Pipe with ID " << delID << " has been deleted" << endl;
    }
    else {
        cout << "Pipe with ID " << delID << " not found." << endl;
    }
}

void Pipe::editPipe(int& id, map<int, Pipe>& pipes)
{
    if (pipes.find(id) != pipes.end()) {
        pipes[id].inRepair = !pipes[id].inRepair;
        cout << "Pipe with ID: " << id << " has been updated" << endl;
    }
    else {
        cout << "Pipe with ID: " << id << " not found" << endl;
    }
}

void Pipe::filterPipe(map<int, Pipe>& pipes)
{
    if (pipes.empty()) {
        cout << "No pipes available.\n";
        return;
    }
    displayPipes(pipes);
    vector<int> filtered;
    string filterName;
    bool filterByName = inputWhat("Filter by name? (Y/N): ", "Repair");

    if (filterByName) {
        cout << "Enter name to filter by: ";
        getline(cin, filterName);

        for (const auto& pipe: pipes) {
            if (pipe.second.name.find(filterName) != string::npos) {
                cout << "ID: " << pipe.first << pipe.second;
                filtered.push_back(pipe.first);
            }
        }
    }
    else {
        bool filterRepair = inputWhat("Repair status (Y/N): ", "Repair");

        for (const auto& pipe : pipes) {
            if (pipe.second.inRepair == filterRepair) {
                cout << "ID: " << pipe.first << pipe.second;
                filtered.push_back(pipe.first);
            }
        }
    }

    // Выбор редактирования после фильтрации
    string choice;
    cout << "Edit all (A), specific by ID (S), or cancel (N)? (A/S/N): ";
    getline(cin, choice);
    if (choice == "A" || choice == "a") {
        bool newInRepair = inputWhat("Set repair status (Y/N): ", "Repair");
        for (const auto& i : filtered) {
            pipes[i].inRepair = newInRepair; // Обновление статуса для всех
        }
        cout << "All found pipes have been updated.\n";
    }
    else if (choice == "S" || choice == "s") {
        int pipeID = inputWhat("Enter pipe ID to edit: ", "Integer");
        editPipe(pipeID, pipes); // Редактирование конкретной трубы
    }
    else if (choice == "N" || choice == "n") {
        cout << "No changes made.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void Pipe::saveToFile(ofstream& outFile, map<int, Pipe>& pipes)
{
    if (!pipes.empty()) {
        for (auto& pipe : pipes) {
            outFile << "Pipe ID: " << pipe.first << pipe.second;
        }
    }
}

void Pipe::loadFromFile(string& filename, map<int, Pipe>& pipes, int& id)
{
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: Unable to open file for loading" << endl;
        return;
    }

    string line;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        if (line.find("Pipe ID:") != string::npos) {
            size_t idPos = line.find("Pipe ID:") + 9;
            size_t namePos = line.find("Pipe Name:") + 11;
            size_t lengthPos = line.find("Length:") + 8;
            size_t diameterPos = line.find("Diameter:") + 10;
            size_t repairPos = line.find("In Repair:") + 11;

            id = stoi(line.substr(idPos, line.find(",", idPos) - idPos));
            name = line.substr(namePos, line.find(",", namePos) - namePos);
            length = stoi(line.substr(lengthPos, line.find(",", lengthPos) - lengthPos));
            diameter = stoi(line.substr(diameterPos, line.find(",", diameterPos) - diameterPos));
            string inRepairStr = line.substr(repairPos);

            inRepair = (inRepairStr == "Yes");
            pipes[id] = { name, length, diameter, inRepair };

        }
    }

    inFile.close();
}

ostream& operator<<(ostream& os, const Pipe& pipe)
{
    os << ", Pipe name: " << pipe.name << ", Length: " << pipe.length << ", Diameter: " << pipe.diameter
        << ", In Repair: " << (pipe.inRepair ? "Yes" : "No") << endl;
    return os;

}

