#include "stdafx.h"
#include "../body_hierarchy/Cylinder.h"

using namespace std;

struct CylinderTestsFixture
{
    double radius;
    double height;
    double density;
    CCylinder cylinder;

    CylinderTestsFixture()
        : radius(2)
        , height(3)
        , density(2)
        , cylinder(radius, density)
    {}
};

BOOST_FIXTURE_TEST_SUITE(CylinderTests, CylinderTestsFixture)

BOOST_AUTO_TEST_CASE(NewCylinder)
{
    BOOST_CHECK(CheckDoublesAreEqual(cylinder.GetRadius(), radius));
    BOOST_CHECK(CheckDoublesAreEqual(cylinder.GetHeight(), height));

    BOOST_CHECK(CheckDoublesAreEqual(cylinder.GetDensity(), density));
    BOOST_CHECK(CheckDoublesAreEqual(cylinder.GetVolume(), M_PI * pow(radius, 2) * height));
    BOOST_CHECK(CheckDoublesAreEqual(cylinder.GetMass(), cylinder.GetDensity() * cylinder.GetVolume()));
}

BOOST_AUTO_TEST_CASE(InvalidCylinderDoesntCreated)
{
    BOOST_CHECK_THROW(CCylinder(0, 1), invalid_argument);
    BOOST_CHECK_THROW(CCylinder(-1, 1), invalid_argument);

    BOOST_CHECK_THROW(CCylinder(1, 0), invalid_argument);
    BOOST_CHECK_THROW(CCylinder(1, -1), invalid_argument);

    BOOST_CHECK_NO_THROW(CCylinder(0.1, 0.1));
}

BOOST_AUTO_TEST_CASE(CylinderStringRepresentation)
{
    ostringstream strm;
    strm << "-- Cylinder --" << endl <<
        "Radius: " << cylinder.GetRadius() << endl <<
        "Height: " << cylinder.GetHeight() << endl <<
        "Volume: " << cylinder.GetVolume() << endl <<
        "Density: " << cylinder.GetDensity() << endl <<
        "Mass: " << cylinder.GetMass() << endl;

    BOOST_CHECK(cylinder.ToString() == strm.str());
}

BOOST_AUTO_TEST_SUITE_END()