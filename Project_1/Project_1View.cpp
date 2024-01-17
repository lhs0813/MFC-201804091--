
// Project_1View.cpp: CProject1View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Project_1.h"
#endif

#include "Project_1Doc.h"
#include "Project_1View.h"

#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"


// CProject1View

IMPLEMENT_DYNCREATE(CProject1View, CView)

BEGIN_MESSAGE_MAP(CProject1View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDD_FORMVIEW, &CProject1View::OnIddFormview)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FRAME_BTN, &CProject1View::OnBnClickedFrameBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CProject1View::OnBnClickedButton2)
END_MESSAGE_MAP()

// CProject1View 생성/소멸

CProject1View::CProject1View() : CFormView(IDD_FORMVIEW) // noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	_FileName = _T("");
	_FileExt = _T("");
	_X = _T("");
	_Y = _T("");


	
}

CProject1View::~CProject1View()
{
}

BOOL CProject1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CProject1View 그리기

void CProject1View::OnDraw(CDC* pDC)
{
	CProject1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.'
	CClientDC dc(this);
	dc.TextOut(0, 0, _T("조작 뷰어"));

	
}


// CProject1View 인쇄

BOOL CProject1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CProject1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CProject1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CProject1View 진단

#ifdef _DEBUG
void CProject1View::AssertValid() const
{
	CView::AssertValid();
}

void CProject1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject1Doc* CProject1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject1Doc)));
	return (CProject1Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject1View 메시지 처리기


void CProject1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	GetDocument()->_points.AddTail(point);

	GetDocument()->UpdateAllViews(NULL);

	CView::OnLButtonDown(nFlags, point);
}


void CProject1View::OnIddFormview()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CProject1View::DoDataExchange(CDataExchange* pDX)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFormView::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_FILE_NAME, _FileName);
	DDX_Text(pDX, IDC_FIE_EXT, _FileExt);

	DDX_Text(pDX, IDC_Mouse_X, _X);
	DDX_Text(pDX, IDC_Mouse_Y, _Y);

	DDX_Text(pDX, IDC_FILE_WIDTH, _Width);
	DDX_Text(pDX, IDC_FILE_HEIGHT, _Height);

	//DDX_Control(pDX, IDC_RGB_R, _RGB_Control_R);
	//DDX_Control(pDX, IDC_RGB_G, _RGB_Control_G);
	//DDX_Control(pDX, IDC_RGB_B, _RGB_Control_B);


	

	

}


void CProject1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//Invalidate();

	
		

	CFormView::OnTimer(nIDEvent);
}


void CProject1View::OnBnClickedFrameBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	_AniBtn = TRUE;

	//CString str1;
	//CString str2;
	//CString str3;

	//_RGB_Control_R.GetWindowText(str1);
	//_RGB_Control_G.GetWindowText(str2);
	//_RGB_Control_B.GetWindowText(str3);

	RGB_R = GetDlgItemInt(IDC_RGB_R);
	RGB_G = GetDlgItemInt(IDC_RGB_G);
	RGB_B = GetDlgItemInt(IDC_RGB_B);

	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();

	Vfr->_AniView->Color_R = RGB_R;
	Vfr->_AniView->Color_G = RGB_G;
	Vfr->_AniView->Color_B = RGB_B;
	//Vfr->_AniView->UpdateData(FALSE);

	

	//Vfr->_infoView->_Width = _imgWidth;
	//Vfr->_infoView->Invalidate();
	//Vfr->_infoView->_Height = _imgHeight;
	//Vfr->_infoView->Invalidate();
	//Vfr->_infoView->UpdateData(FALSE);
}


void CProject1View::OnBnClickedButton2()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_FRAME = GetDlgItemInt(IDC_FRAME_ON);

	CMainFrame* Vfr = (CMainFrame*)AfxGetMainWnd();

	Vfr->_AniView->Frame = _FRAME;
	
}
