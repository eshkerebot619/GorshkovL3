#include "Pipe.h"
#include "GorshkovLab3.2.h"


using namespace std;

Pipe::Pipe(string n, int l, int d, bool r)
{
    name = n;
    length = l;
    diameter = d;
    inRepair = r;
}

string Pipe::getName()
{
    return name;
}

int Pipe::getLength()
{
    return length;
}

int Pipe::getDiameter()
{
    return diameter;
}

bool Pipe::getInRepair()
{
    return inRepair;
}

void Pipe::addPipe(map<int, Pipe> pipes)
{
    id++;
    cout << "Enter name: ";
    getline(cin, name);
    length = inputWhat("Enter length: ", "Integer");
    diameter = inputWhat("Enter diameter: ", "Integer");
    inRepair = inputWhat("Is the pipe being repaired? (Y/N):  ", "Repair");
    
    pipes[id] = Pipe(name, length, diameter, inRepair);
}

void Pipe::displayPipes(map<int, Pipe> pipes) const
{
    for (const auto& pipe : pipes) {
        cout << pipe.second;
    }
}

ostream& operator<<(ostream& os, const Pipe& pipe)
{
    os << "Pipe ID: " << pipe.id << ", Pipe name: " << pipe.name << ", Length: " << pipe.length << ", Diameter: " << pipe.diameter
        << ", In Repair: " << (pipe.inRepair ? "Yes" : "No") << endl;
    return os;

}

