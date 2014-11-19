#include "stdafx.h"
#include "MazeIO.h"


CMazeIO::CMazeIO(const char * inputFileName, const char * outputFileName)
{
    OpenInputFile(inputFileName);
    OpenOutputFile(outputFileName);
}


CMazeIO::~CMazeIO()
{
}

/* Private methods */

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
