// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// Model.h : interface of the CModel class
//
#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "IModel.h"
#include "IAction.h"
#include "ActionHandler.h"

class CModel : public CDocument, public IModel
{
public:
	virtual ~CModel();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void AddFigure(std::shared_ptr<IFigure> const& figure);
	void RemoveFigure(std::shared_ptr<IFigure> const& figure);
	unsigned int GetNumberOfFigures() const;
	const std::shared_ptr<IFigure> GetFigureAt(unsigned int index) const;
	void AddNewRectangle(int centerX, int centerY, unsigned int width, unsigned int height);
	void AddNewCircle(int centerX, int centerY, unsigned int width, unsigned int height);
	void AddNewTriangle(int centerX, int centerY, unsigned int width, unsigned int height);
	void Remove(std::shared_ptr<IFigure> const& figure);
	void MoveAndResizeFigure(std::shared_ptr<IFigure> const& figure, int deltaX, int deltaY, int deltaWidth, int deltaHeight);
	void SetOnChangeCallback(std::function<void()> const& callback);
	void OnChange();
	CActionHandler * GetActionHandler() { return &m_actHandler; }
protected:
	CModel();
	DECLARE_DYNCREATE(CModel)
	DECLARE_MESSAGE_MAP()
private:
	void Reset();
	CActionHandler m_actHandler;
	std::vector<std::shared_ptr<IFigure>> m_figures;
	std::function<void()> m_onChangeCallback;
};
