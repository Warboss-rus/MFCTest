#pragma once
#include <memory>
#include "IFigure.h"

class IModel
{
public:
	virtual ~IModel() {}
	virtual void AddFigure(std::shared_ptr<IFigure> figure) = 0;
	virtual void Remove(std::shared_ptr<IFigure> figure) = 0;
};