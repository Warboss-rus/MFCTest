#include "stdafx.h"
#include "ActionDeleteFigure.h"
#include "Model.h"

CActionDeleteFigure::CActionDeleteFigure(std::shared_ptr<IFigure> figure)
	:m_figure(figure)
{
}

void CActionDeleteFigure::Redo() const
{
	CModel* pDoc = CModel::GetModel();
	pDoc->RemoveFigure(m_figure);
}

void CActionDeleteFigure::Undo() const
{
	CModel* pDoc = CModel::GetModel();
	pDoc->AddFigure(m_figure);
}