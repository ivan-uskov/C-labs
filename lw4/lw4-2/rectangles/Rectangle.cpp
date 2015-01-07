#include "stdafx.h"
#include "Rectangle.h"

using namespace std;

int MakePositive(const int num)
{
    return num > 0 ? num : 0;
}

bool IsNumInRange(pair<int, int> const& range, const int num)
{
    return range.first <= num && num <= range.second;
}

bool IsRectangleIncludePoint(CRectangle const& rec, pair<int, int> point)
{
    return IsNumInRange({ rec.GetLeft(), rec.GetRight() }, point.first) &&
        IsNumInRange({ rec.GetTop(), rec.GetBottom() }, point.second);
}

CRectangle::CRectangle(const int left, const int top, const int width, const int height)
    : m_left(MakePositive(left))
    , m_top(MakePositive(top))
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
    m_left = MakePositive(m_left + dx);
    m_top = MakePositive(m_top + dy);
}

void CRectangle::Scale(const int sx, const int sy)
{
    m_width = MakePositive(m_width + sx);
    m_height = MakePositive(m_height + sy);
}

bool CRectangle::Intersect(CRectangle const& other)
{
    const int top = GetTop();
    const int left = GetLeft();
    const int right = GetRight();
    const int bottom = GetBottom();

    bool isIntersect = IsRectangleIncludePoint(other, { left, top }) ||
        IsRectangleIncludePoint(other, { left, bottom }) ||
        IsRectangleIncludePoint(other, { right, top })   ||
        IsRectangleIncludePoint(other, { right, bottom });

    if (isIntersect)
    {
        SetTop( min(top, other.GetTop()) );
        SetLeft( max(left, other.GetLeft()) );
        SetBottom( max(bottom, other.GetBottom()) );
        SetRight( min(right, other.GetRight()) );
    }
    else
    {
        m_width = 0;
        m_height = 0;
    }

    return isIntersect;
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