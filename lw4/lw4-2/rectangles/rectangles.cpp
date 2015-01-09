#include "stdafx.h"
#include "Rectangle.h"
#include "Canvas.h"

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

void FillRectangle(CRectangle const& rect, char code, CCanvas & canvas)
{
    for (int y = rect.GetTop(); y <= rect.GetBottom(); ++y)
    {
        for (int x = rect.GetLeft(); x <= rect.GetRight(); ++x)
        {
            canvas.SetPixel(x, y, code);
        }
    }
}

void ProcessRectangles(ifstream & rec1Input, ifstream & rec2Input, CCanvas & canvas)
{
    cout << "Rectangle 1 :" << endl;
    auto rec1 = ReadRectangle(rec1Input);
    PrintRectangleInfo(rec1);
    FillRectangle(rec1, '+', canvas);

    cout << "Rectangle 2 :" << endl;
    auto rec2 = ReadRectangle(rec2Input);
    PrintRectangleInfo(rec2);
    FillRectangle(rec2, '-', canvas);

    cout << "Intersect rectangle:" << endl;
    rec1.Intersect(rec2);
    PrintRectangleInfo(rec1);
    FillRectangle(rec1, '#', canvas);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Usage: [First rectangle file] [Second rectangle file] [Canvas file]?" << endl;
        return 1;
    }

    ifstream rec1Input(argv[1]);
    ifstream rec2Input(argv[2]);
    if (rec1Input.bad() || rec2Input.bad())
    {
        cout << "Can't open rectangle files!" << endl;
        return 1;
    }

    CCanvas canvas(60, 20);

    ProcessRectangles(rec1Input, rec2Input, canvas);

    ofstream output;

    if (argc > 3 && string(argv[3]) != "")
    {
        ofstream output(argv[3]);
        canvas.Write(output);
    }
    else
    {
        canvas.Write(cout);
    }

    return 0;
}

