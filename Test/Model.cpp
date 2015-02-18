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

// Model.cpp : implementation of the CModel class
//

#include "stdafx.h"

#include "Model.h"
#include <propkey.h>
#include "FigureRectangle.h"
#include "FigureCircle.h"
#include "FigureTriangle.h"
#include "ActionNewFigure.h"
#include "ActionDeleteFigure.h"
#include "ActionMoveFigure.h"
#include "ActionResizeFigure.h"
#include "tinyxml.h"

// CModel

IMPLEMENT_DYNCREATE(CModel, CDocument)

BEGIN_MESSAGE_MAP(CModel, CDocument)
END_MESSAGE_MAP()


// CModel construction/destruction

CModel::CModel():m_currentActionIndex(-1)
{
	// TODO: add one-time construction code here

}

CModel::~CModel()
{
}

BOOL CModel::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	Reset();

	return TRUE;
}




// CModel serialization

void CModel::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		TiXmlDocument doc;
		TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
		doc.LinkEndChild(decl);
		TiXmlElement * element = new TiXmlElement("figures");
		doc.LinkEndChild(element);
		for (unsigned int i = 0; i < m_figures.size(); ++i)
		{
			TiXmlElement * figure = new TiXmlElement("figure");
			element->LinkEndChild(figure);
			IFigure * pFigure = m_figures[i].get();
			figure->SetAttribute("x", pFigure->GetCenterX());
			figure->SetAttribute("y", pFigure->GetCenterY());
			figure->SetAttribute("width", pFigure->GetWidth());
			figure->SetAttribute("height", pFigure->GetHeight());
			figure->SetAttribute("type", pFigure->GetType());
		}
		TiXmlPrinter printer;
		printer.SetIndent("    ");
		doc.Accept(&printer);
		std::string xmltext = printer.CStr();
		ar.Write(&xmltext[0], xmltext.size());
	}
	else
	{
		// TODO: add loading code here
		Reset();
		CFile * pFile = ar.GetFile();
		std::vector<char> str;
		unsigned int size = min(static_cast<unsigned int>(pFile->GetLength() + 1), UINT_MAX);
		str.resize(size);
		pFile->Read(&str[0], size);
		TiXmlDocument doc;
		doc.Parse(&str[0]);
		TiXmlElement* root = doc.RootElement();
		if (root)
		{
			TiXmlElement* figure = root->FirstChildElement("figure");
			while (figure)
			{
				int x = atoi(figure->Attribute("x"));
				int y = atoi(figure->Attribute("y"));
				unsigned int width = atoi(figure->Attribute("width"));
				unsigned int height = atoi(figure->Attribute("height"));
				std::string type = figure->Attribute("type");
				std::shared_ptr<IFigure> fig;
				if (type == "Rectangle") fig.reset(new CRectangle(x, y, width, height));
				if (type == "Triangle") fig.reset(new CTriangle(x, y, width, height));
				if (type == "Circle") fig.reset(new CCircle(x, y, width, height));
				AddFigure(fig);
				figure = figure->NextSiblingElement("figure");
			}
		}
		doc.Clear();
		OnChange();
	}
}

// CModel commands

void CModel::AddFigure(std::shared_ptr<IFigure> figure)
{
	m_figures.push_back(figure);
}

unsigned int CModel::GetNumberOfFigures() const
{
	return m_figures.size();
}

const std::shared_ptr<IFigure> CModel::GetFigureAt(unsigned int index) const
{
	return m_figures[index];
}

void CModel::Remove(std::shared_ptr<IFigure> figure)
{
	for (unsigned int i = 0; i < m_figures.size(); ++i)
	{
		if (m_figures[i] == figure)
		{
			std::swap(m_figures[i], m_figures.back());
			m_figures.pop_back();
			return;
		}
	}
}

CModel * CModel::GetModel()
{
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
	return (CModel *)pFrame->GetActiveDocument();
}

void CModel::AddNewRectangle(int centerX, int centerY, unsigned int width, unsigned int height)
{
	std::shared_ptr<IFigure> figure(new CRectangle(centerX, centerY, width, height));
	AddAction(new CActionNewFigure(this, figure));
}

void CModel::AddNewCircle(int centerX, int centerY, unsigned int width, unsigned int height)
{
	std::shared_ptr<IFigure> figure(new CCircle(centerX, centerY, width, height));
	AddAction(new CActionNewFigure(this, figure));
}

void CModel::AddNewTriangle(int centerX, int centerY, unsigned int width, unsigned int height)
{
	std::shared_ptr<IFigure> figure(new CTriangle(centerX, centerY, width, height));
	AddAction(new CActionNewFigure(this, figure));
}

void CModel::RemoveFigure(std::shared_ptr<IFigure> figure)
{
	AddAction(new CActionDeleteFigure(this, figure));
}

void CModel::MoveFigure(std::shared_ptr<IFigure> figure, int deltaX, int deltaY)
{
	AddAction(new CActionMoveFigure(figure, deltaX, deltaY), false);
}

void CModel::ResizeFigure(std::shared_ptr<IFigure> figure, int deltaWidth, int deltaHeight)
{
	AddAction(new CActionResizeFigure(figure, deltaWidth, deltaHeight), false);
}

void CModel::AddAction(IAction* action, bool execute)
{
	if (m_currentActionIndex != m_actions.size() - 1)
	{
		m_actions.erase(m_actions.begin() + m_currentActionIndex, m_actions.end());
	}
	if (execute) action->Redo();
	m_actions.push_back(std::unique_ptr<IAction>(action));
	m_currentActionIndex = m_actions.size() - 1;
	OnChange();
}

void CModel::Undo()
{
	if (m_currentActionIndex < 0) return;
	m_actions[m_currentActionIndex]->Undo();
	m_currentActionIndex--;
	OnChange();
}

void CModel::Redo()
{
	if (!CanRedo()) return;
	m_currentActionIndex++;
	m_actions[m_currentActionIndex]->Redo();
	OnChange();
}

bool CModel::CanRedo() const
{
	return m_currentActionIndex < (int)m_actions.size() - 1;
}

bool CModel::CanUndo() const
{
	return m_currentActionIndex >= 0;
}

void CModel::Reset()
{
	m_figures.clear();
	m_actions.clear();
	m_currentActionIndex = -1;
}

void CModel::OnChange()
{
	SetModifiedFlag();
	if (m_onChangeCallback) m_onChangeCallback();
}

void CModel::SetOnChangeCallback(std::function<void()> callback)
{
	m_onChangeCallback = callback;
}