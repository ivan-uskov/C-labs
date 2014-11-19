#include "stdafx.h"

const char START_POINT_CHAR = 'A';
const char START_POINT_VAL = -1;
const char END_POINT_CHAR   = 'B';
const char WAY_ELT_CHAR    = '.';
const char WALL_CHAR       = '#';
const char FREE_SPACE_CHAR = ' ';
const char FREE_SPACE_VAL = NAN;
const char WALL_VAL = -1;
const char START_VAL = 0;
const int PARAMS_COUNT     = 3;

using namespace std;

struct PointType
{
    int x;
    int y;
};

struct WayBorderType
{
    PointType * start = nullptr;
    PointType * end   = nullptr;
};

struct LabyrinthType
{
    WayBorderType wayBorder;
    vector<vector<char>> field;
};

enum class ErrorCodeType
{
    WrongParamsNumber, 
    OpenFiles,
    WayNotExists,
    LotBorderPoints,
    FewBorderPoints
};

void PrintError(ErrorCodeType errorCode)
{
    switch (errorCode)
    {
        case ErrorCodeType::WrongParamsNumber:
        {
            cout << "Wrong parameters number!" << endl;
            break;
        }
        case ErrorCodeType::OpenFiles:
        {
            cout << "Can't open files!" << endl;
            break;
        }
        case ErrorCodeType::WayNotExists:
        {
            cout << "Way not exists!" << endl;
            break;
        }
        case ErrorCodeType::LotBorderPoints:
        {
            cout << "A lot of start/end points!" << endl;
            break;
        }
        case ErrorCodeType::FewBorderPoints:
        {
            cout << "Few of start/end points!" << endl;
            break;
        }
    }
}

PointType** GetBorderPointBySym(char ch, LabyrinthType & labyrinth)
{
    if (ch == START_POINT_CHAR)
    {
        return &labyrinth.wayBorder.start;
    }
    else if (ch == END_POINT_CHAR)
    {
        return &labyrinth.wayBorder.end;
    }
    return nullptr;
}

