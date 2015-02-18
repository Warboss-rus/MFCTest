#include "stdafx.h"
#include "ActionDeleteFigure.h"

CActionDeleteFigure::CActionDeleteFigure(IModel * model, std::shared_ptr<IFigure> figure)
	:m_figure(figure)
{
}

void CActionDeleteFigure::Redo() const
{
	m_pModel->Remove(m_figure);
}

void CActionDeleteFigure::Undo() const
{
	m_pModel->AddFigure(m_figure);
}