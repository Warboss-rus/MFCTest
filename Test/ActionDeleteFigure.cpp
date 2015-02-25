#include "stdafx.h"
#include "ActionDeleteFigure.h"

CActionDeleteFigure::CActionDeleteFigure(IModel * model, std::shared_ptr<IFigure> const& figure)
	:m_figure(figure), m_pModel(model)
{
}

void CActionDeleteFigure::Redo()
{
	m_pModel->Remove(m_figure);
}

void CActionDeleteFigure::Undo()
{
	m_pModel->AddFigure(m_figure);
}