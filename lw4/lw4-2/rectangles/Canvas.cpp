#include "stdafx.h"
#include "Canvas.h"

bool IsCharacterWriteble(char ch)
{
    return ch >= ' ';
}

CCanvas::CCanvas(unsigned width, unsigned height)
    : m_canvas(width * height, ' ')
    , m_width(width)
    , m_height(height)
{

}


CCanvas::~CCanvas()
{
}

/* Public methods */

unsigned CCanvas::GetWidth()const
{
    return m_width;
}

unsigned CCanvas::GetHeight()const
{
    return m_height;
}

void CCanvas::Clear(char code)
{
    transform(m_canvas.begin(), m_canvas.end(), m_canvas.begin(), [code](char ch){ return code; });
}

void CCanvas::SetPixel(int x, int y, char code)
{
    if (IsCharacterWriteble(code) && IsPixelExists(x, y))
    {
        m_canvas[GetPixelPosition(x, y)] = code;
    }
}

char CCanvas::GetPixel(int x, int y)const
{
    return IsPixelExists(x, y) ? m_canvas[GetPixelPosition(x, y)] : ' ';
}

void CCanvas::Write(std::ostream & ostream)const
{
    for (size_t i = 0; i < m_canvas.size(); ++i)
    {
        ostream << m_canvas[i];
        if ((i + 1) % m_width == 0 && i > 0)
        {
            ostream << std::endl;
        }
    }
}

/* Private methods */

bool CCanvas::IsPixelExists(unsigned x, unsigned y)const
{
    return GetPixelPosition(x, y) < (m_width * m_height);
}

unsigned CCanvas::GetPixelPosition(unsigned x, unsigned y)const
{
    return y * m_width + x;
}