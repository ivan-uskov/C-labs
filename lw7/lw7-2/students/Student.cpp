#include "stdafx.h"
#include "Student.h"

using namespace std;

namespace
{
    bool StringHasSpaces(string const& str)
    {
        return string::npos != str.find(' ');
    }

    bool AgeNotForStudent(unsigned age)
    {
        return !((14 <= age) && (age <= 60));
    }
};

CStudent::CStudent(unsigned age, string const& name, string const& surname, string const& patronymic)
{
    AssignAge(age);
    AssignFullName(name, surname, patronymic);
}

bool CStudent::Rename(std::string const& name, std::string const& surname, std::string const& patronymic)
{
    bool isRenamed = true;

    try
    {
        AssignFullName(name, surname, patronymic);
    }
    catch (exception const&)
    {
        isRenamed = false;
    }

    return isRenamed;
}

void CStudent::SetAge(unsigned age)
{
    if (age < m_age)
    {
        throw domain_error("Age can not be changed downward!");
    }

    AssignAge(age);
}

std::string const& CStudent::GetName()const
{
    return m_name;
}

std::string const& CStudent::GetSurname()const
{
    return m_surname;
}

std::string const& CStudent::GetPatronymic()const
{
    return m_patronymic;
}

unsigned CStudent::GetAge()const
{
    return m_age;
}

// private

void CStudent::AssignFullName(std::string name, std::string surname, std::string patronymic)
{
    if (name.empty() || StringHasSpaces(name))
    {
        throw invalid_argument("Name is incorrect!");
    }

    if (surname.empty() || StringHasSpaces(surname))
    {
        throw invalid_argument("Surname is incorrect!");
    }

    if (StringHasSpaces(patronymic))
    {
        throw invalid_argument("Patronymic is incorrect!");
    }

    m_name = move(name);
    m_surname = move(surname);
    m_patronymic = move(patronymic);
}

void CStudent::AssignAge(unsigned age)
{
    if (AgeNotForStudent(age))
    {
        throw out_of_range("This age not for student!");
    }

    m_age = age;
}