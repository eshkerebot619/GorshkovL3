#include "CS.h"


using namespace std;


CS::CS()
{
	name = "";
	stations = 1;
	workStations = 0;
	effectivity = 0;
}

CS::CS(string n, int s, int w, int e)
{
	name = n;
	stations = s;
	workStations = w;
	effectivity = e;
}


void CS::addCS(int& id, map<int, CS>& cs)
{
	++id;
	cout << "Enter name of CS: ";
	getline(cin, name);

	stations = inputWhat("Enter number of stations: ", "Integer");

	while (true)
	{
		workStations = inputWhat("Enter number of working stations: ", "Integer");
		if (workStations <= stations) {
			break;
		}
	}

	while (true)
	{
		effectivity = inputWhat("Enter effectivity (0-100): ", "Integer");
		if (effectivity >= 0 && effectivity <= 100) {
			break;
		}
	}

	cs[id] = { name , stations, workStations, effectivity };

}

void CS::showCS(map<int, CS>& cs)
{
	for (const auto& cs : cs) {
		std::cout << "CS ID: " << cs.first << " CS name: " << cs.second.name << ", the number of stations: " << cs.second.stations << ", the number of working stations: " << cs.second.workStations
			<< ", Effectivity: " << cs.second.effectivity << endl;
	}
}

void CS::deleteCS(map<int, CS>& cs)
{
	showCS(cs);
	int delID;
	delID = inputWhat("Enter ID: ", "Integer");
	if (cs.erase(delID)) {
		cout << "CS with ID " << delID << " deleted successfully." << endl;
	}
	else {
		cout << "CS with ID " << delID << " not found." << endl;

	}
}

void CS::editCS(int& editID, map<int, CS>& cs)
{
	if (cs.find(editID) != cs.end()) {
		while (true)
		{
			cs[editID].workStations = inputWhat("Enter numbber of working stations: ", "Integer");
			if (cs[editID].workStations <= cs[editID].stations) {
				break;
			}
		}
	}
}

void CS::filterCS(int& id, map<int, CS>& cs)
{
    if (cs.empty()) {
        cout << "No pipes available.\n";
        return;
    }
    showCS(cs);
    vector<int> filtered;
    string filterName;
    bool filterByName = inputWhat("Filter by name? (Y/N): ", "Repair");

    if (filterByName) {
        cout << "Enter name to filter by: ";
        getline(cin, filterName);

        for (int i = 1; i <= id; ++i) {
            if (cs.find(i) != cs.end() && cs[i].name.find(filterName) != string::npos) {
                cout << "ID: " << i
                    << ", Name: " << cs[i].name
                    << ", Number of stations: " << cs[i].stations
                    << ", Number working stations: " << cs[i].workStations
                    << ", Effictivity: " << cs[i].effectivity << endl;
                filtered.push_back(i);
            }
        }
    }
    else {
        int filterCoef = inputWhat("Working stations/Stations * 100%: ", "Integer");

        for (int i = 1; i <= id; ++i) {
            if (cs.find(i) != cs.end() && (((cs[i].workStations * 100) / cs[i].stations) >= (filterCoef - 15)) && (((cs[i].workStations * 100) / cs[i].stations) <= (filterCoef + 15))) {
                cout << "ID: " << i
                    << ", Name: " << cs[i].name
                    << ", Number of stations: " << cs[i].stations
                    << ", Number working stations: " << cs[i].workStations
                    << ", Effictivity: " << cs[i].effectivity << endl;
                filtered.push_back(i);
            }
        }
    }

    string choice;
    cout << "Edit all (A), specific by ID (S), or cancel (N)? (A/S/N): ";
    getline(cin, choice);
    int newEffectivity;
    if (choice == "A" || choice == "a") {
        while (true)
        {
            newEffectivity = inputWhat("Set effectuvuty: ", "Integer");
            if (newEffectivity <= 100 && newEffectivity >= 0) {
                break;
            }
        }

        for (const auto& i : filtered) {
            cs[i].effectivity = newEffectivity;
        }
        cout << "All found cs have been updated.\n";
    }
    else if (choice == "S" || choice == "s") {
        int csID = inputWhat("Enter CS ID to edit: ", "Integer");
        editCS(csID, cs);
    }
    else if (choice == "N" || choice == "n") {
        cout << "No changes made.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void CS::saveToFile(ofstream& outFile, map<int, CS>& cs)
{
    if (!cs.empty()) {
        for (auto& station : cs) {
            outFile << "CS name: " << station.second.name << ", CS ID: " << station.first << ", the number of stations: " << station.second.stations << ", the number of working stations: " << station.second.workStations
                << ", Effectivity: " << station.second.effectivity << endl;
        }
    }
}

void CS::loadFromFile(string& fileName, map<int, CS>& cs, int& id)
{
    ifstream inFile(fileName);

    if (!inFile.is_open()) {
        std::cout << "Error: Unable to open file for loading" << endl;
        return;
    }

    string line;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        if (line.find("CS name:") != string::npos) {
            string name;

            size_t namePos = line.find("CS name:") + 9;
            size_t idPos = line.find("CS ID:") + 7;
            size_t stationsCountPos = line.find("the number of stations:") + 24;
            size_t workingStsPos = line.find("the number of working stations:") + 32;
            size_t effectivityPos = line.find("Effectivity:") + 13;

            name = line.substr(namePos, line.find(",", namePos) - namePos);
            id = stoi(line.substr(idPos, line.find(",", idPos) - idPos));
            int stationsCount = stod(line.substr(stationsCountPos, line.find(",", stationsCountPos) - stationsCountPos));
            int workingSts = stod(line.substr(workingStsPos, line.find(",", workingStsPos) - workingStsPos));
            int effectivity = stod(line.substr(effectivityPos));

            if (name.empty() || stationsCount < 0 || workingSts < 0 || effectivity < 0) {
                std::cout << "Error loading data: Invalid values found in line: " << line << endl;
                continue;
            }

            cs[id] = { name, stationsCount, workingSts,effectivity };

        }
    }

    inFile.close();
}