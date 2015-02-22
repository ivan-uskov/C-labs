#include "stdafx.h"
#include "../body_hierarchy/Sphere.h"

using namespace std;

struct SphereTestsFixture
{
    double radius;
    double density;
    CSphere sphere;

    SphereTestsFixture()
        : radius(2)
        , density(2)
        , sphere(radius, density)
    {}
};

BOOST_FIXTURE_TEST_SUITE(SphereTests, SphereTestsFixture)

BOOST_AUTO_TEST_CASE(NewSphere)
{
    BOOST_CHECK(CheckDoublesAreEqual(sphere.GetRadius(), radius));

    BOOST_CHECK(CheckDoublesAreEqual(sphere.GetDensity(), density));
    BOOST_CHECK(CheckDoublesAreEqual(sphere.GetVolume(), (1.0 / 3.0) * M_PI * pow(radius, 3)));
    BOOST_CHECK(CheckDoublesAreEqual(sphere.GetMass(), sphere.GetDensity() * sphere.GetVolume()));
}

BOOST_AUTO_TEST_CASE(InvalidSphereDoesntCreated)
{
    BOOST_CHECK_THROW(CSphere(0), invalid_argument);
    BOOST_CHECK_THROW(CSphere(-1), invalid_argument);
    BOOST_CHECK_NO_THROW(CSphere(0.1));
}

BOOST_AUTO_TEST_CASE(SphereStringRepresentation)
{
    ostringstream strm;
    strm << "-- Sphere --" << endl <<
        "Radius: " << sphere.GetRadius() << endl <<
        "Volume: " << sphere.GetVolume() << endl <<
        "Density: " << sphere.GetDensity() << endl <<
        "Mass: " << sphere.GetMass() << endl;

    BOOST_CHECK(sphere.ToString() == strm.str());
}

BOOST_AUTO_TEST_SUITE_END()