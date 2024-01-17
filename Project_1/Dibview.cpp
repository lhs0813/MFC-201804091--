// Dibview.cpp: 구현 파일
//

#include "pch.h"
#include <atlimage.h>
#include "Project_1.h"
#include "Dibview.h"
#include "MainFrm.h"

#include "pch.h"
#include "framework.h"
#include "Project_1.h"
#include "MainFrm.h"
#include "Project_1Doc.h"
#include "Project_1View.h"
#include "COtherView.h"
#include "Dibview.h"
#include "CAnimationView.h"
#include "CPivotView.h "


// Dibview

IMPLEMENT_DYNCREATE(Dibview, CView)

Dibview::Dibview()
{
	m_ptCurPoint = NULL;
	m_ptOldPoint = NULL;
	m_ptBoxStart = m_ptBoxEnd = NULL;
}

Dibview::~Dibview()
{
}

BEGIN_MESSAGE_MAP(Dibview, CView)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// Dibview 그리기


void Dibview::CrossLien(CPoint point)
{
	CClientDC dc(this);
	CPen Cross(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* pOldPen = dc.SelectObject(&Cross);

	dc.SetROP2(R2_XORPEN);

	//가로
	dc.MoveTo(0, point.y);
	dc.LineTo(RECT.right, point.y);

	//세로
	dc.MoveTo(point.x, 0);
	dc.LineTo(point.x, RECT.bottom);

	dc.SelectObject(pOldPen);

	//DeleteObject(&Cross);
	//DeleteObject(pOldPen);


	//dc.SelectObject(pOldPen);
	

}

void Dibview::BOX(CPoint ptStart, CPoint ptEnd)
{
	CClientDC dc(this);

	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(NULL_BRUSH);
	dc.SetROP2(R2_XORPEN);
	//사각형
	dc.Rectangle(ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
}

void Dibview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.


	CClientDC dc(this);
	dc.TextOut(0, 0, _T("스프라이트 뷰어"));
	//dc.TextOut(0, 0, _T("스프라이트 뷰어"));
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	memDC.SelectObject(&bitmap);
	memDC.Rectangle(rect);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CBrush wallBrush(RGB(255, 255, 255));
	memDC.SelectObject(wallBrush);
	memDC.Rectangle(0, 0, rect.Width(), rect.Height());
	
	memDC.TextOut(0, 0, _T("스프라이트 뷰어"));

	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP1);

	//CBrush brush(&bitmap);
	//dc.SelectObject(&brush);
	//dc.Rectangle(0, 0, 30, 30);


	





	//이미지 포멧 출력 구문
	CImage bmpImage;
	if (FAILED(bmpImage.Load(_IMGNAME)))
	{
		return;
	}
	int imgWidth = bmpImage.GetWidth();
	int imgHeight = bmpImage.GetHeight();

	CString _imgWidth;
	CString _imgHeight;

	_imgWidth.Format(_T("%d"), imgWidth);
	_imgHeight.Format(_T("%d"), imgHeight);

	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();
	Vfr->_infoView-> _Width = _imgWidth;
	//Vfr->_infoView->Invalidate();
	Vfr->_infoView-> _Height = _imgHeight;
	//Vfr->_infoView->Invalidate();
	Vfr->_infoView->UpdateData(FALSE);

	bmpImage.BitBlt(memDC, 0, 0, imgWidth, imgHeight, 0, 0, SRCCOPY);

	dc.BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
	Invalidate();


}


// Dibview 진단

#ifdef _DEBUG
void Dibview::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void Dibview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// Dibview 메시지 처리기



void Dibview::OnMouseMove(UINT nFlags, CPoint point)

{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	GetClientRect(&RECT);
	m_ptCurPoint = point;
	CrossLien(m_ptOldPoint);
	m_ptOldPoint = m_ptCurPoint;
	CrossLien(m_ptCurPoint);

	if (_btnclick) {
		BOX(m_ptBoxStart, m_ptBoxEnd);
		m_ptBoxEnd = point;
		BOX(m_ptBoxStart, m_ptBoxEnd);
	}

	//마우스 포인터 다이얼로그
	CClientDC dc(this);

	CString strPoint_X;
	CString strPoint_Y;
	CString strPoint;

	//strPoint.Format(_T("%04d, %04d"), point.x, point.y);

	strPoint_X.Format(_T("%04d"), point.x);
	strPoint_Y.Format(_T("%04d"), point.y);

	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();
	Vfr -> _infoView ->  _X = strPoint_X;
	//Vfr->_infoView->Invalidate();
	Vfr -> _infoView  -> _Y = strPoint_Y;
	//Vfr->_infoView->Invalidate();
	Vfr-> _infoView -> UpdateData(FALSE);

	//dc.TextOut(0,0,strPoint);
	
	CView::OnMouseMove(nFlags, point);
}


BOOL Dibview::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CrossLien(m_ptOldPoint);

	return true;
}


void Dibview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();

	m_ptBoxStart = m_ptBoxEnd = point;

	_StartPos = point;
	Vfr->_SpriteView->_StartLine_pos = _StartPos;
	Vfr->_AniView->Task_X = _StartPos;
	Vfr->_PivotView->Task_X = _StartPos;

	Vfr->_PivotView->_nextframe += 1;
	Vfr->_AniView->_nextframe += 1;

	//Vfr->_SpriteView->_StartLine.AddTail(_StartPos);

	_btnclick = TRUE;


	CView::OnLButtonDown(nFlags, point);
}


void Dibview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();

	BOX(m_ptBoxStart, m_ptBoxEnd);

	_EndPos = point;

	Vfr->_SpriteView->_EndLine_pos = _EndPos;
	Vfr->_AniView->Task_Y = _EndPos;
	Vfr->_PivotView->Task_Y = _EndPos;
	
	//Vfr->_SpriteView->_StartLine.AddTail(_EndPos);
	Vfr->_SpriteView->nextframe += _EndPos.x - _StartPos.x + 20;
	Vfr->_SpriteView->NumOFFire += 1;

	Vfr->_SpriteView->UpdateData(FALSE);
	Vfr->_AniView->UpdateData(FALSE);

	_btnclick = FALSE;
	

	CView::OnLButtonUp(nFlags, point);
}
