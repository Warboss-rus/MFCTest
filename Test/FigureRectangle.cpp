#include "stdafx.h"
#include "FigureRectangle.h"

CRectangle::CRectangle(int centerX, int centerY, unsigned int width, unsigned int height)
	:CFigure(centerX, centerY, width, height)
{
}

bool CRectangle::IsOnFigure(int x, int y) const
{
	int left = m_centerX - m_width / 2;
	int right = m_centerX + m_width / 2;
	int top = m_centerY - m_height / 2;
	int bottom = m_centerY + m_height / 2;
	return (x > left && x < right && y > top && y < bottom);
}

std::string CRectangle::GetType() const
{
	return "Rectangle";
}