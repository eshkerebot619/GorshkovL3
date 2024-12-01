#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "GorshkovLab3.2.h"
#include <map>


using namespace std;



class CS
{
private:
	string name;
	int stations;
	int workStations;
	int effectivity;

public:

	CS();

	CS(string n, int s, int w, int e);

	void addCS(int& id, map<int, CS>& cs);
	
	void showCS(map<int, CS>& cs);

	void deleteCS(map<int, CS>& cs);

	void editCS(int& editID, map<int, CS>& cs);

	void filterCS(int& id, map<int, CS>& cs);

	void saveToFile(ofstream& outFile, map<int, CS>& cs);

	void loadFromFile(string& fileName, map<int, CS>& cs, int& id);
};

