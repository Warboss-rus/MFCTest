#include "stdafx.h"
#include "ActionResizeFigure.h"

CActionResizeFigure::CActionResizeFigure(std::shared_ptr<IFigure> figure, int deltaWidth, int deltaHeight)
	:m_figure(figure), m_deltaWidth(deltaWidth), m_deltaHeight(deltaHeight)
{
}

void CActionResizeFigure::Redo() const
{
	m_figure->Resize(m_figure->GetWidth() + m_deltaWidth, m_figure->GetHeight() + m_deltaHeight);
}

void CActionResizeFigure::Undo() const
{
	m_figure->Resize(m_figure->GetWidth() - m_deltaWidth, m_figure->GetHeight() - m_deltaHeight);
}