#pragma once

class CMazeIO
{

public:

    static const char START_POINT =  0;
    static const char END_POINT   = -1;
    static const char WALL        = -2;
    static const char WAY         = -3;
    static const char FREE_SPACE  = -4;

    typedef struct Point
    {
        unsigned x, y;
    };
    typedef struct WayBorder
    {
        Point * start;
        Point * end;
    };

    typedef vector<vector<char>> Field;

    CMazeIO(const char * inputFileName, const char * outputFileName);
    ~CMazeIO();

    CMazeIO::Field CMazeIO::ReadMaze(std::ifstream & input);
    bool IsError()const;

private:

    const char START_POINT_CHAR = 'A';
    const char END_POINT_CHAR   = 'B';
    const char WALL_CHAR        = '#';
    const char WAY_CHAR         = '.';
    const char FREE_SPACE_CHAR  = ' ';

    enum class Errors
    {
        None,
        OpenInputFile,
        OpenOutputFile,
        UnexpectedSymbol
    };

    Errors m_Error = Errors::None;
    WayBorder m_WayBorder;
    Field m_Field;
    std::ifstream m_Input;
    std::ofstream m_Output;

    void OpenInputFile(const char* fileName);
    void OpenOutputFile(const char* fileName);
};

