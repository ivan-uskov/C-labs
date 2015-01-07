#pragma once

class CRectangle
{

public:

    CRectangle(const int left, const int top, const int width, const int height);
    ~CRectangle();

    int GetLeft()const;
    int GetRight()const;
    int GetTop()const;
    int GetBottom()const;
    int GetWidth()const;
    int GetHeight()const;

    void SetLeft(const int left);
    void SetRight(const int right);
    void SetTop(const int top);
    void SetBottom(const int bottom);
    void SetWidth(const int width);
    void SetHeight(const int height);

    void Move(const int dx, const int dy);
    void Scale(const int sx, const int sy);
    bool Intersect(CRectangle const& other);

    int GetArea()const;
    int GetPerimeter()const;

private:

    int m_left, m_top;
    int m_width, m_height;

};

