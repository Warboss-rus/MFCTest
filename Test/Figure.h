#pragma once
#include "IFigure.h"

class CFigure : public IFigure
{
public:
	CFigure(int centerX, int centerY, unsigned int width, unsigned int height);
	virtual bool IsOnFigure(unsigned int x, unsigned int y) const = 0;
	virtual std::string GetType() const = 0;
	int GetCenterX() const;
	int GetCenterY() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	void SetCenter(int x, int y);
	void Resize(unsigned int width, unsigned int height);
protected:
	int m_centerX;
	int m_centerY;
	unsigned int m_width;
	unsigned int m_height;
};