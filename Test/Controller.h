#pragma once
#include <vector>
#include <memory>
#include "IAction.h"
#include "IFigure.h"

class CController
{
public:
	CController() :m_currentActionIndex(-1) {}
	void AddNewRectangle(int centerX, int centerY, unsigned int width, unsigned int height);
	void AddNewCircle(int centerX, int centerY, unsigned int width, unsigned int height);
	void AddNewTriangle(int centerX, int centerY, unsigned int width, unsigned int height);
	void RemoveFigure(std::shared_ptr<IFigure> figure);
	void MoveFigure(std::shared_ptr<IFigure> figure, int deltaX, int deltaY);
	void ResizeFigure(std::shared_ptr<IFigure> figure, int deltaWidth, int deltaHeight);
	void Undo();
	void Redo();
	bool CanUndo() const;
	bool CanRedo() const;
	void Reset();
private:
	
	void AddAction(std::shared_ptr<IAction> action, bool execute = true);
	std::vector<std::shared_ptr<IAction>> m_actions;
	int m_currentActionIndex;
};