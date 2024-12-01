#include "GasTransportNetwork.h"
#include <queue>
#include <set>

void GasTransportNetwork::connectStations(int inCS, int outCS, int diameter, map<int, Pipe>& pipes, int& pipeID)
{
    
    for (const auto& pipe : pipes) {
        if (pipe.second.getDiameter() == diameter && !pipe.second.isInRepair()) {
            adjList[inCS].emplace_back(outCS, pipe.first);
            cout << "Connected CS " << inCS << " -> CS " << outCS << " using Pipe ID " << pipe.first << endl;
            return;
        }
    }

    Pipe newPipe;
    newPipe.addPipe(pipeID, pipes);
    adjList[inCS].emplace_back(outCS, pipeID);
    cout << "Created and connected CS " << inCS << " -> CS " << outCS << " using new Pipe ID " << pipeID << endl;
}

void GasTransportNetwork::displayNetwork(const map<int, CS>& cs, const map<int, Pipe>& pipes) const
{
    for (const auto& connections : adjList) {
        cout << "CS " << connections.first << " connections:\n";
        for (const auto& connection : connections.second) {
            int outCS = connection.first;
            int pipeID = connection.second;
            cout << "  -> CS " << outCS << " via Pipe ID " << pipeID
                << " (Diameter: " << pipes.at(pipeID).getDiameter() << ")\n";
        }
    }

}

vector<int> GasTransportNetwork::topologicalSort() const
{
    map<int, int> inDegree;

    for (auto it = adjList.begin(); it != adjList.end(); ++it) {
        int node = it->first;
        const vector<pair<int, int>>& edges = it->second;

        if (inDegree.find(node) == inDegree.end()) {
            inDegree[node] = 0;
        }

        for (size_t i = 0; i < edges.size(); ++i) {
            int dest = edges[i].first;
            if (inDegree.find(dest) == inDegree.end()) {
                inDegree[dest] = 0;
            }
            inDegree[dest]++;
        }
    }

    // Заполняем очередь узлами с нулевой степенью
    queue<int> zeroInDegree;
    for (auto it = inDegree.begin(); it != inDegree.end(); ++it) {
        if (it->second == 0) {
            zeroInDegree.push(it->first);
        }
    }

    // Выполняем топологическую сортировку
    vector<int> sorted;
    while (!zeroInDegree.empty()) {
        int current = zeroInDegree.front();
        zeroInDegree.pop();
        sorted.push_back(current);

        if (adjList.find(current) != adjList.end()) {
            const vector<pair<int, int>>& neighbors = adjList.at(current);
            for (size_t i = 0; i < neighbors.size(); ++i) {
                int neighbor = neighbors[i].first;
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    zeroInDegree.push(neighbor);
                }
            }
        }
    }

    // Проверка на циклы
    if (sorted.size() != adjList.size()) {
        cout << "Graph has cycles! Topological sort is not possible.\n";
        return {};
    }

    return sorted;
}


