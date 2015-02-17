#include "stdafx.h"
#include "Controller.h"
#include "Model.h"
#include "FigureRectangle.h"
#include "FigureCircle.h"
#include "FigureTriangle.h"
#include "ActionNewFigure.h"
#include "ActionDeleteFigure.h"
#include "ActionMoveFigure.h"
#include "ActionResizeFigure.h"
#include "TestView.h"

void CController::AddNewRectangle(int centerX, int centerY, unsigned int width, unsigned int height)
{
	std::shared_ptr<IFigure> figure(new CRectangle(centerX, centerY, width, height));
	std::shared_ptr<IAction> action(new CActionNewFigure(figure));
	AddAction(action);
}

void CController::AddNewCircle(int centerX, int centerY, unsigned int width, unsigned int height)
{
	std::shared_ptr<IFigure> figure(new CCircle(centerX, centerY, width, height));
	std::shared_ptr<IAction> action(new CActionNewFigure(figure));
	AddAction(action);
}

void CController::AddNewTriangle(int centerX, int centerY, unsigned int width, unsigned int height)
{
	std::shared_ptr<IFigure> figure(new CTriangle(centerX, centerY, width, height));
	std::shared_ptr<IAction> action(new CActionNewFigure(figure));
	AddAction(action);
}

void CController::RemoveFigure(std::shared_ptr<IFigure> figure)
{
	std::shared_ptr<IAction> action(new CActionDeleteFigure(figure));
	AddAction(action);
}

void CController::MoveFigure(std::shared_ptr<IFigure> figure, int deltaX, int deltaY)
{
	std::shared_ptr<IAction> action(new CActionMoveFigure(figure, deltaX, deltaY));
	AddAction(action, false);
}

void CController::ResizeFigure(std::shared_ptr<IFigure> figure, int deltaWidth, int deltaHeight)
{
	std::shared_ptr<IAction> action(new CActionResizeFigure(figure, deltaWidth, deltaHeight));
	AddAction(action, false);
}

void CController::AddAction(std::shared_ptr<IAction> action, bool execute)
{
	if (m_currentActionIndex != m_actions.size() - 1)
	{
		m_actions.erase(m_actions.begin() + m_currentActionIndex, m_actions.end());
	}
	if (execute) action->Redo();
	m_actions.push_back(action);
	m_currentActionIndex = m_actions.size() - 1;
	CTestView::GetView()->OnModelChange();
}

void CController::Undo()
{
	if (m_currentActionIndex < 0) return;
	m_actions[m_currentActionIndex]->Undo();
	m_currentActionIndex--;
	CTestView::GetView()->OnModelChange();
}

void CController::Redo()
{
	if (!CanRedo()) return;
	m_currentActionIndex++;
	m_actions[m_currentActionIndex]->Redo();
	CTestView::GetView()->OnModelChange();
}

bool CController::CanRedo() const
{
	return m_currentActionIndex < (int)m_actions.size() - 1;
}

bool CController::CanUndo() const
{
	return m_currentActionIndex >= 0;
}

void CController::Reset()
{
	m_actions.clear();
	m_currentActionIndex = -1;
}