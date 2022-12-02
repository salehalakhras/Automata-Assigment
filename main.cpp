#include <iostream>
#include <list>
using namespace std;

class Arc
{
    char symbol;
    State beginState;
    State finishState;
};

class State
{
    int name;
    bool isFinal;
    bool isStart;
};

class Automata
{
    list<State> states;
    char alphabet[];
    list<Arc> arcs;
};

int main()
{
}