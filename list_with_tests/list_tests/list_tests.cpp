#include "stdafx.h"
#include "../list/List.h"

using namespace std;
using namespace std::placeholders;

template <typename T1, typename T2, typename T3>
void compare(T1 stdIt, T2 myIt, T3 myItEnd)
{
    for (; myIt != myItEnd; ++myIt, ++stdIt)
    {
        BOOST_CHECK_EQUAL(*myIt, *stdIt);
    }
};

template <typename T>
void verifyEqual(const list<T> & stdList, const List<T> & list)
{
    BOOST_CHECK_EQUAL(stdList.size(), list.size());

    compare(stdList.begin(), list.begin(), list.end());
    compare(stdList.rbegin(), list.rbegin(), list.rend());
}

struct FixtureWithMyList
{
    List<int> myInts = { 5, 6, 14, 9, 10 };
    const List<int> & myIntsConstRef = myInts;
};

struct FixtureWithMyListAndStlList : public FixtureWithMyList
{
    std::list<int> stdInts = { 5, 6, 14, 9, 10 };
};

BOOST_FIXTURE_TEST_SUITE(ListTests, FixtureWithMyListAndStlList)

    BOOST_AUTO_TEST_CASE(TestDefaultConstruct)
    {
        BOOST_CHECK_NO_THROW(List<int>());
    }

    BOOST_AUTO_TEST_CASE(TestConstructFromIterators)
    {
        auto list = List<int>(stdInts.begin(), stdInts.end());

        verifyEqual(stdInts, myInts);
    }

    BOOST_AUTO_TEST_CASE(TestConstructFromInitializerList)
    {
        verifyEqual(stdInts, myInts);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(IteratorsTests, FixtureWithMyList)

    BOOST_AUTO_TEST_CASE(TestBeginDereference)
    {
        BOOST_CHECK_EQUAL(*myInts.begin(), 5);
    }

    BOOST_AUTO_TEST_CASE(TestEnd)
    {
        List<int> list = { 5, 6 };
        auto end = list.end();
        BOOST_CHECK_EQUAL(*(--end), 6);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(InsertToMiddleTests, FixtureWithMyListAndStlList)

    BOOST_AUTO_TEST_CASE(TestCopyOneInsert)
    {
        myInts.insert(++myInts.cbegin(), 7);
        BOOST_CHECK((myInts == List<int>{ 5, 6, 7, 14, 9, 10 }));
    }

    BOOST_AUTO_TEST_CASE(TestCopyManyInsert)
    {
        myInts.insert(++(++myInts.cbegin()), 5, 7);
        BOOST_CHECK((myInts == List<int>{ 5, 6, 14, 7, 7, 7, 7, 7, 9, 10 }));
    }

    BOOST_AUTO_TEST_CASE(TestRangeInsert)
    {
        myInts.insert(++(++myInts.cbegin()), stdInts.begin(), stdInts.end());
        BOOST_CHECK((myInts == List<int>{ 5, 6, 14, 5, 6, 14, 9, 10, 9, 10 }));
    }

    BOOST_AUTO_TEST_CASE(TestMoveInsert)
    {
        List<unique_ptr<int>> list;
        BOOST_CHECK_NO_THROW(list.emplace(list.cend(), make_unique<int>(5)));
        BOOST_CHECK_EQUAL(list.size(), 1);
        BOOST_CHECK_EQUAL(**list.begin(), 5);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(CommonFunctionsTests, FixtureWithMyList)

    BOOST_AUTO_TEST_CASE(TestClear)
    {
        myInts.clear();
        BOOST_CHECK_EQUAL(myInts.size(), 0);
        BOOST_CHECK(myInts == List<int>());
    }

    BOOST_AUTO_TEST_CASE(TestFrontElement)
    {
        BOOST_CHECK_EQUAL(myInts.front(), 5);
        BOOST_CHECK_EQUAL(myIntsConstRef.front(), 5);
        myInts.clear();
        BOOST_CHECK_THROW(myInts.front(), std::logic_error);
        BOOST_CHECK_THROW(myIntsConstRef.front(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestBackElement)
    {
        BOOST_CHECK_EQUAL(myInts.back(), 10);
        BOOST_CHECK_EQUAL(myIntsConstRef.back(), 10);
        myInts.clear();
        BOOST_CHECK_THROW(myInts.back(), std::logic_error);
        BOOST_CHECK_THROW(myIntsConstRef.back(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestSwap)
    {
        auto anotherInts = List<int>{ 4, 3, 2, 1 };
        BOOST_CHECK_NO_THROW(anotherInts.swap(myInts));
        BOOST_CHECK((myInts == List<int>{ 4, 3, 2, 1 }));
        BOOST_CHECK((anotherInts == List<int>{ 5, 6, 14, 9, 10 }));
    }

    BOOST_AUTO_TEST_CASE(TestPopBack)
    {
        auto ints = List<int>{ 4, 3, 2, 1 };
        BOOST_CHECK_EQUAL(ints.size(), 4);
        BOOST_CHECK_EQUAL(ints.back(), 1);
        BOOST_CHECK_NO_THROW(ints.pop_back());
        BOOST_CHECK_EQUAL(ints.size(), 3);
        BOOST_CHECK_EQUAL(ints.back(), 2);
        BOOST_CHECK_NO_THROW(ints.pop_back());
        BOOST_CHECK_EQUAL(ints.size(), 2);
        BOOST_CHECK_EQUAL(ints.back(), 3);
        BOOST_CHECK_NO_THROW(ints.pop_back());
        BOOST_CHECK_EQUAL(ints.size(), 1);
        BOOST_CHECK_EQUAL(ints.back(), 4);
        BOOST_CHECK_NO_THROW(ints.pop_back());
        BOOST_CHECK_EQUAL(ints.size(), 0);
        BOOST_CHECK_THROW(ints.back(), std::logic_error);
        BOOST_CHECK_THROW(ints.pop_back(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestPopFront)
    {
        auto ints = List<int>{ 4, 3, 2, 1 };
        BOOST_CHECK_EQUAL(ints.size(), 4);
        BOOST_CHECK_EQUAL(ints.front(), 4);
        BOOST_CHECK_NO_THROW(ints.pop_front());
        BOOST_CHECK_EQUAL(ints.size(), 3);
        BOOST_CHECK_EQUAL(ints.front(), 3);
        BOOST_CHECK_NO_THROW(ints.pop_front());
        BOOST_CHECK_EQUAL(ints.size(), 2);
        BOOST_CHECK_EQUAL(ints.front(), 2);
        BOOST_CHECK_NO_THROW(ints.pop_front());
        BOOST_CHECK_EQUAL(ints.size(), 1);
        BOOST_CHECK_EQUAL(ints.front(), 1);
        BOOST_CHECK_NO_THROW(ints.pop_front());
        BOOST_CHECK_EQUAL(ints.size(), 0);
        BOOST_CHECK_THROW(ints.front(), std::logic_error);
        BOOST_CHECK_THROW(ints.pop_front(), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(TestEmplaceFront)
    {
        auto myIntsOldSize = myInts.size();
        myInts.emplace_front(2);
        BOOST_CHECK_EQUAL(myInts.front(), 2);
        BOOST_CHECK_EQUAL(myInts.size(), myIntsOldSize + 1);
    }

    BOOST_AUTO_TEST_CASE(EndIteratorIncrementThrowsLogicError)
    {
        BOOST_CHECK_THROW(++myInts.end(), std::logic_error);
        BOOST_CHECK_THROW(myInts.end()++, std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(BeginIteratorDecrementThrowsLogicError)
    {
        BOOST_CHECK_THROW(--myInts.begin(), std::logic_error);
        BOOST_CHECK_THROW(myInts.begin()--, std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(CheckEndIteratorAlwaysEndIterator)
    {
        List<int> list{ 1, 2, 3, 4, 5 };
        auto i = list.end();
        --i;
        BOOST_CHECK_EQUAL(*i, 5);
        ++i;
        list.push_back(42);
        --i;
        BOOST_CHECK_EQUAL(*i, 42);
    }

BOOST_AUTO_TEST_SUITE_END()