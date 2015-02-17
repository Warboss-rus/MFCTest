#pragma once
#include "IAction.h"
#include <memory>
#include "IFigure.h"

class CActionNewFigure : public IAction
{
public:
	CActionNewFigure(std::shared_ptr<IFigure> figure);
	void Undo() const;
	void Redo() const;
private:
	std::shared_ptr<IFigure> m_figure;
};