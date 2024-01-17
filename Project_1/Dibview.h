#pragma once


// Dibview 보기

class Dibview : public CView
{
	DECLARE_DYNCREATE(Dibview)

protected:
	Dibview();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~Dibview();

public:
	CString	_IMGNAME;
	CRect RECT;
	CPoint m_ptCurPoint;
	CPoint m_ptOldPoint;

	CPoint m_ptBoxEnd;
	CPoint m_ptBoxStart;

	BOOL _btnclick;


	CPoint _StartPos;
	CPoint _EndPos;



	void CrossLien(CPoint point);
	void BOX(CPoint ptStart, CPoint ptEnd);

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
	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


