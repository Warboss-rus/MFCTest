#pragma once
class IAction
{
public:
	virtual ~IAction() {}
	virtual void Undo() const = 0;
	virtual void Redo() const = 0;
};