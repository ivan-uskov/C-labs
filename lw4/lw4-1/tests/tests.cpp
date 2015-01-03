#include "stdafx.h"
#include "../virtual_car/Car.cpp"


struct CarTestsFixture
{
    CCar car;
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

BOOST_AUTO_TEST_CASE(VerifySpeedChange)
{
    BOOST_CHECK(car.TurnOnEngine());
    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK_EQUAL(car.GetGear(), 1);
    BOOST_CHECK(car.SetSpeed(20));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
    BOOST_CHECK(car.SetSpeed(30));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 30);

    BOOST_CHECK(car.SetGear(0));
    BOOST_CHECK_EQUAL(car.GetGear(), 0);
    BOOST_CHECK(car.SetSpeed(0));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    BOOST_CHECK(!car.SetSpeed(20));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
}

BOOST_AUTO_TEST_CASE(VefiryGearChange)
{
    BOOST_CHECK(car.TurnOnEngine());

    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK_EQUAL(car.GetGear(), 1);

    BOOST_CHECK(car.SetSpeed(20));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 20);

    BOOST_CHECK(car.SetGear(2));
    BOOST_CHECK_EQUAL(car.GetGear(), 2);

    BOOST_CHECK(car.SetSpeed(50));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 50);

    BOOST_CHECK(car.SetGear(3));
    BOOST_CHECK_EQUAL(car.GetGear(), 3);

    BOOST_CHECK(car.SetSpeed(60));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 60);

    BOOST_CHECK(car.SetGear(4));
    BOOST_CHECK_EQUAL(car.GetGear(), 4);

    BOOST_CHECK(car.SetSpeed(90));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 90);

    BOOST_CHECK(car.SetGear(5));
    BOOST_CHECK_EQUAL(car.GetGear(), 5);

    BOOST_CHECK(car.SetSpeed(150));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 150);

    BOOST_CHECK(car.GetDirection() == CCar::Direction::Ahead);

    BOOST_CHECK(car.SetGear(0));
    BOOST_CHECK_EQUAL(car.GetGear(), 0);

    BOOST_CHECK(car.SetSpeed(0));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

    BOOST_CHECK(car.GetDirection() == CCar::Direction::None);
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

    BOOST_CHECK(car.GetDirection() == CCar::Direction::Back);
}
BOOST_AUTO_TEST_CASE(VerifyErrorBehaviorInSwitchingGearOrSpeed)
{
    BOOST_CHECK(car.TurnOnEngine());

    BOOST_CHECK(!car.SetSpeed(20));
    BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

    BOOST_CHECK(car.SetGear(1));
    BOOST_CHECK(car.SetSpeed(20));

    BOOST_CHECK(!car.SetGear(-1));
    BOOST_CHECK(!car.SetGear(4));
    BOOST_CHECK(!car.SetSpeed(145));

}

BOOST_AUTO_TEST_SUITE_END()