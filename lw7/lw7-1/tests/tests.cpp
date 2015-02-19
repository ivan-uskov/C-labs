#include "stdafx.h"
#include "../equation/EquationSolve.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(Solve4Tests)

BOOST_AUTO_TEST_CASE(CatchExceptionIf_A_CoefZero)
{
    BOOST_CHECK_THROW(Solve3(0, 1, 1, 1), invalid_argument);
    BOOST_CHECK_NO_THROW(Solve3(1, 1, 1, 1));
    BOOST_CHECK_NO_THROW(Solve3(-1, 1, 1, 1));
    BOOST_CHECK_NO_THROW(Solve3(1.3, 1, 1, 1));
    BOOST_CHECK_NO_THROW(Solve3(-1.3, 1, 1, 1));
}

BOOST_AUTO_TEST_CASE(OneRealRoot)
{
    auto solution = Solve3(1, 1, 1, 1);
    BOOST_CHECK(DblsEqualy(solution.numRoots, 1));
    BOOST_CHECK(DblsEqualy(solution.roots[0], -1));

    // Q < 0
    solution = Solve3(1, 0, 1, 0);
    BOOST_CHECK(DblsEqualy(solution.numRoots, 1));
    BOOST_CHECK(DblsEqualy(solution.roots[0], 0));

    // Q > 0
    solution = Solve3(1, 9, 1, 1);
    BOOST_CHECK(DblsEqualy(solution.numRoots, 1));
    BOOST_CHECK(DblsEqualy(Round(solution.roots[0], 3), -8.9));

    // Q == 0
    solution = Solve3(1, 6, 12, 1);
    BOOST_CHECK(DblsEqualy(solution.numRoots, 1));
    BOOST_CHECK(DblsEqualy(Round(solution.roots[0], 3), Round(-0.087, 3)));
}

BOOST_AUTO_TEST_CASE(TwoRealRoots)
{
    auto solution = Solve3(1, 0, 0, 0);

    BOOST_CHECK(DblsEqualy(solution.numRoots, 2));
    BOOST_CHECK(DblsEqualy(solution.roots[0], 0));
    BOOST_CHECK(DblsEqualy(solution.roots[1], 0));

    solution = Solve3(1, 1, 0, 0);

    BOOST_CHECK(DblsEqualy(solution.numRoots, 2));
    BOOST_CHECK(DblsEqualy(solution.roots[0], 0));
    BOOST_CHECK(DblsEqualy(solution.roots[1], -1));
}

BOOST_AUTO_TEST_CASE(ThreeRealRoots)
{
    auto solution = Solve3(1, -4, 1, 1);

    BOOST_CHECK(DblsEqualy(solution.numRoots, 3));
    BOOST_CHECK(DblsEqualy(Round(solution.roots[0], 3), Round(-0.377, 3)));
    BOOST_CHECK(DblsEqualy(Round(solution.roots[1], 3), Round(3.6510, 3)));
    BOOST_CHECK(DblsEqualy(Round(solution.roots[2], 3), Round(0.726, 3)));
}

BOOST_AUTO_TEST_SUITE_END()
