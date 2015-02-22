#pragma once
#include <string>

class CStudent
{
public:

    CStudent(unsigned age, std::string const& name, std::string const& surname, std::string const& patronymic = std::string());

    std::string const& GetName()const;
    std::string const& GetSurname()const;
    std::string const& GetPatronymic()const;
    unsigned GetAge()const;

    void Rename(std::string const& name, std::string const& surname, std::string const& patronymic = std::string());
    void SetAge(unsigned age);

private:

    void AssignFullName(std::string name, std::string surname, std::string patronymic);
    void AssignAge(unsigned age);

private:

    unsigned m_age;
    std::string m_name;
    std::string m_surname;
    std::string m_patronymic;
};

