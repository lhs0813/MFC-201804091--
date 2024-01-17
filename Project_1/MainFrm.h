
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once


#include "Project_1Doc.h"
#include "Project_1View.h"
#include "COtherView.h"
#include "Dibview.h"
#include "CAnimationView.h"
#include "CPivotView.h "


class CMainFrame : public CFrameWnd
{
private:
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
protected:
	
public:

	CSplitterWnd m_wndSplitter01;
	CSplitterWnd m_wndSplitter02;
	CSplitterWnd m_wndSplitter03;
	CSplitterWnd m_wndSplitter04;


	CProject1View* _infoView;
	Dibview* _DibView;
	CAnimationView* _AniView;
	COtherView* _SpriteView;
	CPivotView* _PivotView;



// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	BOOL m_blsSplitter;
	void ResizeSplitter();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	 
// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBmpBmp();
};


