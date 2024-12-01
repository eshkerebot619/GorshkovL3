#pragma once
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iostream>


using namespace std;

class Pipe
{
private:
	string name;
	int length;
	int diameter;
	bool inRepair;
public:

	Pipe();
	
	Pipe(string n, int l, int d, bool r);

	int getDiameter() const { return diameter; }

	bool isInRepair() const { return inRepair; }

	void addPipe(int& id, map<int, Pipe>& pipes);

	void displayPipes(map<int, Pipe> pipes) const;

	void deletePipe(map<int, Pipe>& pipes);

	void editPipe(int& id, map<int, Pipe>& pipes);

	void filterPipe(map<int, Pipe>& pipes);

	void saveToFile(ofstream& outFile, map<int, Pipe>& pipes);

	void loadFromFile(string& filename, map<int, Pipe>& pipes, int& id);

	friend std::ostream& operator<<(ostream& os, const Pipe& p);
};

