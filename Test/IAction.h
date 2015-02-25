#pragma once
class IAction
{
public:
	virtual ~IAction() {}
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};