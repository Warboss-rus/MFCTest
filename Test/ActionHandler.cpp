#include "stdafx.h"
#include "ActionHandler.h"

CActionHandler::CActionHandler(IModel * model) :m_pModel(model), m_currentActionIndex(-1)
{}

void CActionHandler::AddAction(std::unique_ptr<IAction> && action, bool execute)
{
	if (m_currentActionIndex != m_actions.size() - 1)
	{
		m_actions.erase(m_actions.begin() + m_currentActionIndex, m_actions.end());
	}
	if (execute) action->Redo();
	m_actions.push_back(std::move(action));
	m_currentActionIndex = m_actions.size() - 1;
	m_pModel->OnChange();
}

void CActionHandler::Undo()
{
	if (m_currentActionIndex < 0) return;
	m_actions[m_currentActionIndex]->Undo();
	m_currentActionIndex--;
	m_pModel->OnChange();
}

void CActionHandler::Redo()
{
	if (!CanRedo()) return;
	m_currentActionIndex++;
	m_actions[m_currentActionIndex]->Redo();
	m_pModel->OnChange();
}

bool CActionHandler::CanRedo() const
{
	return m_currentActionIndex < (int)m_actions.size() - 1;
}

bool CActionHandler::CanUndo() const
{
	return m_currentActionIndex >= 0;
}

void CActionHandler::Reset()
{
	m_actions.clear();
	m_currentActionIndex = -1;
}