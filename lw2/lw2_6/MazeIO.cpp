#include "stdafx.h"
#include "MazeIO.h"

using namespace std;

CMazeIO::CMazeIO(const char * inputFileName, const char * outputFileName)
{
    OpenInputFile(inputFileName);

    if (!IsError())
    {
        OpenOutputFile(outputFileName);
    }
}


CMazeIO::~CMazeIO()
{
    m_Input.close();
    m_Output.close();
}

/* Public methods */

CMazeIO::Field CMazeIO::ReadMaze(ifstream & input)
{
    string buffStr;
    while (!input.eof())
    {
        getline(input, buffStr);
        //if (!AddLabyrinthLine(buffStr, labyrinth))
    }

    //if (labyrinth.wayBorder.start == nullptr || labyrinth.wayBorder.end == nullptr)
    {
      //  errorCode = ErrorCodeType::FewBorderPoints;
        //return false;
    }
    //return true;
}

/* Private methods */

bool ReadLine(string const& sourse, LabyrinthType & labyrinth)
{
    vector<char> newLine;
    //PointType ** borderPoint;
    for (auto it = sourse.begin(); it != sourse.end(); ++it)
    {
        newLine.push_back(*it);
      //  borderPoint = GetBorderPointBySym(*it, labyrinth);

        if (borderPoint != nullptr)
        {
            if (*borderPoint != nullptr)
            {
                return false;
            }

            *borderPoint = new PointType;
            (*borderPoint)->x = it - sourse.begin();
            (*borderPoint)->y = labyrinth.field.size();
        }
    }
    labyrinth.field.push_back(newLine);
    return true;
}

void CMazeIO::OpenInputFile(const char* fileName)
{
    m_Input.open(fileName);
    if (m_Input.bad())
    {
        m_Error = Errors::OpenInputFile;
    }
}

void CMazeIO::OpenOutputFile(const char* fileName)
{
    m_Output.open(fileName);
    if (m_Output.bad())
    {
        m_Error = Errors::OpenOutputFile;
    }
}

bool CMazeIO::IsError()const
{
    return m_Error == Errors::None;
}
