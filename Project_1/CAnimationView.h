#pragma once


// CAnimationView 보기

class CAnimationView : public CView
{
	DECLARE_DYNCREATE(CAnimationView)

protected:
	CAnimationView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CAnimationView();

public:
	CString	_IMGNAME_ANI;
	CImage* pszFileName;

	BOOL _AniStart = FALSE;

	int Color_R;
	int Color_G;
	int Color_B;

	CPoint _AniMation_X[15] = { NULL };
	CPoint _AniMation_Y[15] = { NULL };

	CPoint Task_X;
	CPoint Task_Y;

	int Frame = 1;

	int _nextframe =0;

	int i;

	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


