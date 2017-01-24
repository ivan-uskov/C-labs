#include "stdafx.h"

using namespace std;

struct CPoint
{
    CPoint() = default;
    CPoint(int x, int y)
        : x(x)
        , y(y)
    {}

    int x;
    int y;
};

struct CLine
{
    CLine(const CPoint & from, const CPoint & to)
        : start(from)
        , end(to)
    {}

    CPoint start;
    CPoint end;
};

std::ostream & operator << (std::ostream & out, const CLine & line)
{
    out << "Draw Line (startX: " << line.start.x << ", startY: " << line.start.y << "; endX:" << line.end.x << ", endY: " << line.end.y << ")";
    return out;
}

// Холст, позволяющий рисовать графические примитивы
class ICanvas
{
public:
    virtual void DrawLine(const CLine & line) = 0;
    virtual ~ICanvas() {}
};

// Реализация холста, выполняющая вывод информации о рисуемых примитивах в stdout в виде:
// DrawLine:(<x0>, <y0>) - (<x1>, <y1>)
class CCanvas : public ICanvas
{
    CCanvas(std::ostream & out, bool isTextMode = false)
        : m_out(out)
        , m_isTextMode(isTextMode)
    {
        if (!m_isTextMode)
        {
            m_out << "<!DOCTYPE html><html><body><svg height=\"1000\" width=\"1000\">" << std::endl;
        }
    }

    ~CCanvas()
    {
        if (!m_isTextMode)
        {
            m_out << "</svg></body></html>" << std::endl;
        }
    }
public:
    void DrawLine(const CLine & line) override
    {
        if (m_isTextMode)
        {
            m_out << line << endl;
        }
        else
        {
            m_out << "<line style=\"stroke:rgb(255, 0, 0); stroke-width:2\" x1=\"" << line.start.x << "\" y1=\"" << line.start.y << "\" x2=\"" << line.end.x << "\" y2=\"" << line.end.y << "\"/>" << std::endl;
        }
    }

    static void DrawPicture(const std::string & location, function<void(ICanvas&)> && fn)
    {
        std::ofstream strm(location);
        CCanvas canvas(strm);
        fn(canvas);
    }

    static void DrawPictureText(std::ostream & out, function<void(ICanvas&)> && fn)
    {
        CCanvas canvas(out, true);
        fn(canvas);
    }

private:
    std::ostream & m_out;
    bool m_isTextMode = false;
};

// Интерфейс объектов, которые можно нарисовать на холсте
class ICanvasDrawable
{
public:
    virtual std::vector<CLine> getLines() const = 0;
    virtual ~ICanvasDrawable() = default;
};

// Прямоугольник, обладающий координатами верхнего левого угла, шириной и высотой
class CRectangle : public ICanvasDrawable
{
public:
    CRectangle(const CPoint & leftTop, int width, int height)
        : m_leftTop(leftTop)
        , m_width(width)
        , m_height(height)
    {}

    std::vector<CLine> getLines() const
    {
        return{
            CLine(m_leftTop, CPoint(m_leftTop.x + m_width, m_leftTop.y)), //left
            CLine(m_leftTop, CPoint(m_leftTop.x, m_leftTop.y + m_height)), //top
            CLine(CPoint(m_leftTop.x + m_width, m_leftTop.y), CPoint(m_leftTop.x + m_width, m_leftTop.y + m_height)), //right
            CLine(CPoint(m_leftTop.x, m_leftTop.y + m_height), CPoint(m_leftTop.x + m_width, m_leftTop.y + m_height)) //bottom
        };
    }

private:
    CPoint m_leftTop;
    int m_width;
    int m_height;
};

// Треугольник, задается координатами трех вершин
class CTriangle : public ICanvasDrawable
{
public:
    CTriangle(const CPoint & p1, const CPoint & p2, const CPoint & p3)
        : m_p1(p1)
        , m_p2(p2)
        , m_p3(p3)
    {}

    std::vector<CLine> getLines() const
    {
        return{
            CLine(m_p1, m_p2),
            CLine(m_p2, m_p3),
            CLine(m_p3, m_p1)
        };
    }

private:
    CPoint m_p1;
    CPoint m_p2;
    CPoint m_p3;
};

// Рисует картину picture на холсте canvas
void DrawPicture(ICanvas & canvas, const vector<shared_ptr<const ICanvasDrawable>> & picture)
{
    for (auto const& picElement : picture)
    {
        for (auto const& line : picElement->getLines())
        {
            canvas.DrawLine(line);
        }
    }
}

int main()
{
    /*
    Задание:
    При помощи имеющихся фигур описать домик
    "Нарисовать" его при помощи функции DrawPicture на "холсте"
      /\
     /  \
    /    \
    ------
    |    |
    |    |
    |    |
    ------
    */

    vector<shared_ptr<const ICanvasDrawable>> house;
    house.push_back(make_shared<CTriangle>(CPoint(300, 300), CPoint(450, 150), CPoint(600, 300)));
    house.push_back(make_shared<CRectangle>(CPoint(300, 300), 300, 200));

    CCanvas::DrawPicture("my-pic.html", [&house] (ICanvas & canvas) {
        DrawPicture(canvas, house);
    });
    CCanvas::DrawPictureText(cout, [&house](ICanvas & canvas) {
        DrawPicture(canvas, house);
    });

    return 0;
}
