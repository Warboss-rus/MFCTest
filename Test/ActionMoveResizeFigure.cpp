#include "stdafx.h"
#include "ActionMoveResizeFigure.h"

CActionMoveResizeFigure::CActionMoveResizeFigure(std::shared_ptr<IFigure> const& figure, int deltaWidth, int deltaHeight, int deltaX, int deltaY)
	:m_figure(figure), m_deltaWidth(deltaWidth), m_deltaHeight(deltaHeight), m_deltaX(deltaX), m_deltaY(deltaY)
{
}

void CActionMoveResizeFigure::Redo()
{
	m_figure->Resize(m_figure->GetWidth() + m_deltaWidth, m_figure->GetHeight() + m_deltaHeight);
	m_figure->SetCenter(m_figure->GetCenterX() + m_deltaX, m_figure->GetCenterY() + m_deltaY);
}

void CActionMoveResizeFigure::Undo()
{
	m_figure->Resize(m_figure->GetWidth() - m_deltaWidth, m_figure->GetHeight() - m_deltaHeight);
	m_figure->SetCenter(m_figure->GetCenterX() - m_deltaX, m_figure->GetCenterY() - m_deltaY);
}