/*
    return false if found second start or end point
*/
bool AddLabyrinthLine(string const& sourse, LabyrinthType & labyrinth)
{
    vector<char> newLine;
    PointType ** borderPoint;
    for (auto it = sourse.begin(); it != sourse.end(); ++it)
    {
        newLine.push_back(*it);
        borderPoint = GetBorderPointBySym(*it, labyrinth);
        
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

bool ReadLabyrinth(ifstream & input, LabyrinthType & labyrinth, ErrorCodeType & errorCode)
{
    string buffStr;
    while (!input.eof())
    {
        getline(input, buffStr);
        if (!AddLabyrinthLine(buffStr, labyrinth))
        {
            errorCode = ErrorCodeType::LotBorderPoints;
            return false;
        }
    }
    if (labyrinth.wayBorder.start == nullptr || labyrinth.wayBorder.end == nullptr)
    {
        errorCode = ErrorCodeType::FewBorderPoints;
        return false;
    }
    return true;
}

bool CheckFreeCell(PointType point, vector<vector<char>> const* workField)
{
    return ((*workField).size() > point.y) && (point.y > 0) && 
           ((*workField).at(point.y).size() > point.x) && (point.x >= 0) && 
           (*workField)[point.y][point.x] == FREE_SPACE_VAL;
}

void FindFreeCells(PointType const& point, vector<vector<char>> * workField, vector<PointType> & wave2)
{
    if (CheckFreeCell({point.y + 1, point.x + 1}, workField))
    {
        (*workField)[point.y + 1][point.x + 1] = (*workField)[point.y][point.x] + 1;
        wave2.push_back({ point.y + 1, point.x + 1 });
    }

    if (CheckFreeCell({ point.y - 1, point.x - 1 }, workField))
    {
        (*workField)[point.y - 1][point.x - 1] = (*workField)[point.y][point.x] + 1;
        wave2.push_back({ point.y - 1, point.x - 1 });
    }

    if (CheckFreeCell({ point.y + 1, point.x - 1 }, workField))
    {
        (*workField)[point.y + 1][point.x - 1] = (*workField)[point.y][point.x] + 1;
        wave2.push_back({ point.y + 1, point.x - 1 });
    }

    if (CheckFreeCell({ point.y - 1, point.x + 1 }, workField))
    {
        (*workField)[point.y - 1][point.x + 1] = (*workField)[point.y][point.x] + 1;
        wave2.push_back({ point.y - 1, point.x + 1 });
    }
}

vector<PointType> * SelectWay(vector<vector<char>> const* workField, WayBorderType const& borderPoints)
{
    vector<PointType> * way = new vector<PointType>;
    PointType currPoint = *borderPoints.end;
    while ((currPoint.x != borderPoints.start->x) && (currPoint.y != borderPoints.start->y))
    {
        char currVal = (*workField)[currPoint.x][currPoint.y];
        if ((*workField)[currPoint.x + 1][currPoint.y + 1] - currVal == 1)
        {
            ++currPoint.x;
            ++currPoint.y;
        }

        if ((*workField)[currPoint.x - 1][currPoint.y - 1] - currVal == 1)
        {
            --currPoint.x;
            --currPoint.y;
        }

        if ((*workField)[currPoint.x + 1][currPoint.y - 1] - currVal == 1)
        {
            ++currPoint.x;
            --currPoint.y;
        }

        if ((*workField)[currPoint.x - 1][currPoint.y + 1] - currVal == 1)
        {
            --currPoint.x;
            ++currPoint.y;
        }
    }
    return way;
}

vector<PointType> * FindWay(vector<vector<char>> * workField, WayBorderType const& borderPoints)
{
    vector<PointType> wave1, wave2;
    wave1.push_back(*(borderPoints.start));

    while (wave1.size() > 0)
    {
        PointType point;
        for (auto it = wave1.begin(); it != wave1.end(); ++it)
        {
            point = *it;
            FindFreeCells(point, workField, wave2);
        }
        wave1.clear();
        for (auto it = wave2.rbegin(); it != wave2.rend(); ++it)
        {
            if ((it->y == borderPoints.end->y) && (it->x == borderPoints.end->x))
            {
                return SelectWay(workField, borderPoints);
            }
            wave1.push_back(*it);
        }
        wave2.clear();
    }
    return NULL;
}

vector<vector<char>>* CreateWorkField(vector<vector<char>> & field)
{
    vector<vector<char>>* workField = new vector<vector<char>>;
    for (auto itY = field.begin(); itY != field.end(); ++itY)
    {
        vector<char> newVec;
        
        for (auto itX = (*itY).begin(); itX != (*itY).end(); ++itX)
        {
            char newVal = FREE_SPACE_CHAR;

            if (*itX == WALL_CHAR)
            {
                newVal = WALL_VAL;
            }

            if (*itX == START_POINT_CHAR)
            {
                newVal = START_POINT_VAL;
            }

            newVec.push_back(newVal);
        }
        (*workField).push_back(newVec);
    }
    return workField;
}

bool AddWay(LabyrinthType & labyrinth)
{
    vector<vector<char>>* workField = CreateWorkField(labyrinth.field);

    auto way = FindWay(workField, labyrinth.wayBorder);
    if (way == nullptr)
    {
        return false;
    }

    for (auto it = (*way).begin(); it != (*way).end(); ++it)
    {
        labyrinth.field[(*it).y][(*it).x] = WAY_ELT_CHAR;
    }
    
    return true;
}

void PrintLabyrinth(ofstream & output, LabyrinthType const& labyrinth)
{
    for (auto itY = labyrinth.field.begin(); itY != labyrinth.field.end(); ++itY)
    {
        for (auto itX = (*itY).begin(); itX != (*itY).end(); ++itX)
        {
            output << *itX;
        }
        output << endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc < PARAMS_COUNT)
    {
        PrintError(ErrorCodeType::WrongParamsNumber);
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);
    if (input.bad() || output.bad())
    {
        PrintError(ErrorCodeType::OpenFiles);
        return 1;
    }

    LabyrinthType labyrinth;
    ErrorCodeType errorCode;
    if (!ReadLabyrinth(input, labyrinth, errorCode))
    {
        PrintError(errorCode);
        return 1;
    }

    if (!AddWay(labyrinth))
    {
        PrintError(ErrorCodeType::WayNotExists);
        return 1;
    }

    PrintLabyrinth(output, labyrinth);

    input.close();
    output.close();

    return 0;
}