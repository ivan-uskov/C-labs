#include "stdafx.h"
#include "../rectangles/Canvas.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct CanvasTestsFixture
{
    int width;
    int height;
    CCanvas canvas;

    CanvasTestsFixture()
        : canvas(width, height)
        , width(5)
        , height(3)
    {
    }
};

BOOST_FIXTURE_TEST_SUITE(CCanvasTests, CanvasTestsFixture)

BOOST_AUTO_TEST_CASE(NewCanvas)
{
    BOOST_CHECK_EQUAL(canvas.GetWidth(), width);
    BOOST_CHECK_EQUAL(canvas.GetHeight(), height);
}

BOOST_AUTO_TEST_CASE(VerifySetGetPixel)
{
    canvas.SetPixel(2, 2, 'k');
    BOOST_CHECK_EQUAL(canvas.GetPixel(2, 2), 'k');

    BOOST_CHECK_EQUAL(canvas.GetPixel(width - 1, height), 0);
    BOOST_CHECK_EQUAL(canvas.GetPixel(width, height - 1), 0);
    BOOST_CHECK_EQUAL(canvas.GetPixel(width, height), 0);
}

BOOST_AUTO_TEST_CASE(VerifyWriteClearToOstream)
{
    canvas.SetPixel(2, 2, '!');
    canvas.SetPixel(3, 2, '1');

    canvas.Clear('1');
    ostringstream ostrm;
    canvas.Write(ostrm);

    BOOST_CHECK_EQUAL(ostrm.str(), "11111\n11111\n11111\n");
}

BOOST_AUTO_TEST_CASE(VerifySetNotWritebleChar)
{
    ostringstream before, after;

    for (char ch = 0; ch < 20; ++ch)
    {
        before.clear();
        after.clear();
        canvas.Write(before);
        canvas.SetPixel(2, 2, ch);
        canvas.Write(after);

        BOOST_CHECK_EQUAL(before.str(), after.str());
    }
}


BOOST_AUTO_TEST_SUITE_END()