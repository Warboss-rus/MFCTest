#include "stdafx.h"
#include "ActionNewFigure.h"

CActionNewFigure::CActionNewFigure(IModel* model, std::shared_ptr<IFigure> const& figure)
	:m_figure(figure), m_pModel(model)
{
}

void CActionNewFigure::Redo()
{
	m_pModel->AddFigure(m_figure);
}

void CActionNewFigure::Undo()
{
	m_pModel->Remove(m_figure);
}