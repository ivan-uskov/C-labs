#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

typedef void(Command)(CRectangle &);

istringstream GetLineStreamFromIstream(istream & input)
{
    string line;
    getline(input, line);
    return istringstream(line);
}

void ProcessCommand(CRectangle & rec, istringstream & cmdStrm)
{
    string cmdName;
    if (cmdStrm >> cmdName)
    {
        if (cmdName == "Scale")
        {
            int sx, sy;
            if (cmdStrm >> sx >> sy)
            {
                rec.Scale(sx, sy);
            }
        }
        else if (cmdName == "Move")
        {
            int dx, dy;
            if (cmdStrm >> dx >> dy)
            {
                rec.Move(dx, dy);
            }
        }
        else if (cmdName == "Rectangle")
        {
            int left, top, width, height;
            if (cmdStrm >> left >> top >> width >> height)
            {
                rec.SetLeft(left);
                rec.SetTop(top);
                rec.SetWidth(width);
                rec.SetHeight(height);
            }
        }
    }
}

CRectangle ReadRectangle(istream & input)
{
    CRectangle rec(0, 0, 0, 0);

    while (!input.eof())
    {
        ProcessCommand(rec, GetLineStreamFromIstream(input));
    }

    return rec;
}

void PrintRectangleInfo(CRectangle const& rectangle)
{
    cout << "\tLeft, top: (" << rectangle.GetLeft() << "; " << rectangle.GetTop() << ")" << endl;
    cout << "\tSize: " << rectangle.GetWidth() << " * " << rectangle.GetHeight() << endl;
    cout << "\tRight, bottom: (" << rectangle.GetRight() << "; " << rectangle.GetBottom() << ")" << endl;
    cout << "\tArea: " << rectangle.GetArea() << endl;
    cout << "\tPerimeter: " << rectangle.GetPerimeter() << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Usage: [First rectangle file] [Second rectangle file]" << endl;
        return 1;
    }

    ifstream firstRecFile(argv[1]);
    ifstream secondRecFile(argv[2]);
    if (firstRecFile.bad() || secondRecFile.bad())
    {
        cout << "Can't open rectangle files!" << endl;
        return 1;
    }

    cout << "Rectangle 1 :" << endl;
    auto rec1 = ReadRectangle(firstRecFile);
    PrintRectangleInfo(rec1);

    cout << "Rectangle 2 :" << endl;
    auto rec2 = ReadRectangle(secondRecFile);
    PrintRectangleInfo(rec2);

    return 0;
}

