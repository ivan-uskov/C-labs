#include "stdafx.h"
#include "../list/MyList.h"

using namespace std;
using namespace std::placeholders;

namespace
{
    struct EmptyListFixure
    {
        CMyList<int> list;
        CMyList<int> const & constList = list;
    };

    template <typename T>
    bool operator == (const CMyList<T> & lhs, const std::list<T> & rhs)
    {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
}

BOOST_AUTO_TEST_SUITE(default_contructor)

BOOST_AUTO_TEST_CASE(default_constructor_creates_empty_list_with_size_0)
{
    auto list = CMyList<int>();
    BOOST_CHECK(list.IsEmpty());
    BOOST_CHECK_EQUAL(list.GetSize(), 0);
}

struct ThrowErrorInDefaultConstructor
{
    ThrowErrorInDefaultConstructor()
    {
        throw runtime_error("from default constructor");
    }
};

BOOST_AUTO_TEST_CASE(default_constructor_does_not_create_empty_values)
{
    BOOST_CHECK_NO_THROW(CMyList<ThrowErrorInDefaultConstructor>());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(empty_list_iterator, EmptyListFixure)

BOOST_AUTO_TEST_CASE(cbegin_equals_to_begin)
{
    BOOST_CHECK(list.begin() == constList.begin());
    BOOST_CHECK(list.begin() == list.cbegin());
}

BOOST_AUTO_TEST_CASE(cend_equals_to_end)
{
    BOOST_CHECK(list.end() == constList.end());
    BOOST_CHECK(list.end() == list.cend());
}

BOOST_AUTO_TEST_CASE(begin_on_empty_list_equals_end_iterator)
{
    BOOST_CHECK(list.begin() == list.end());
    BOOST_CHECK(constList.begin() == constList.end());
    BOOST_CHECK(list.cbegin() == list.cend());

    BOOST_CHECK(list.rbegin() == list.rend());
    BOOST_CHECK(constList.rbegin() == constList.rend());
    BOOST_CHECK(list.crbegin() == list.crend());
}

BOOST_AUTO_TEST_CASE(decrement_begin_iterator_throws_logic_error)
{
    auto CheckThrowLogicError = [](auto && it) {
        BOOST_CHECK_THROW(--it, logic_error);
        BOOST_CHECK_THROW(it--, logic_error);
    };

    CheckThrowLogicError(list.begin());
    CheckThrowLogicError(list.cbegin());
    CheckThrowLogicError(constList.begin());
    CheckThrowLogicError(list.rbegin());
    CheckThrowLogicError(list.crbegin());
    CheckThrowLogicError(constList.rbegin());
}

BOOST_AUTO_TEST_CASE(increment_begin_iterator_throws_logic_error)
{
    auto CheckThrowLogicError = [](auto && it) {
        BOOST_CHECK_THROW(++it, logic_error);
        BOOST_CHECK_THROW(it++, logic_error);
    };

    CheckThrowLogicError(list.end());
    CheckThrowLogicError(list.cend());
    CheckThrowLogicError(constList.end());
    CheckThrowLogicError(list.rend());
    CheckThrowLogicError(list.crend());
    CheckThrowLogicError(constList.rend());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(emplace_to_list, EmptyListFixure)

BOOST_AUTO_TEST_CASE(emplace_to_list_increase_size_by_1)
{
    auto it = list.Emplace(list.cend(), 42);
    BOOST_CHECK_EQUAL(list.GetSize(), 1);

    list.Emplace(it, 43);
    BOOST_CHECK_EQUAL(list.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(emplace_to_list_returns_iterator_to_inserted_element)
{
    auto it = list.Emplace(list.cend(), 42);
    BOOST_CHECK_EQUAL(*it, 42);

    it = list.Emplace(it, 2);
    BOOST_CHECK_EQUAL(*it, 2);
}

BOOST_AUTO_TEST_CASE(emplace_to_end_creates_elements_coherently)
{
    list.Emplace(list.cend(), 1);
    list.Emplace(list.cend(), 2);
    list.Emplace(list.cend(), 3);

    BOOST_CHECK((list == std::list<int>{1, 2, 3}));
}

BOOST_AUTO_TEST_CASE(emplace_to_begin_creates_elements_reversed_after_first)
{
    list.Emplace(list.cbegin(), 1);
    list.Emplace(list.cbegin(), 2);
    list.Emplace(list.cbegin(), 3);
    list.Emplace(list.cbegin(), 4);

    BOOST_CHECK((list == std::list<int>{1, 4, 3, 2}));
}

BOOST_AUTO_TEST_SUITE_END()

struct ListWithSeveralIntsFixture : public EmptyListFixure
{
    ListWithSeveralIntsFixture()
    {
        list.Emplace(list.cend(), 1);
        list.Emplace(list.cend(), 2);
        list.Emplace(list.cend(), 3);
        list.Emplace(list.cend(), 4);
    }

    const size_t listInitialSize = 4;
};

BOOST_FIXTURE_TEST_SUITE(list_iterator, ListWithSeveralIntsFixture)

BOOST_AUTO_TEST_CASE(begin_iterator_refers_to_first_element)
{
    BOOST_CHECK_EQUAL(*list.begin(), 1);
    BOOST_CHECK_EQUAL(*list.cbegin(), 1);
    BOOST_CHECK_EQUAL(*constList.begin(), 1);
}

BOOST_AUTO_TEST_CASE(end_iterator_refers_to_node_after_last_element)
{
    BOOST_CHECK_EQUAL(*(--list.end()), 4);
    BOOST_CHECK_EQUAL(*(--list.cend()), 4);
    BOOST_CHECK_EQUAL(*(--constList.end()), 4);
}

BOOST_AUTO_TEST_CASE(old_end_iterator_stay_end_after_emplace_back)
{
    auto it = list.end();
    --it;
    BOOST_CHECK_EQUAL(*it, 4);
    ++it;
    list.Emplace(list.cend(), 42);
    --it;
    BOOST_CHECK_EQUAL(*it, 42);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(erase_from_list, ListWithSeveralIntsFixture)

BOOST_AUTO_TEST_CASE(erase_element_decrease_size_by_1)
{
    list.Erase(list.begin());
    BOOST_CHECK_EQUAL(list.GetSize(), listInitialSize - 1);

    list.Erase(list.begin());
    BOOST_CHECK_EQUAL(list.GetSize(), listInitialSize - 2);
}

BOOST_AUTO_TEST_CASE(erase_begin_element_remove_first_element)
{
    list.Erase(list.begin());
    BOOST_CHECK((list == std::list<int>{2, 3, 4}));
}

BOOST_AUTO_TEST_CASE(erase_pre_end_element_remove_one_element_from_back)
{
    list.Erase(--list.end());
    BOOST_CHECK((list == std::list<int>{1, 2, 3}));
}

BOOST_AUTO_TEST_CASE(erase_range_of_element_from_begin_to_middle)
{
    list.Erase(list.begin(), --(--list.end()));
    BOOST_CHECK((list == std::list<int>{3, 4}));
    BOOST_CHECK_EQUAL(list.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(erase_range_of_element_from_middle_to_end)
{
    list.Erase(++(++list.begin()), list.end());
    BOOST_CHECK((list == std::list<int>{1, 2}));
    BOOST_CHECK_EQUAL(list.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(erase_range_of_element_in_middle)
{
    list.Erase(++list.begin(), --list.end());
    BOOST_CHECK((list == std::list<int>{1, 4}));
    BOOST_CHECK_EQUAL(list.GetSize(), 2);
}

BOOST_AUTO_TEST_CASE(clear_remove_all_elements)
{
    list.Clear();
    BOOST_CHECK(list.IsEmpty());
    BOOST_CHECK_EQUAL(list.GetSize(), 0);
    BOOST_CHECK((list.begin() == list.end()));
}

BOOST_AUTO_TEST_SUITE_END()