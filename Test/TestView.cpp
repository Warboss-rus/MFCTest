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

// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Test.h"
#endif


#include "TestView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std::placeholders;


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(ID_BUTTON2, OnNewRectangle)
	ON_BN_CLICKED(ID_BUTTON3, OnNewTriangle)
	ON_BN_CLICKED(ID_BUTTON4, OnNewCircle)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_KEYUP()
	ON_BN_CLICKED(ID_EDIT_UNDO, OnEditUndo)
	ON_BN_CLICKED(ID_EDIT_REDO, OnEditRedo)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnCommandUpdateUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnCommandUpdateRedo)
END_MESSAGE_MAP()

void DrawRectangle(CDC* pDC, int left, int right, int top, int bottom)
{
	pDC->Rectangle(left, top, right, bottom);
}

void DrawCircle(CDC* pDC, int left, int right, int top, int bottom)
{
	pDC->Ellipse(left, top, right, bottom);
}

void DrawTriangle(CDC* pDC, int left, int right, int top, int bottom)
{
	CPoint pts[3];
	pts[0].x = left;
	pts[0].y = bottom;
	pts[1].x = (right + left) / 2;
	pts[1].y = top;
	pts[2].x = right;
	pts[2].y = bottom;
	pDC->Polygon(pts, 3);
}

// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
	m_drawingFunctions["Rectangle"] = std::bind<void>(DrawRectangle, _1, _2, _3, _4, _5);
	m_drawingFunctions["Circle"] = std::bind<void>(DrawCircle, _1, _2, _3, _4, _5);
	m_drawingFunctions["Triangle"] = std::bind<void>(DrawTriangle, _1, _2, _3, _4, _5);
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//AdjustWindowRectEx(

	return CView::PreCreateWindow(cs);
}

// CTestView drawing

BOOL CTestView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CTestView::OnDraw(CDC* DC)
{
	CModel* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC dcMem;
	CBitmap bitmap;
	CRect rect;

	GetWindowRect(rect);
	dcMem.CreateCompatibleDC(DC);
	bitmap.CreateCompatibleBitmap(DC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = dcMem.SelectObject(&bitmap);

	DrawFigures(&dcMem, &rect);

	CPoint scroll = GetScrollPosition();
	DC->BitBlt(scroll.x, scroll.y, rect.Width(), rect.Height(), &dcMem, 0, 0, SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
}

void CTestView::DrawFigures(CDC * pDC, CRect * rect)
{
	CModel* pDoc = GetDocument();

	pDC->Rectangle(0, 0, rect->Width(), rect->Height());

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	CPoint scroll = GetScrollPosition();

	for (unsigned int i = 0; i < pDoc->GetNumberOfFigures(); ++i)
	{
		std::shared_ptr<IFigure> m_figure = pDoc->GetFigureAt(i);

		int left = -scroll.x + m_figure->GetCenterX() - m_figure->GetWidth() / 2;
		int right = -scroll.x + m_figure->GetCenterX() + m_figure->GetWidth() / 2;
		int top = -scroll.y + m_figure->GetCenterY() - m_figure->GetHeight() / 2;
		int bottom = -scroll.y + m_figure->GetCenterY() + m_figure->GetHeight() / 2;

		//Find a registered drawing function and execute it
		auto it = m_drawingFunctions.find(m_figure->GetType());
		if (it != m_drawingFunctions.end())
			it->second(pDC, left, right, top, bottom);
	}

	if (m_selectedObject)
	{
		m_tracker.Draw(pDC);
	}

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

CModel* CTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModel)));
	return (CModel*)m_pDocument;
}

void CTestView::OnNewRectangle()
{
	GetDocument()->AddNewRectangle(320, 240, 100, 100);
	UpdateScrollbars();
}

void CTestView::OnNewTriangle()
{
	GetDocument()->AddNewTriangle(320, 240, 100, 100);
	UpdateScrollbars();
}

void CTestView::OnNewCircle()
{
	GetDocument()->AddNewCircle(320, 240, 100, 100);
	UpdateScrollbars();
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_selectedObject)
	{
		m_prevRect = m_tracker.m_rect;
		if(m_tracker.Track(this, point, FALSE))
		{
			CPoint const& centerPoint = m_tracker.m_rect.CenterPoint() + GetScrollPosition();
			int width = m_tracker.m_rect.Width();
			int height = m_tracker.m_rect.Height();
			m_selectedObject->SetCenter(centerPoint.x, centerPoint.y);
			m_selectedObject->Resize(width, height);
			if (m_tracker.m_rect != m_prevRect)
			{
				CPoint deltaCenter = centerPoint - m_prevRect.CenterPoint();
				int deltaWidth = width - m_prevRect.Width();
				int deltaHeight = height - m_prevRect.Height();
				GetDocument()->MoveAndResizeFigure(m_selectedObject, deltaCenter.x, deltaCenter.y, deltaWidth, deltaHeight);
				UpdateScrollbars();
			}
		}
		InvalidateRect(NULL);
	}
}

void CTestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CModel* pDoc = GetDocument();
	m_selectedObject = NULL;
	CPoint scrolledPoint = point + GetScrollPosition();
	for (unsigned int i = 0; i < pDoc->GetNumberOfFigures(); ++i)
	{
		if (pDoc->GetFigureAt(i)->IsOnFigure(scrolledPoint.x, scrolledPoint.y))
		{
			m_selectedObject = pDoc->GetFigureAt(i);
		}
	}
	if (m_selectedObject)
	{
		CPoint top_left(m_selectedObject->GetCenterX() - m_selectedObject->GetWidth() / 2, m_selectedObject->GetCenterY() - m_selectedObject->GetHeight() / 2);
		CPoint bottom_right(m_selectedObject->GetCenterX() + m_selectedObject->GetWidth() / 2, m_selectedObject->GetCenterY() + m_selectedObject->GetHeight() / 2);
		CRect rect(top_left, bottom_right);
		rect -= GetScrollPosition();
		m_tracker = CRectTrackerUpdate(rect, CRectTracker::hatchedBorder | CRectTracker::resizeOutside | CRectTracker::resizeInside, this);
		m_tracker.m_sizeMin = CSize(100, 100);
	}
	else
	{
		m_tracker = CRectTrackerUpdate();
	}
	InvalidateRect(NULL);
}

BOOL CTestView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (pWnd == this && m_tracker.SetCursor(this, nHitTest))
		return TRUE;
	return CView::OnSetCursor(pWnd, nHitTest, message);
}
// CTestView message handlers

void CTestView::Update()
{
	if (m_selectedObject)
	{
		CPoint centerPoint = m_tracker.m_rect.CenterPoint() + GetScrollPosition();
		m_selectedObject->SetCenter(centerPoint.x, centerPoint.y);
		m_selectedObject->Resize(m_tracker.m_rect.Width(), m_tracker.m_rect.Height());
		InvalidateRect(NULL);
	}
}

void CTestView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE)
	{
		GetDocument()->RemoveFigure(m_selectedObject);
		m_selectedObject.reset();
		m_tracker = CRectTrackerUpdate();
		UpdateScrollbars();
	}
}

void CTestView::OnEditUndo()
{
	GetDocument()->GetActionHandler()->Undo();
	m_selectedObject.reset();
	UpdateScrollbars();
}

void CTestView::OnEditRedo()
{
	GetDocument()->GetActionHandler()->Redo();
	m_selectedObject.reset();
	UpdateScrollbars();
}

void CTestView::OnSize(UINT nType, int cx, int cy)
{
	UpdateBars();
}

void CTestView::OnInitialUpdate()
{
	SetScrollSizes(MM_TEXT, CSize(0, 0));
	CModel * model = GetDocument();
	model->SetOnChangeCallback([this]{InvalidateRect(NULL); });
}

void CTestView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
	m_tracker.m_rect -= (CPoint)(GetScrollPosition() - m_prevScrollPosition);
	m_prevScrollPosition = GetScrollPosition();
	Invalidate();
}

void CTestView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
	m_tracker.m_rect -= (CPoint)(GetScrollPosition() - m_prevScrollPosition);
	m_prevScrollPosition = GetScrollPosition();
	Invalidate();
}

void CTestView::OnCommandUpdateUndo(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetDocument()->GetActionHandler()->CanUndo());
}

void CTestView::OnCommandUpdateRedo(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(GetDocument()->GetActionHandler()->CanRedo());
}

void CTestView::UpdateScrollbars()
{
	CModel * model = GetDocument();
	int width = 0;
	int height = 0;
	for (int i = 0; i < model->GetNumberOfFigures(); ++i)
	{
		std::shared_ptr<IFigure> figure = model->GetFigureAt(i);
		width = max(width, figure->GetCenterX() + figure->GetWidth() / 2 + 5);//additional 5 pixels so you can grab RectTracker
		height = max(height, figure->GetCenterY() + figure->GetHeight() / 2 + 5);
	}
	SetScrollSizes(MM_TEXT, CSize(width, height));
}