#pragma once
#include <utility>

class CCar
{
public:

    enum class Direction
    {
        Ahead,
        Back,
        None
    };

    CCar();
    ~CCar();

    int GetGear()const;
    int GetSpeed()const;
    bool IsEngineOn()const;
    Direction GetDirection()const;


    bool TurnOnEngine();
    bool TurnOffEngine();
    
    bool SetGear(int gear);
    bool SetSpeed(int speed);

private:

    Direction m_direction;
    bool m_isEngineOn;
    int m_speed;
    int m_gear;

    bool IsEngineStartable()const;
    bool IsEngineStopable()const;
    bool IsSpeedChangeble(const int speed)const;
    bool IsGearChangeble(const int gear)const;

    std::pair<int, int> GetSpeedRange(const int gear)const;
    bool IsNewSpeedCorrect(int newSpeed)const;

    void UpdateDirection();
};

