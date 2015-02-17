#include "stdafx.h"
#include "ActionNewFigure.h"
#include "Model.h"

CActionNewFigure::CActionNewFigure(std::shared_ptr<IFigure> figure)
	:m_figure(figure)
{
}

void CActionNewFigure::Redo() const
{
	CModel* pDoc = CModel::GetModel();
	pDoc->AddFigure(m_figure);
}

void CActionNewFigure::Undo() const
{
	CModel* pDoc = CModel::GetModel();
	pDoc->RemoveFigure(m_figure);
}