#pragma once


// CPivotView 보기

class CPivotView : public CView
{
	DECLARE_DYNCREATE(CPivotView)

protected:
	CPivotView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPivotView();


	

public:

	CPoint _AniMation_X[10] = { NULL };
	CPoint _AniMation_Y[10] = { NULL };

	CPoint Task_X;
	CPoint Task_Y;

	int _nextframe = 0;

	CString _IMGNAME_Pivot;
	CRect RECT;
	void CrossLine(CPoint point);
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
};


