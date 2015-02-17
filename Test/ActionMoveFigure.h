#pragma once
#include "IAction.h"
#include <memory>
#include "IFigure.h"

class CActionMoveFigure : public IAction
{
public:
	CActionMoveFigure(std::shared_ptr<IFigure> figure, int deltaX, int deltaY);
	void Undo() const;
	void Redo() const;
private:
	std::shared_ptr<IFigure> m_figure;
	int m_deltaX;
	int m_deltaY;
};