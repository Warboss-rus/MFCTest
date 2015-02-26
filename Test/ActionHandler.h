#include <memory>
#include <vector>
#include "IAction.h"
#include "IModel.h"

class CActionHandler
{
public:
	CActionHandler(IModel * model);
	void AddAction(std::unique_ptr<IAction> && action, bool execute = true);
	void Undo();
	void Redo();
	bool CanUndo() const;
	bool CanRedo() const;
	void Reset();
private:
	std::vector<std::unique_ptr<IAction>> m_actions;
	int m_currentActionIndex;
	IModel * m_pModel;
};