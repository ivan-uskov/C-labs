#include "stdafx.h"
#include "../body_hierarchy/Cone.h"

using namespace std;

struct ConeTestsFixture
{
    double radius;
    double height;
    double density;
    CCone cone;

    ConeTestsFixture()
        : radius(2)
        , height(3)
        , density(2)
        , cone(radius, density)
    {}
};

BOOST_FIXTURE_TEST_SUITE(ConeTests, ConeTestsFixture)

BOOST_AUTO_TEST_CASE(NewCone)
{
    BOOST_CHECK(CheckDoublesAreEqual(cone.GetRadius(), radius));
    BOOST_CHECK(CheckDoublesAreEqual(cone.GetHeight(), height));

    BOOST_CHECK(CheckDoublesAreEqual(cone.GetDensity(), density));
    BOOST_CHECK(CheckDoublesAreEqual(cone.GetVolume(), (1.0 / 3.0) * M_PI * pow(radius, 2) * height));
    BOOST_CHECK(CheckDoublesAreEqual(cone.GetMass(), cone.GetDensity() * cone.GetVolume()));
}

BOOST_AUTO_TEST_CASE(InvalidConeDoesntCreated)
{
    BOOST_CHECK_THROW(CCone(0, 1), invalid_argument);
    BOOST_CHECK_THROW(CCone(-1, 1), invalid_argument);

    BOOST_CHECK_THROW(CCone(1, 0), invalid_argument);
    BOOST_CHECK_THROW(CCone(1, -1), invalid_argument);

    BOOST_CHECK_NO_THROW(CCone(0.1, 0.1));
}

BOOST_AUTO_TEST_CASE(ConeStringRepresentation)
{
    ostringstream strm;
    strm << "-- Cone --" << endl <<
        "Radius: " << cone.GetRadius() << endl <<
        "Height: " << cone.GetHeight() << endl <<
        "Volume: " << cone.GetVolume() << endl <<
        "Density: " << cone.GetDensity() << endl <<
        "Mass: " << cone.GetMass() << endl;

    BOOST_CHECK(cone.ToString() == strm.str());
}

BOOST_AUTO_TEST_SUITE_END()