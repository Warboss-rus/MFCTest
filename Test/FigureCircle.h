#pragma once
#include "Figure.h"

class CCircle : public CFigure
{
public:
	CCircle(int centerX, int centerY, unsigned int width, unsigned int height);
	bool IsOnFigure(int x, int y) const;
	std::string GetType() const;
};