#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Pipe.h"
#include "CS.h"

using namespace std;

class GasTransportNetwork {
private:
    map<int, vector<pair<int, int>>> adjList;
  
public:
    void connectStations(int inCS, int outCS, int diameter, map<int, Pipe>& pipes, int& pipeID);

    void displayNetwork(const map<int, CS>& cs, const map<int, Pipe>& pipes) const;

    vector<int> topologicalSort() const;
};
