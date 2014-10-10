#include "stdafx.h"

const double ACCELERATION_TO_GRAVITY = 9.8; // ускорение свободного падения
const double PI = 3.14159265358979323;
const std::string EXIT_LINE = "exit";

enum LOOP_STATE
{
    Break,
    Continue,
    None
};


double getRadByDegree(double degree)
{
    return degree * PI / 180;
}

double calculateDistance(double speed, double alpha)
{    
    double coal = sin(getRadByDegree(2 * alpha));
    return speed * speed * sin(getRadByDegree(2 * alpha)) / ACCELERATION_TO_GRAVITY;
}

bool checkSpeed(double speed)
{
    return speed > 0;
}

bool checkAlpha(double alpha)
{
    return (0 < alpha) && (alpha < 90);
}

LOOP_STATE initSpeed(double * speed)
{
    std::string line;
    printf("Enter speed [m/s] (or type 'exit')> ");
    std::getline(std::cin, line);
    if (line.compare(EXIT_LINE) == 0)
    {
        return Break;
    }

    *speed = strtod(line.c_str(), NULL);

    if (!checkSpeed(*speed))
    {
        printf("Invalid parameter\n");
        return Continue;
    }
    return None;
}

LOOP_STATE initAlpha(double * alpha)
{
    std::string line;
    printf("Enter a0 [degree] (or type 'exit')> ");
    std::getline(std::cin, line);
    if (line.compare(EXIT_LINE) == 0)
    {
        return Break;
    }

    *alpha = strtod(line.c_str(), NULL);
    if (!checkAlpha(*alpha))
    {
        printf("Invalid parameter\n");
        return Continue;
    }
    return None;
}

int main(int argc, char* argv[])
{
    while (1)
    {
        LOOP_STATE state;
        double speed;
        double alpha;
        
        state = initSpeed(&speed);
        if (state == Break)
        {
            break;
        }
        else if (state == Continue)
        {
            continue;
        }

        state = initAlpha(&alpha);
        if (state == Break)
        {
            break;
        }
        else if (state == Continue)
        {
            continue;
        }

        printf("Distance is: %.3f\n", calculateDistance(speed, alpha));
    }

    return 0;
}


