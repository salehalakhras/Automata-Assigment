#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
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
    Automata(string alphabet)
    {
        this->alphabet = alphabet;
    }

    void createState(int name, bool isFinal, bool isStart)
    {
        State temp(name, isFinal, isStart);
        if (isStart)
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

    bool checkString(string input)
    {
        int currentState = start.name;

        for (int i = 0; i < input.length(); i++)
        {
            currentState = nextState(currentState , input[i]);
        }

        if (returnState(currentState).isFinal)
            return true;
        else
            return false;
    }

    int nextState(int currentState, char transition)
    {
        list<Arc>::iterator i;
        for (i = arcs.begin(); i != arcs.end(); i++)
        {
            if((*i).symbol == transition && (*i).beginState == currentState)
                return (*i).finishState;
        }

        return -1;
    }

    State returnState(int name)
    {
        State temp;
        temp.name = -1;
        list<State>::iterator i;
        for (i = states.begin(); i != states.end(); i++)
        {
            if ((*i).name == name)
                return *i;
        }
        return temp;
    }
};

int main()
{
    string input;
    Automata automaton("01");
    automaton.createState(0, true, true);
    automaton.createState(1, false, false);
    automaton.createArc('0', 0, 0);
    automaton.createArc('1', 0, 1);
    automaton.createArc('0', 1, 1);
    automaton.createArc('1', 1, 0);

    cout<<"Please enter a string to check"<<endl;
    cin>>input;
    if(automaton.checkString(input))
        cout<<"Yes"<<endl;
    else
        cout<<"No"<<endl;
}