#include "stdafx.h"
#include "ActionMoveFigure.h"

CActionMoveFigure::CActionMoveFigure(std::shared_ptr<IFigure> figure, int deltaX, int deltaY)
	:m_figure(figure), m_deltaX(deltaX), m_deltaY(deltaY)
{
}

void CActionMoveFigure::Redo() const
{
	m_figure->SetCenter(m_figure->GetCenterX() + m_deltaX, m_figure->GetCenterY() + m_deltaY);
}

void CActionMoveFigure::Undo() const
{
	m_figure->SetCenter(m_figure->GetCenterX() - m_deltaX, m_figure->GetCenterY() - m_deltaY);
}