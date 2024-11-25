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
	int id;
public:

	Pipe(string n, int l, int d, bool r);

	string getName();

	int getLength();

	int getDiameter();

	bool getInRepair();

	void addPipe(map<int, Pipe> pipes);

	void displayPipes(map<int, Pipe> pipes) const;

	friend std::ostream& operator<<(ostream& os, const Pipe& p);
};

