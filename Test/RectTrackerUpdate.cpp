#include "stdafx.h"
#include "RectTrackerUpdate.h"
#include "TestView.h"

CRectTrackerUpdate::CRectTrackerUpdate(LPCRECT lpSrcRect, UINT nStyle, CTestView * view)
	:CRectTracker(lpSrcRect, nStyle), m_view(view)
{

}

void CRectTrackerUpdate::DrawTrackerRect(LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd)
{
	m_view->Update();
}