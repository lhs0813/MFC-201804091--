// COtherView.cpp: 구현 파일
//

#include "pch.h"
#include "Project_1.h"
#include "COtherView.h"


// COtherView

IMPLEMENT_DYNCREATE(COtherView, CView)

COtherView::COtherView()
{

}

COtherView::~COtherView()
{
}

BEGIN_MESSAGE_MAP(COtherView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// COtherView 그리기

void COtherView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	CClientDC dc(this);
	

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	memDC.SelectObject(&bitmap);
	memDC.Rectangle(rect);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 
	//Draw wall
	CBrush wallBrush(RGB(255, 255, 255));
	memDC.SelectObject(wallBrush);
	memDC.Rectangle(0, 0, rect.Width(), rect.Height());

	dc.TextOut(0,200, _T("프레임 뷰어"));

	CImage bmpImage;
	if (FAILED(bmpImage.Load(_FileName)))
	{
		return;
	}
	//memDC.Rectangle(nextframe + 10, 0, _EndLine_pos.x - _StartLine_pos.x +10, _EndLine_pos.y - _StartLine_pos.y + 10);
	//dc.TextOut(nextframe, 0, _T("1"));

	_num.Format(_T("%.0f"), NumOFFire);
	dc.TextOut(nextframe, 0, _num);

	//CBrush _recside(RGB(0, 255, 0));
	//dc.SelectObject(_recside);
	//dc.Rectangle(nextframe + _EndLine_pos.x - _StartLine_pos.x , _EndLine_pos.y - _StartLine_pos.y + 20, _StartLine_pos.x, _StartLine_pos.y);

	bmpImage.BitBlt(dc.m_hDC, nextframe, 20, _EndLine_pos.x - _StartLine_pos.x, _EndLine_pos.y - _StartLine_pos.y, _StartLine_pos.x, _StartLine_pos.y, SRCCOPY);

	Invalidate();
	
	//_StartLine_pos = _StartLine.GetTail();
	//_EndLine_pos = _EndLine.GetTail();

	
	//bmpImage.BitBlt(dc.m_hDC, 16, 17, 69, 50, 0, 0, SRCCOPY);

	
	
	//bmpImage.BitBlt(dc.m_hDC, _StartLine_pos.x, _StartLine_pos.y,_EndLine_pos.x, _EndLine_pos.y, 0, 0, SRCCOPY);

	//dc.BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
}


// COtherView 진단

#ifdef _DEBUG
void COtherView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void COtherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// COtherView 메시지 처리기


BOOL COtherView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
