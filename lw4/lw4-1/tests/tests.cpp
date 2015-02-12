#include "stdafx.h"
#include "../virtual_car/Car.h"
#include <functional>

using namespace std;
using namespace std::placeholders;


bool CarStateIsNotChangedOn(CCar const& car, function<void(CCar & car)> const& fn)
{
    CCar clone(car);
    fn(clone);
    return
        (car.IsEngineOn() == clone.IsEngineOn()) &&
        (car.GetGear() == clone.GetGear()) &&
        (car.GetSpeed() == clone.GetSpeed()) &&
        (car.GetDirection() == clone.GetDirection());
}

void SwitchGear(CCar & car, int gear)
{
    car.SetGear(gear);
}

void SwitchSpeed(CCar & car, int speed)
{
    car.SetSpeed(speed);
}

struct CarTestsFixture
{
    CCar car;

    bool StateIsNotChangedOn(function<void(CCar & car)> const& fn)
    {
        return CarStateIsNotChangedOn(car, fn);
    }
};

BOOST_FIXTURE_TEST_SUITE(CCarTests, CarTestsFixture)

BOOST_AUTO_TEST_CASE(VerifyNewCar)
{
    BOOST_CHECK(!car.IsEngineOn());
    BOOST_CHECK_EQUAL(car.GetGear(), 0);
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    BOOST_CHECK(car.GetDirection() == CCar::Direction::None);
}

BOOST_AUTO_TEST_CASE(VerifyEngineTurnOn)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.IsEngineOn());
    BOOST_CHECK_EQUAL(car.GetGear(), 0);
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    BOOST_CHECK(car.GetDirection() == CCar::Direction::None);
}

BOOST_AUTO_TEST_CASE(VerifyEngineTurnOff)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.TurnOffEngine());
    BOOST_CHECK(!car.IsEngineOn());
    BOOST_CHECK_EQUAL(car.GetGear(), 0);
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    BOOST_CHECK(car.GetDirection() == CCar::Direction::None);
}

BOOST_AUTO_TEST_CASE(VerifyFirstGearChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK_EQUAL(car.GetGear(), 1);

    //Set max
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);
    // Set min
    BOOST_CHECK(car.SetSpeed(0));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    BOOST_CHECK(car.GetDirection() == CCar::Direction::None);
    // Verify borders
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 31)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, -1)));
}

BOOST_AUTO_TEST_CASE(VerifySecondGearChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(20));
    BOOST_CHECK(car.SetGear(2));
    BOOST_CHECK_EQUAL(car.GetGear(), 2);

    //Set max
    BOOST_CHECK(car.SetSpeed(50));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
    // Set min
    BOOST_CHECK(car.SetSpeed(20));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
    // Verify borders
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 51)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 19)));
    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);
}

BOOST_AUTO_TEST_CASE(VerifyThirdGearChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK(car.SetGear(3));
    BOOST_CHECK_EQUAL(car.GetGear(), 3);

    //Set max
    BOOST_CHECK(car.SetSpeed(60));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
    // Set min
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
    // Verify borders
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 61)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 29)));
    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);
}

BOOST_AUTO_TEST_CASE(VerifyFourthGearChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK(car.SetGear(3));
    BOOST_CHECK(car.SetSpeed(40));
    BOOST_CHECK(car.SetGear(4));
    BOOST_CHECK_EQUAL(car.GetGear(), 4);

    //Set max
    BOOST_CHECK(car.SetSpeed(90));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
    // Set min
    BOOST_CHECK(car.SetSpeed(40));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
    // Verify borders
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 91)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 39)));
    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);
}

BOOST_AUTO_TEST_CASE(VerifyFifthGearChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK(car.SetGear(3));
    BOOST_CHECK(car.SetSpeed(40));
    BOOST_CHECK(car.SetGear(4));
    BOOST_CHECK_EQUAL(car.GetGear(), 4);

    //Set max
    BOOST_CHECK(car.SetSpeed(90));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
    // Set min
    BOOST_CHECK(car.SetSpeed(40));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
    // Verify borders
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 91)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 39)));
    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);
}

BOOST_AUTO_TEST_CASE(VerifySixthearChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK(car.SetGear(3));
    BOOST_CHECK(car.SetSpeed(50));
    BOOST_CHECK(car.SetGear(5));
    BOOST_CHECK_EQUAL(car.GetGear(), 5);

    //Set max
    BOOST_CHECK(car.SetSpeed(150));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 150);
    // Set min
    BOOST_CHECK(car.SetSpeed(50));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
    // Verify borders
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 151)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 49)));
    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);
}

BOOST_AUTO_TEST_CASE(VerifyChangeGearToBack)
{
    BOOST_CHECK(car.TurnOnEngine());

    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK_EQUAL(car.GetGear(), 1);
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

    BOOST_CHECK(car.SetGear(-1));
    BOOST_CHECK_EQUAL(car.GetGear(), -1);

    BOOST_CHECK(car.SetSpeed(20));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 20);

    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 21)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, -1)));

    BOOST_CHECK(car.GetDirection() == CCar::Direction::Back);
}

BOOST_AUTO_TEST_CASE(VerifyErrorBehaviorInSwitchingGearOrSpeed)
{
    BOOST_CHECK(car.TurnOnEngine());

    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchSpeed, car, 20)));

    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(20));

    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchGear, car, -1)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchGear, car, 3)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchGear, car, 4)));
    BOOST_CHECK(StateIsNotChangedOn(bind(SwitchGear, car, 145)));
}

BOOST_AUTO_TEST_SUITE_END()