#pragma once
#include "IAction.h"
#include <memory>
#include "IFigure.h"

class CActionResizeFigure : public IAction
{
public:
	CActionResizeFigure(std::shared_ptr<IFigure> figure, int deltaWidth, int deltaHeight);
	void Undo() const;
	void Redo() const;
private:
	std::shared_ptr<IFigure> m_figure;
	int m_deltaWidth;
	int m_deltaHeight;
};