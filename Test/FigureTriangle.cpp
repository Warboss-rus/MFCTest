#include "stdafx.h"
#include "FigureTriangle.h"

CTriangle::CTriangle(int centerX, int centerY, unsigned int width, unsigned int height)
	:CFigure(centerX, centerY, width, height)
{
}

int sign(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y)
{
	return (p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y);
}

bool CTriangle::IsOnFigure(unsigned int x, unsigned int y) const
{
	int left = m_centerX - m_width / 2;
	int right = m_centerX + m_width / 2;
	int top = m_centerY - m_height / 2;
	int bottom = m_centerY + m_height / 2;

	int v1x = left;
	int v1y = bottom;
	int v2x = m_centerX;
	int v2y = top;
	int v3x = right;
	int v3y = bottom;

	bool b1 = sign(x, y, v1x, v1y, v2x, v2y) < 0;
	bool b2 = sign(x, y, v2x, v2y, v3x, v3y) < 0;
	bool b3 = sign(x, y, v3x, v3y, v1x, v1y) < 0;

	return ((b1 == b2) && (b2 == b3));
}

std::string CTriangle::GetType() const
{
	return "Triangle";
}