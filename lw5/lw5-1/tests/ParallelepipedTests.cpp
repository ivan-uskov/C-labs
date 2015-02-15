#include "stdafx.h"
#include "../body_hierarchy/Parallelepiped.h"

using namespace std;

struct ParallelepipedTestsFixture
{
    double width, height, depth;
    double density;
    CParallelepiped parral;

    ParallelepipedTestsFixture()
        : width(2)
        , height(3)
        , depth(4)
        , density(2)
        , parral(width, height, depth, density)
    {}
};

BOOST_FIXTURE_TEST_SUITE(ParallelepipedTests, ParallelepipedTestsFixture)

BOOST_AUTO_TEST_CASE(NewParallelepiped)
{
    BOOST_CHECK(CheckDoublesAreEqual(parral.GetWidth(), width));
    BOOST_CHECK(CheckDoublesAreEqual(parral.GetHeight(), height));
    BOOST_CHECK(CheckDoublesAreEqual(parral.GetDepth(), depth));

    BOOST_CHECK(CheckDoublesAreEqual(parral.GetDensity(), density));
    BOOST_CHECK(CheckDoublesAreEqual(parral.GetVolume(), width * height * depth));
    BOOST_CHECK(CheckDoublesAreEqual(parral.GetWeight(), parral.GetDensity() * parral.GetVolume()));
}

BOOST_AUTO_TEST_CASE(InvalidParallelepipedDoesntCreated)
{
    BOOST_CHECK_THROW(CParallelepiped(0, 1, 1), invalid_argument);
    BOOST_CHECK_THROW(CParallelepiped(-1, 1, 1), invalid_argument);

    BOOST_CHECK_THROW(CParallelepiped(1, 0, 1), invalid_argument);
    BOOST_CHECK_THROW(CParallelepiped(1, -1, 1), invalid_argument);

    BOOST_CHECK_THROW(CParallelepiped(1, 1, 0), invalid_argument);
    BOOST_CHECK_THROW(CParallelepiped(1, 1, -1), invalid_argument);

    BOOST_CHECK_NO_THROW(CParallelepiped(0.1, 0.1, 0.1));
}

BOOST_AUTO_TEST_CASE(ParallelepipedStringRepresentation)
{
    ostringstream strm;
    strm << "-- Parallelepiped --\n" << "Volume: " << parral.GetVolume() << endl <<
        "Density: " << parral.GetDensity() << endl <<
        "Weight: " << parral.GetWeight() << endl;

    BOOST_CHECK(parral.ToString() == strm.str());
}

BOOST_AUTO_TEST_SUITE_END()

