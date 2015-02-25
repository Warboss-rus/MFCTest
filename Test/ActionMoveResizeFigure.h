#pragma once
#include "IAction.h"
#include <memory>
#include "IFigure.h"

class CActionMoveResizeFigure : public IAction
{
public:
	CActionMoveResizeFigure(std::shared_ptr<IFigure> const& figure, int deltaWidth, int deltaHeight, int deltaX, int deltaY);
	void Undo();
	void Redo();
private:
	std::shared_ptr<IFigure> m_figure;
	int m_deltaWidth;
	int m_deltaHeight;
	int m_deltaX;
	int m_deltaY;
};