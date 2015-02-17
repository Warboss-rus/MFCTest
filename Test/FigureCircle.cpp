#include "stdafx.h"
#include "FigureCircle.h"

CCircle::CCircle(int centerX, int centerY, unsigned int width, unsigned int height)
	:CFigure(centerX, centerY, width, height)
{
}

bool CCircle::IsOnFigure(unsigned int x, unsigned int y) const
{
	double a = (double)m_width / 2.0;
	double b = (double)m_height / 2.0;
	int normalizedX = x - m_centerX;
	int normalizedY = y - m_centerY;
	return ((double)(normalizedX * normalizedX) / (a * a) + (double)(normalizedY * normalizedY) / (b * b) <= 1.0);
}

std::string CCircle::GetType() const
{
	return "Circle";
}