#pragma once
#include "IAction.h"
#include <memory>
#include "IModel.h"

class CActionNewFigure : public IAction
{
public:
	CActionNewFigure(IModel * model, std::shared_ptr<IFigure> const& figure);
	void Undo();
	void Redo();
private:
	std::shared_ptr<IFigure> m_figure;
	IModel * m_pModel;
};