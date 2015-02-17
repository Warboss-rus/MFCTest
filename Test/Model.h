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
#include "IFigure.h"

class CModel : public CDocument
{
public:
	virtual ~CModel();
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	void AddFigure(std::shared_ptr<IFigure> figure);
	void RemoveFigure(std::shared_ptr<IFigure> figure);
	unsigned int GetNumberOfFigures() const;
	const std::shared_ptr<IFigure> GetFigureAt(unsigned int index) const;
	static CModel * GetModel();
protected:
	CModel();
	DECLARE_DYNCREATE(CModel)
	DECLARE_MESSAGE_MAP()
private:
	std::vector<std::shared_ptr<IFigure>> m_figures;
};
