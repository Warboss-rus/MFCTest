#pragma once
#include "IAction.h"
#include <memory>
#include "IFigure.h"

class CActionDeleteFigure : public IAction
{
public:
	CActionDeleteFigure(std::shared_ptr<IFigure> figure);
	void Undo() const;
	void Redo() const;
private:
	std::shared_ptr<IFigure> m_figure;
};
