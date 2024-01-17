// CAnimationView.cpp: 구현 파일
//

#include "pch.h"
#include "Project_1.h"
#include "CAnimationView.h"


// CAnimationView

IMPLEMENT_DYNCREATE(CAnimationView, CView)

CAnimationView::CAnimationView()
{
	Color_R;
	Color_G;
	Color_B;

	i = 0;
	
}

CAnimationView::~CAnimationView()
{
}

BEGIN_MESSAGE_MAP(CAnimationView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CAnimationView 그리기

void CAnimationView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	//중점창
	CClientDC dc(this);
	dc.TextOut(0, 0, _T("애니메이션 뷰어"));
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(&rect);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rect.right, rect.bottom);
	memDC.SelectObject(&bitmap);
	memDC.Rectangle(rect);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	


	//CPen Cross(PS_SOLID, 2, RGB(255, 255, 255));
	//CPen* pOldPen = memDC.SelectObject(&Cross);

	//memDC.SetROP2(R2_XORPEN);

	_AniMation_X[_nextframe] = Task_X;
	_AniMation_Y[_nextframe] = Task_Y;

	//가로

	//가로
	//memDC.MoveTo(150, 0);
	//memDC.LineTo(150, 500);

	//세로
	//memDC.MoveTo(0, 100);
	//memDC.LineTo(500, 100);

	//memDC.SelectObject(pOldPen);
	//애니메이션 실행

	CString str;
	CString str2;
	CString str3;
	str.Format(_T("%d"), Color_R);
	str2.Format(_T("%d"), Color_G);
	str3.Format(_T("%d"), Color_B);

	

	CBrush wallBrush(RGB(Color_R, Color_G, Color_B));
	memDC.SelectObject(wallBrush);
	memDC.Rectangle(0, 0, rect.Width(), rect.Height());

	memDC.TextOut(0, 0, _T("애니메이션 뷰어"));


	memDC.TextOut(180, 0, _T("R"));

	memDC.TextOut(180, 20, str);

	memDC.TextOut(230, 0, _T("G"));

	memDC.TextOut(230, 20, str2);

	memDC.TextOut(280, 0, _T("B"));

	memDC.TextOut(280, 20, str3);


	CImage bmpImage;
	if (FAILED(bmpImage.Load(_IMGNAME_ANI)))
	{
		return;
	}





	if (_AniStart == FALSE) {


		HDC hMemDC;
		//CString str4;
		//str4.Format(_T("%d"), _AniMation_X[0].x);
		//memDC.TextOut(150, 150, str4);
		//HRESULT Load(LPCTSTR pszFileName) throw();
		//bmpImage.TransparentBlt(memDC, _AniMation_X[_nextframe].x, _AniMation_X[_nextframe].y, _AniMation_Y[_nextframe].x, _AniMation_Y[_nextframe].y, RGB(0, 0, 0));
		//bmpImage.TransparentBlt(memDC, _AniMation_X[_nextframe], _AniMation_Y[_nextframe], RGB(0, 0, 0));
		//TransparentBlt(memDC, 0, 0, 640, 1280, hMemDC, 0, 0, 640, 1280, RGB(255, 255, 255));
		bmpImage.BitBlt(memDC, 140, 80, _AniMation_Y[_nextframe].x - _AniMation_X[_nextframe].x, _AniMation_Y[_nextframe].y - _AniMation_X[_nextframe].y, _AniMation_X[_nextframe].x, _AniMation_X[_nextframe].y, SRCCOPY);

		//bmpImage.BitBlt(memDC, 150,130,17,12,72,74, SRCCOPY);

		//memDC.TextOut(0, 15, Color_R);

	}

	if (_AniStart == TRUE) {



		//CString str4;
		//str4.Format(_T("%d"), _AniMation_X[0].x);
		//memDC.TextOut(150, 150, str4);
		//HRESULT Load(LPCTSTR pszFileName) throw();


		for (int j = 0; j < (100*Frame); j++) {
			bmpImage.BitBlt(memDC, 140, 80, _AniMation_Y[i].x - _AniMation_X[i].x, _AniMation_Y[i].y - _AniMation_X[i].y, _AniMation_X[i].x, _AniMation_X[i].y, SRCCOPY);
		}
		i++;

		//bmpImage.BitBlt(memDC, 150,130,17,12,72,74, SRCCOPY);

		//memDC.TextOut(0, 15, Color_R);
		

	}

	if (i == 14) {
		i = 0;
	}



















	
	
	//memDC.Rectangle(nextframe + 10, 0, _EndLine_pos.x - _StartLine_pos.x +10, _EndLine_pos.y - _StartLine_pos.y + 10);
	//dc.TextOut(nextframe, 0, _T("1"));

	//CBrush _recside(RGB(0, 255, 0));
	//dc.SelectObject(_recside);
	//dc.Rectangle(nextframe + _EndLine_pos.x - _StartLine_pos.x , _EndLine_pos.y - _StartLine_pos.y + 20, _StartLine_pos.x, _StartLine_pos.y);

	//--bmpImage.BitBlt(dc.m_hDC, nextframe, 20, _EndLine_pos.x - _StartLine_pos.x, _EndLine_pos.y - _StartLine_pos.y, _StartLine_pos.x, _StartLine_pos.y, SRCCOPY);
	//Invalidate();
	//CDC MemDC;
	//CBitmap memBmp;
	//COLORREF color;



	/*
	MemDC.CreateCompatibleDC(pDC);
	memBmp.CreateCompatibleBitmap(pDC, pDib->Width(), pDib->Height());
	CBitmap* oldBmp = (CBitmap*)MemDC.SelectObject(&memBmp);

	SetDIBitsToDevice(MemDC, 0, 0, pDib->Width(), pDib->Height(),
		0, 0, 0, pDib->Height(), pDib->GetImgPtr(), pDib->GetInfoPtr(), DIB_RGB_COLORS);

	color = MemDC.GetPixel(0, 0); //컬러값 잡을 위치

	TransparentBlt(pDC->m_hDC, (rt.right - rt.left) / 2 - pDib->m_CenterPoint.x,
		(rt.bottom - rt.top) / 2 - pDib->m_CenterPoint.y, pDib->Width(), pDib->Height(),
		MemDC, 0, 0, pDib->Width(), pDib->Height(), RGB(color, color, color));  //칼라값 설정

	MemDC.DeleteDC();
	DeleteObject(&memBmp);

	*/
	Invalidate();
	dc.BitBlt(0, 0, rect.right, rect.bottom, &memDC, 0, 0, SRCCOPY);
	
	
}


// CAnimationView 진단

#ifdef _DEBUG
void CAnimationView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CAnimationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAnimationView 메시지 처리기


BOOL CAnimationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CAnimationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//if (_AniStart == TRUE) {
	//	nextframe++;
	//}

	if (nIDEvent == 0) {
	//	if (_AniStart == TRUE) {
		//	i++;
		//}
		
		
	}
	
	CView::OnTimer(nIDEvent);
}


int CAnimationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 100, NULL);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void CAnimationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_SPACE:

		if (_AniStart == FALSE) {
			_AniStart = TRUE;
		}

		else if (_AniStart == TRUE) {
			_AniStart = FALSE;
		}
		//nextframe = 0;
		i = 0;

	case VK_RIGHT:
		i++;

	case VK_LEFT:
		i--;

		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
