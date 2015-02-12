#include "stdafx.h"
#include "Car.h"
#include <limits>

using namespace std;

bool IsSpeedInRange(pair<int, int> const& range, int const speed);

CCar::CCar()
    : m_isEngineOn(false)
    , m_gear(0)
    , m_speed(0)
    , m_direction(Direction::None)
{
}


CCar::~CCar()
{
}

/* Public methods */

// Property access

bool CCar::IsEngineOn()const
{
    return m_isEngineOn;
}

int CCar::GetGear()const
{
    return m_gear;
}

int CCar::GetSpeed()const
{
    return m_speed;
}

CCar::Direction CCar::GetDirection()const
{
    return m_direction;
}

// Change state 

bool CCar::TurnOnEngine()
{
    m_isEngineOn = IsEngineStartable();
    return m_isEngineOn;
}

bool CCar::TurnOffEngine()
{
    m_isEngineOn = !IsEngineStopable();
    return !m_isEngineOn;
}

bool CCar::SetSpeed(int speed)
{
    if (IsSpeedChangeble(speed))
    {
        m_speed = speed;
        UpdateDirection();
        return true;
    }
    return false;
}

bool CCar::SetGear(int gear)
{
    if (IsGearChangeble(gear))
    {
        m_gear = gear;
        return true;
    }
    return false;
}

/* Private methods */

bool CCar::IsEngineStartable()const
{
    return (!m_isEngineOn) && (m_speed == 0) && (m_gear == 0);
}

bool CCar::IsEngineStopable()const
{
    return m_isEngineOn && (m_speed == 0) && (m_gear == 0);
}

pair<int, int> CCar::GetSpeedRange(const int gear)const
{
    switch (gear)
    {
        case -1:
            return { 0, 20 };
        case 0:
            return { 0, 150 };
        case 1:
            return { 0, 30 };
        case 2:
            return { 20, 50 };
        case 3:
            return { 30, 60 };
        case 4:
            return { 40, 90 };
        case 5:
            return { 50, 150 };
        default:
            return { 0, 0 };
    }
}

bool CCar::IsSpeedChangeble(const int speed)const
{
    return (m_gear == 0 && speed < m_speed) || (m_gear != 0 && IsSpeedInRange(GetSpeedRange(m_gear), speed));
}

bool CCar::IsGearChangeble(const int gear)const
{
    bool IsGearCorrect = (-1 <= gear && gear <= 5);

    bool IsSpeedInNewGearRange = IsSpeedInRange(GetSpeedRange(gear), m_speed);

    bool IsDirectionCorrect = (gear == 0) || (m_direction == Direction::None) ||
        (gear > 0 && m_direction == Direction::Ahead) ||
        (gear < 0 && m_direction == Direction::Back);

    return IsGearCorrect && IsSpeedInNewGearRange && IsDirectionCorrect;
}

void CCar::UpdateDirection()
{
    if (m_speed == 0)
    {
        m_direction = Direction::None;
    }
    else if (m_gear > 0)
    {
        m_direction = Direction::Ahead;
    }
    else if (m_gear < 0)
    {
        m_direction = Direction::Back;
    }
}

bool IsSpeedInRange(pair<int, int> const& range, int const speed)
{
    return (range.first <= speed) && (speed <= range.second);
}