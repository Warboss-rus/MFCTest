#pragma once

class CTestView;

class CRectTrackerUpdate : public CRectTracker
{
public:
	CRectTrackerUpdate() {}
	CRectTrackerUpdate(LPCRECT lpSrcRect,UINT nStyle, CTestView * view);
	virtual void DrawTrackerRect(LPCRECT lpRect, CWnd* pWndClipTo, CDC* pDC, CWnd* pWnd);
private:
	CTestView * m_view;
};