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
            currentState = nextState(currentState, input[i]);
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
            if ((*i).symbol == transition && (*i).beginState == currentState)
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
    string input, alphabet;
    char symbol;
    int stateName, numOfStates, fromState, toState, inputNum;
    bool final, start;
    cout << "-------------------------\n";
    cout << "Pleaase enter the language alphabet concatenated ex: ab , 01 , abc\n";
    cin >> alphabet;
    Automata automaton(alphabet);
    cout << "\n------------------------\n";
    cout << "Please enter the number of states in the automaton\n";
    cin >> numOfStates;

    for (int i = 0; i < numOfStates; i++)
    {
        cout << "\nEnter the state number (integer) and if its a start state 0 or 1 and if its a final state 0 or 1\nEample: 1 0 0 , 0 0 1\n";
        cin >> stateName >> start >> final;
        automaton.createState(stateName, start, final);
    }
    cout << "\n------------------------\n";
    cout << "Please enter the arcs (edges) in this format:\n symbol fromState toState ex: a 0 0 (loop)";
    for (int i = 0; i < alphabet.length() * numOfStates; i++)
    {
        cout << "\nEnter Arc:  ";
        cin >> symbol >> fromState >> toState;
        automaton.createArc(symbol, fromState, toState);
    }
    // automaton.createState(1, true, true);
    // automaton.createState(2, false, false);
    // automaton.createState(3, false, false);
    // automaton.createArc('a', 1, 1);
    // automaton.createArc('b', 1, 2);
    // automaton.createArc('a', 2, 3);
    // automaton.createArc('b', 2, 1);
    // automaton.createArc('a', 3, 2);
    // automaton.createArc('b', 3, 3);
    cout << "\n------------------------\n";
    cout << "Please the number of inputs you want to check\n";
    cin >> inputNum;
    for (int i = 0; i < inputNum; i++)
    {
        cout << "\n------------------------";
        cout << "\nEnter the input to check:  ";
        cin >> input;
        if (automaton.checkString(input))
            cout << "\nThe string \"" << input << "\" is Accepted";
        else
            cout << "\nThe string \"" << input << "\" is Rejected";
    }
}