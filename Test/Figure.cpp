#include "stdafx.h"
#include "Figure.h"

CFigure::CFigure(int centerX, int centerY, unsigned int width, unsigned int height)
	:m_centerX(centerX), m_centerY(centerY), m_width(width), m_height(height)
{

}

int CFigure::GetCenterX() const
{
	return m_centerX;
}

int CFigure::GetCenterY() const
{
	return m_centerY;
}

unsigned int CFigure::GetWidth() const
{
	return m_width;
}

unsigned int CFigure::GetHeight() const
{
	return m_height;
}

void CFigure::SetCenter(int x, int y)
{
	m_centerX = x;
	m_centerY = y;
}

void CFigure::Resize(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
}