
// Project_1View.h: CProject1View 클래스의 인터페이스
//

#pragma once


class CProject1View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CProject1View();
	DECLARE_DYNCREATE(CProject1View)

// 특성입니다.
public:
	CProject1Doc* GetDocument() const;

	CString	_FileName;
	CString _FileExt;

	CString _X;
	CString _Y;

	CString _Height;
	CString _Width;

	BOOL _AniBtn = FALSE;

	int RGB_R;
	int RGB_G;
	int RGB_B;

	CEdit _RGB_Control_R;
	CEdit _RGB_Control_G;
	CEdit _RGB_Control_B;

	int _FRAME;

// 작업입니다.
public:
	enum { IDD = IDD_FORMVIEW};

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CProject1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnIddFormview();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedFrameBtn();
	afx_msg void OnBnClickedButton2();
};

#ifndef _DEBUG  // Project_1View.cpp의 디버그 버전
inline CProject1Doc* CProject1View::GetDocument() const
   { return reinterpret_cast<CProject1Doc*>(m_pDocument); }
#endif

