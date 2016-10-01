#include "stdafx.h"
#include "JPSPathFinder.h"

using namespace std;

struct MyGrid
{
    static const char PATH  = '.';
    static const char WALL  = '#';
    static const char START = 'A';
    static const char END   = 'B';

    struct Point
    {
        unsigned x, y;
    };

    bool initialize(istream & in)
    {
        m_grid.reserve(100);
        string line;

        while (getline(in, line))
        {
            tryFindPoint(line, m_startPoint, START);
            tryFindPoint(line, m_endPoint, END);

            m_grid.push_back(line);
        }

        return m_startPoint && m_endPoint;
    }

    bool operator () (unsigned x, unsigned y) const
    {
        return hasPoint(x, y) && (m_grid[y][x] != WALL);
    }

    void set(unsigned x, unsigned y, char val)
    {
        if (hasPoint(x, y))
        {
            m_grid[y][x] = val;
        }
    }

    const JPS::Position & getStartPoint() const
    {
        return *m_startPoint;
    }

    const JPS::Position & getEndPoint() const
    {
        return *m_endPoint;
    }

    friend ostream & operator << (ostream & out, const MyGrid & grid);

private:
    bool hasPoint(unsigned x, unsigned y) const
    {
        return (y < m_grid.size()) && (x < m_grid[y].size());
    }

    void tryFindPoint(const string & line, unique_ptr<JPS::Position> & pointHolder, const char & symbol)
    {
        auto pointX = line.find(symbol);
        if (pointX != std::string::npos)
        {
            pointHolder = make_unique<JPS::Position>();
            pointHolder->x = pointX;
            pointHolder->y = m_grid.size();
        }
    };

    vector<string> m_grid;
    unique_ptr<JPS::Position> m_startPoint;
    unique_ptr<JPS::Position> m_endPoint;
};

ostream & operator << (ostream & out, const MyGrid & grid)
{
    ostream_iterator<string> outIt(out, "\n");
    copy(grid.m_grid.begin(), grid.m_grid.end(), outIt);

    return out;
}

int main(int argc, char const *argv[])
{
    MyGrid grid;
    if (!grid.initialize(cin))
    {
        cout << "Failed to find start or end point!" << endl;
        return 1;
    }

    JPS::PathVector path;
    auto start = grid.getStartPoint();
    auto end = grid.getEndPoint();
    unsigned mode = 1;

    if (!JPS::findPath(path, grid, start.x, start.y, end.x, end.y, mode))
    {
        cout << "Path not found!" << endl;
        return 1;
    }

    for_each(path.begin(), path.end(), [&](auto const& pathItem) {
        if ((pathItem != start) && (pathItem != end))
        {
            grid.set(pathItem.x, pathItem.y, MyGrid::PATH);
        }
    });

    cout << grid << endl;

    return 0;
}