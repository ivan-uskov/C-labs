#pragma once
#include <vector>

class CCanvas
{
public:

    CCanvas(unsigned width, unsigned height);
    ~CCanvas();

    unsigned GetWidth()const;
    unsigned GetHeight()const;

    void Clear(char code = ' ');

    void SetPixel(int x, int y, char code);
    char GetPixel(int x, int y)const;
    void Write(std::ostream & ostream)const;

private:
    unsigned m_width, m_height;
    std::vector<char> m_canvas;

    bool PixelExists(unsigned x, unsigned y)const;
    unsigned GetPixelPosition(unsigned x, unsigned y)const;
};

