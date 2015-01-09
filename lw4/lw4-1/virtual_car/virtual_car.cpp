#include "stdafx.h"
#include "Car.h"

using namespace std;

typedef void (*Command)(CCar &, const int);

struct Action
{
    Command command;
    int argument;
};

void ExecuteInfo(CCar & car, const int argument)
{
    cout << "Car Info" << endl;
    cout << "Gear: " << car.GetGear() << endl;
    cout << "Speed: " << car.GetSpeed() << endl;
    cout << "Direction: ";

    switch (car.GetDirection())
    {
        case CCar::Direction::Ahead :
        {
            cout << "Ahead";
            break;
        }
        case CCar::Direction::Back:
        {
            cout << "Back";
            break;
        }
        case CCar::Direction::None:
        {
            cout << "None";
            break;
        }
    }
    cout << endl;
}

void ExecuteSetSpeed(CCar & car, const int argument)
{
    if (car.SetSpeed(argument))
    {
        cout << "New speed: " << argument << endl;
    }
    else
    {
        cout << "Can't set speed" << endl;
    }
}

void ExecuteSetGear(CCar & car, const int argument)
{
    if (car.SetGear(argument))
    {
        cout << "New gear: " << argument << endl;
    }
    else
    {
        cout << "Can't set gear" << endl;
    }
}

void ExecuteEngineOn(CCar & car, const int argument)
{
    if (car.TurnOnEngine())
    {
        cout << "Engine started!" << endl;
    }
    else
    {
        cout << "Engine is already working" << endl;
    }
}

void ExecuteEngineOff(CCar & car, const int argument)
{
    if (car.TurnOffEngine())
    {
        cout << "Engine stoped!" << endl;
    }
    else
    {
        cout << "Can't stop engine now" << endl;
    }
}

void ExecuteHelp(CCar & car, const int argument)
{
    char ch;
    ifstream helpFile("help.txt");

    while (helpFile.peek() != EOF)
    {
        cout << static_cast<char>(helpFile.get());
    }

    cout << endl;
}

bool ParseCommand(string const& cmdStr, Command & command)
{
    if (cmdStr == "Info")
    {
        command = ExecuteInfo;
    }
    else if (cmdStr == "SetSpeed")
    {
        command = ExecuteSetSpeed;
    }
    else if (cmdStr == "SetGear")
    {
        command = ExecuteSetGear;
    }
    else if (cmdStr == "EngineOn")
    {
        command = ExecuteEngineOn;
    }
    else if (cmdStr == "EngineOff")
    {
        command = ExecuteEngineOff;
    }
    else if (cmdStr == "Help")
    {
        command = ExecuteHelp;
    }
    else if (cmdStr == "End")
    {
        command = nullptr;
    }
    else
    {
        return false;
    }
    return true;
}

bool NeedArgument(Command const& command)
{
    return (command == ExecuteSetGear) || (command == ExecuteSetSpeed);
}

bool ReadCommand(Action & action)
{
    cout << "> ";
    string command, inputLine;
    getline(cin, inputLine);
    istringstream input(inputLine);

    if (!((input >> command) && ParseCommand(command, action.command)))
    {
        cout << "Invalid command: " << command << endl;
        return false;
    }

    if (NeedArgument(action.command) && !(input >> action.argument))
    {
        cout << "Invalid argument for command: " << command << endl;
        return false;
    }

    return true;
}

bool ReadAction(Action & action)
{
    while (!ReadCommand(action))
    {
        cout << "Input Error, use 'Help' for command reference!" << endl;
    };

    return (action.command != nullptr);
}

void ExecuteAction(CCar & car, Action const& action)
{
    action.command(car, action.argument);
}

int main(int argc, char* argv[])
{ 
    CCar car;
    Action action;

    cout << "Hello enter your command! Type 'Help' for command reference!" << endl;

    while (ReadAction(action))
    {
        ExecuteAction(car, action);
    }

    cout << "Bye!" << endl;

    return 0;
}

