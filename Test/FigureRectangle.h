#pragma once
#include "Figure.h"

class CRectangle : public CFigure
{
public:
	CRectangle(int centerX, int centerY, unsigned int width, unsigned int height);
	bool IsOnFigure(int x, int y) const;
	std::string GetType() const;
};