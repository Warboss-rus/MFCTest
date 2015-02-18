#pragma once
#include "Figure.h"

class CTriangle : public CFigure
{
public:
	CTriangle(int centerX, int centerY, unsigned int width, unsigned int height);
	bool IsOnFigure(int x, int y) const;
	std::string GetType() const;
};