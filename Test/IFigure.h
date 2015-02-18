#pragma once
#include <string>

class IFigure
{
public:
	virtual ~IFigure() {}
	virtual int GetCenterX() const = 0;
	virtual int GetCenterY() const = 0;
	virtual unsigned int GetWidth() const = 0;
	virtual unsigned int GetHeight() const = 0;
	virtual bool IsOnFigure(int x, int y) const = 0;
	virtual std::string GetType() const = 0;
	virtual void SetCenter(int x, int y) = 0;
	virtual void Resize(unsigned int width, unsigned int height) = 0;
};