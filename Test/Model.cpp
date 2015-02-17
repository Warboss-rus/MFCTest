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
#include "tinyxml.h"
#include "TestView.h"

// CModel

IMPLEMENT_DYNCREATE(CModel, CDocument)

BEGIN_MESSAGE_MAP(CModel, CDocument)
END_MESSAGE_MAP()


// CModel construction/destruction

CModel::CModel()
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
	m_figures.clear();
	CTestView * view = CTestView::GetView();
	if(view) view->GetController()->Reset();

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
			figure->SetAttribute("x", m_figures[i]->GetCenterX());
			figure->SetAttribute("y", m_figures[i]->GetCenterY());
			figure->SetAttribute("width", m_figures[i]->GetWidth());
			figure->SetAttribute("height", m_figures[i]->GetHeight());
			figure->SetAttribute("type", m_figures[i]->GetType());
			element->LinkEndChild(figure);
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
		m_figures.clear();
		CTestView::GetView()->GetController()->Reset();
		CFile * pFile = ar.GetFile();
		char* str = NULL;
		try
		{
			str = new char[pFile->GetLength() + 1];
			pFile->Read(str, pFile->GetLength() + 1);
			TiXmlDocument doc;
			doc.Parse(str);
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
		}
		catch (std::exception) {}
		if (str) delete[] str;
		CTestView::GetView()->OnModelChange();
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

void CModel::RemoveFigure(std::shared_ptr<IFigure> figure)
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