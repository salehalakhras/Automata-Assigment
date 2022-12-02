#include <iostream>
#include <list>
#include <iterator>
#include<algorithm>
using namespace std;

class State
{
public:
    int name;
    bool isFinal;
    bool isStart;

    State()
    {
    }

    State(int name, bool isFinal, bool isStart)
    {
        this->name = name;
        this->isFinal = isFinal;
        this->isStart = isStart;
    }
};
class Arc
{
public:
    char symbol;
    int beginState;
    int finishState;

    Arc()
    {
        symbol = ' ';
    }
};

class Automata
{
    list<State> states;
    string alphabet;
    list<Arc> arcs;
    State start;

public:
    Automata(int numOfStates, int numOfArcs, string alphabet)
    {
        states.resize(numOfStates);
        arcs.resize(numOfArcs);
        this->alphabet = alphabet;
    }

    void createState(int name, bool isFinal, bool isStart)
    {  
        State temp(name, isFinal, isStart);
        if(isStart)
            start = temp;
        states.push_back(temp);
    }

    void createArc(char symbol, int startState, int endState)
    {
        if (alphabet.find(symbol) == string::npos)
            cout << "The arc symbol you entered does not belong to the alphabet\n";
        else
        {
            Arc temp;
            temp.symbol = symbol;
            temp.beginState = startState;
            temp.finishState = endState;
            arcs.push_back(temp);
        }
    }


};

int main()
{
    Automata automaton(2,4,"01");
    automaton.createState(0,true,true);
    automaton.createState(1,false,false);
    automaton.createArc('0',0,0);
    automaton.createArc('1',0,1);
    automaton.createArc('0',1,1);
    automaton.createArc('1',1,0);
}