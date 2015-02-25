#pragma once
#include "IAction.h"
#include <memory>
#include "IModel.h"

class CActionDeleteFigure : public IAction
{
public:
	CActionDeleteFigure(IModel * model, std::shared_ptr<IFigure> const& figure);
	void Undo();
	void Redo();
private:
	std::shared_ptr<IFigure> m_figure;
	IModel * m_pModel;
};
