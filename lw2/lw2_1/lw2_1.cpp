#include "stdafx.h"

const int PARAMS_COUNT = 2;
const int FIRST_LINE_NIMBER = 1;

bool PrintSubStrings(std::ifstream * input, char* string)
{
    bool matchesFounded = false;
    int stringCount = FIRST_LINE_NIMBER;

    std::string search(string);
    std::string currStr;

    while (!(*input).eof())
    {
        std::getline(*input, currStr);
        std::size_t found = currStr.find(search);
        if (found != std::string::npos)
        {
            std::cout << stringCount << "\n";
            matchesFounded = true;
        }
        ++stringCount;
    }
    return matchesFounded;
}

int main(int argc, char * argv[])
{
    if (argc < PARAMS_COUNT)
    {
        printf("Expected arguments: [input_file] [outputfile]\n");
        return 1;
    }

    std::ifstream input(argv[1]);

    if (input.bad())
    {
        std::cout << "Input file doesn't exists!\n";
        return 1;
    }
    
    bool stringsFounded = PrintSubStrings(&input, argv[2]);
    if (!stringsFounded)
    {
        std::cout << "Text not found\n";
    }

    return stringsFounded ? 0 : 1;
}