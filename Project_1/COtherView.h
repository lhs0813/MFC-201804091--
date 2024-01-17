#pragma once


// COtherView 보기

class COtherView : public CView
{
	DECLARE_DYNCREATE(COtherView)

protected:
	COtherView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~COtherView();

public:
	CString	_FileName;

	CString _num = 0;
	float NumOFFire;

	CList<CPoint> _StartLine;
	CList<CPoint> _EndLine;

	CPoint _StartLine_pos;
	CPoint _EndLine_pos;

	int nextframe = -20;



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


