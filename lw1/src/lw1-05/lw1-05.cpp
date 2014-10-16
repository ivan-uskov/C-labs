#include "stdafx.h"

const double GRAVITY = 9.8;
const double PI = 3.14159265358979323;
const std::string EXIT_LINE = "exit";

double DegreeToRadians(double degree)
{
    return degree * PI / 180;
}

double CalculateDistance(double speed, double angle)
{
    double coal = sin(DegreeToRadians(2 * angle));
    return speed * speed * sin(DegreeToRadians(2 * angle)) / GRAVITY;
}

bool CheckSpeed(double speed)
{
    return speed > 0;
}

bool CheckAngle(double angle)
{
    return (0 < angle) && (angle < 90);
}

bool ReadDouble(double * num)
{
    std::string inputString;
    std::getline(std::cin, inputString);
    if (inputString == EXIT_LINE)
    {
        return false;
    }
    *num = strtod(inputString.c_str(), NULL);
    return true;
}

bool ReadSpeed(double * speed)
{
    bool isSpeedCorrect;
    do 
    {
        printf("Enter speed [m/s] (or type 'exit')> ");
        
        if (!ReadDouble(speed))
        {
            return false;
        }

        isSpeedCorrect = CheckSpeed(*speed);
        if (!isSpeedCorrect)
        {
            printf("Invalid parameter!\nUsage: [SPEED INTEGER > 0 [m/s]]\n");
        }
    }
    while (!isSpeedCorrect);
    return true;
}

bool ReadAngle(double * angle)
{
    bool isAngleCorrect;
    do
    {
        printf("Enter a0 [degree] (or type 'exit')> ");

        if (!ReadDouble(angle))
        {
            return false;
        }

        isAngleCorrect = CheckAngle(*angle);
        if (!isAngleCorrect)
        {
            printf("Invalid parameter!\nUsage: [Angle 0 < INTEGER < 90 [degree]]\n");
        }
    } while (!isAngleCorrect);
    return true;
}

int main(int argc, char* argv[])
{
    while (1)
    {
        double speed;
        double angle;

        if (!ReadSpeed(&speed))
        {
            printf("Thinks for using as!\n");
            return 1;
        }

        if (!ReadAngle(&angle))
        {
            printf("Thinks for using as!\n");
            return 1;
        }

        printf("Distance is: %.3f\n", CalculateDistance(speed, angle));
    }
    return 0;
}