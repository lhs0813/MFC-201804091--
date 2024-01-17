// CPivotView.cpp: 구현 파일
//

#include "pch.h"
#include "Project_1.h"
#include "CPivotView.h"


// CPivotView

IMPLEMENT_DYNCREATE(CPivotView, CView)

CPivotView::CPivotView()
{

}

CPivotView::~CPivotView()
{
}

void CPivotView::CrossLine(CPoint point)
{
	
}

BEGIN_MESSAGE_MAP(CPivotView, CView)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CPivotView 그리기

void CPivotView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CClientDC dc(this);
	dc.TextOut(0, 0, _T("이미지 뷰"));

	

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	memDC.SelectObject(&bitmap);
	memDC.Rectangle(rect);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CBrush wallBrush(RGB(0, 255, 0));
	memDC.SelectObject(wallBrush);
	memDC.Rectangle(0, 0, rect.Width(), rect.Height());

	memDC.TextOut(0, 0, _T("이미지 뷰"));

	_AniMation_X[_nextframe] = Task_X;
	_AniMation_Y[_nextframe] = Task_Y;

	CImage bmpImage;
	if (FAILED(bmpImage.Load(_IMGNAME_Pivot)))
	{
		return;
	}


	bmpImage.BitBlt(memDC, 140, 80, _AniMation_Y[_nextframe].x - _AniMation_X[_nextframe].x, _AniMation_Y[_nextframe].y - _AniMation_X[_nextframe].y, _AniMation_X[_nextframe].x, _AniMation_X[_nextframe].y, SRCCOPY);

	

	CPen Cross(PS_SOLID, 2, RGB(255, 0, 0));
	CPen* pOldPen = memDC.SelectObject(&Cross);

	memDC.SetROP2(R2_XORPEN);

	//가로

	//가로
	memDC.MoveTo(150, 0);
	memDC.LineTo(150, 500);

	//세로
	memDC.MoveTo(0, 100);
	memDC.LineTo(500, 100);

	memDC.SelectObject(pOldPen);

	
	Invalidate();
	dc.BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
}


// CPivotView 진단

#ifdef _DEBUG
void CPivotView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPivotView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPivotView 메시지 처리기


BOOL CPivotView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
