#include "stdafx.h"
#include "../students/Student.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(CStudentTests)

BOOST_AUTO_TEST_CASE(NewStudentThrowExceptionByFIO)
{
    // Имя с пробелами
    BOOST_CHECK_THROW(CStudent(16, "Va s y a", "Ivanov"), invalid_argument);

    // Пустое имя
    BOOST_CHECK_THROW(CStudent(16, "", "Ivanov"), invalid_argument);

    // Фамилия с пробелами
    BOOST_CHECK_THROW(CStudent(16, "Vasya", "I va n ov"), invalid_argument);

    // Пустая фамилия
    BOOST_CHECK_THROW(CStudent(16, "Vasya", ""), invalid_argument);

    // Отчество с пробелами
    BOOST_CHECK_THROW(CStudent(16, "Vasya", "Ivanov", "Pe t r o vi ch"), invalid_argument);


    BOOST_CHECK_NO_THROW(CStudent(16, "Vasya", "Ivanov"));
    BOOST_CHECK_NO_THROW(CStudent(16, "Vasya", "Ivanov", "Petrovich"));
}

BOOST_AUTO_TEST_CASE(NewStudentThrowExceptionByAge)
{
    BOOST_CHECK_THROW(CStudent(13, "Vasya", "Ivanov"), out_of_range);
    BOOST_CHECK_NO_THROW(CStudent(14, "Vasya", "Ivanov"));

    BOOST_CHECK_THROW(CStudent(61, "Vasya", "Ivanov"), out_of_range);
    BOOST_CHECK_NO_THROW(CStudent(60, "Vasya", "Ivanov"));
}

BOOST_AUTO_TEST_CASE(GetNameReturnName)
{
    BOOST_CHECK_EQUAL(CStudent(15, "Vasya", "Ivanov").GetName(), "Vasya");
}

BOOST_AUTO_TEST_CASE(GetSurnameReturnName)
{
    BOOST_CHECK_EQUAL(CStudent(15, "Vasya", "Ivanov").GetSurname(), "Ivanov");
}

BOOST_AUTO_TEST_CASE(GetPatronymicReturnPatronymic)
{
    BOOST_CHECK_EQUAL(CStudent(15, "Vasya", "Ivanov").GetPatronymic(), "");
    BOOST_CHECK_EQUAL(CStudent(15, "Vasya", "Ivanov", "Ololoev").GetPatronymic(), "Ololoev");
    BOOST_CHECK_EQUAL(CStudent(15, "Vasya", "Ivanov", "").GetPatronymic(), "");
}

BOOST_AUTO_TEST_CASE(GetAgeReturnAge)
{
    BOOST_CHECK_EQUAL(CStudent(15, "Vasya", "Ivanov").GetAge(), 15);
}

BOOST_AUTO_TEST_CASE(RenameWithIncorrectArgsNotThrowAndSafeOldValues)
{
    {
        CStudent student(16, "Vasya", "Ivanov");
        // Имя с пробелами
        BOOST_CHECK_NO_THROW(student.Rename("Va s y a", "Ivanov"));
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }

    {
        CStudent student(16, "Vasya", "Ivanov");
        // Пустое имя
        BOOST_CHECK_NO_THROW(student.Rename("", "Ivanov"));
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }

    {
        CStudent student(16, "Vasya", "Ivanov");
        // Фамилия с пробелами
        BOOST_CHECK_NO_THROW(student.Rename("Vasya", "I va n ov"));
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }

    {
        CStudent student(16, "Vasya", "Ivanov");
        // Пустая фамилия
        BOOST_CHECK_NO_THROW(student.Rename("Vasya", ""));
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }

    {
        CStudent student(16, "Vasya", "Ivanov", "Petrovich");
        // Отчество с пробелами
        BOOST_CHECK_NO_THROW(student.Rename("Vasya", "Ivanov", "Pe t r o vi ch"));
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "Petrovich");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }
}

BOOST_AUTO_TEST_CASE(RenameChangeFullName)
{
    CStudent student(16, "Vasya", "Ivanov", "Petrovich");
    BOOST_CHECK(student.Rename("Ivan", "Petrov", "Ivanovich"));
    BOOST_CHECK_EQUAL(student.GetName(), "Ivan");
    BOOST_CHECK_EQUAL(student.GetSurname(), "Petrov");
    BOOST_CHECK_EQUAL(student.GetPatronymic(), "Ivanovich");
    BOOST_CHECK_EQUAL(student.GetAge(), 16);
}

BOOST_AUTO_TEST_CASE(SetAgeThrowErrorsAndSafeOldValue)
{
    // Can't Change age downward
    {
        CStudent student(16, "Vasya", "Ivanov");
        BOOST_CHECK_THROW(student.SetAge(15), domain_error);
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }

    // Can't change age more than 60
    {
        CStudent student(16, "Vasya", "Ivanov");
        BOOST_CHECK_THROW(student.SetAge(61), out_of_range);
        BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
        BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
        BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
        BOOST_CHECK_EQUAL(student.GetAge(), 16);
    }
}

BOOST_AUTO_TEST_CASE(SetAgeCorrectly)
{
    CStudent student(16, "Vasya", "Ivanov");
    BOOST_CHECK_NO_THROW(student.SetAge(20));
    BOOST_CHECK_EQUAL(student.GetName(), "Vasya");
    BOOST_CHECK_EQUAL(student.GetSurname(), "Ivanov");
    BOOST_CHECK_EQUAL(student.GetPatronymic(), "");
    BOOST_CHECK_EQUAL(student.GetAge(), 20);
}

BOOST_AUTO_TEST_SUITE_END()