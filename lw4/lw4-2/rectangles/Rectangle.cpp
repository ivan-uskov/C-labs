#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

int MakePositive(const int num)
{
    return max(num, 0);
}

CRectangle::CRectangle(const int left, const int top, const int width, const int height)
    : m_left(left)
    , m_top(top)
    , m_width(MakePositive(width))
    , m_height(MakePositive(height))
{
}

CRectangle::~CRectangle()
{
}

/* Public methods */

void CRectangle::Move(const int dx, const int dy)
{
    m_left = m_left + dx;
    m_top = m_top + dy;
}

void CRectangle::Scale(const int sx, const int sy)
{
    if (sx > 0)
    {
        m_width = m_width * sx;
    }

    if (sy > 0)
    {
        m_height = m_height * sy;
    }
}

bool CRectangle::Intersect(CRectangle const& other)
{
    bool intersects = !(m_top > other.GetBottom() || 
        GetBottom() < other.GetTop() || 
        GetRight() < other.GetLeft() || 
        m_left > other.GetRight());

    if (intersects)
    {
        int bottom = GetBottom();
        int right = GetRight();

        SetTop( max(GetTop(), other.GetTop()) );
        SetLeft( max(GetLeft(), other.GetLeft()) );
        SetBottom( min(bottom, other.GetBottom()) );
        SetRight( min(right, other.GetRight()) );
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }

    return intersects;
}

int CRectangle::GetArea()const
{
    return m_width * m_height;
}

int CRectangle::GetPerimeter()const
{
    return (m_width + m_height) * 2;
}

//-----------------------------
// Properties

//----Access----

int CRectangle::GetLeft()const
{
    return m_left;
}

int CRectangle::GetRight()const
{
    return m_left + m_width;
}

int CRectangle::GetTop()const
{
    return m_top;
}

int CRectangle::GetBottom()const
{
    return m_top + m_height;
}

int CRectangle::GetWidth()const
{
    return m_width;
}

int CRectangle::GetHeight()const
{
    return m_height;
}

// -------Setters--------

void CRectangle::SetLeft(const int left)
{
    m_left = MakePositive(left);
}

void CRectangle::SetRight(const int right)
{
    if (right > m_left)
    {
        m_width = right - m_left;
    }
}

void CRectangle::SetTop(const int top)
{
    m_top = MakePositive(top);
}

void CRectangle::SetBottom(const int bottom)
{
    if (bottom > m_top)
    {
        m_height = bottom - m_top;
    }
}

void CRectangle::SetWidth(const int width)
{
    m_width = MakePositive(width);
}

void CRectangle::SetHeight(const int height)
{
    m_height = MakePositive(height);
}