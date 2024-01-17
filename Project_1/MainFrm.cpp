
// MainFrm.cpp: CMainFrame 클래스의 구현
//

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


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_BMP_BMP, &CMainFrame::OnBmpBmp)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	m_blsSplitter = FALSE;
}

void CMainFrame::ResizeSplitter()
{
	if (!m_blsSplitter)
	{
		return;
	}

	CRect rect;
	GetClientRect(&rect);

	m_wndSplitter01.SetColumnInfo(0, 250, 80);

	//DIb 뷰 높이	
	m_wndSplitter02.SetRowInfo(0, (rect.bottom * 6) / 10, 150);

	m_wndSplitter02.SetRowInfo(1, (rect.bottom * 3) / 10, 50);

	//DIv뷰 넓이
	m_wndSplitter03.SetColumnInfo(0, (rect.bottom * 12) / 10, 150);

	//애니메이션 뷰
	m_wndSplitter04.SetRowInfo(0, (rect.bottom * 33) / 100, 150);

	m_wndSplitter01.RecalcLayout();
	m_wndSplitter02.RecalcLayout();
	m_wndSplitter03.RecalcLayout();
	m_wndSplitter04.RecalcLayout();

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT)))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{

	if (!m_wndSplitter01.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter02.CreateStatic(&m_wndSplitter01, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter01.IdFromRowCol(0, 1)))
		return FALSE;

	if (!m_wndSplitter03.CreateStatic(&m_wndSplitter02, 1, 2, WS_CHILD | WS_VISIBLE, m_wndSplitter02.IdFromRowCol(0, 0)))
		return FALSE;

	if (!m_wndSplitter04.CreateStatic(&m_wndSplitter03, 2, 1, WS_CHILD | WS_VISIBLE, m_wndSplitter03.IdFromRowCol(0, 1)))
		return FALSE;
	

	//return m_wndSplitter.Create(this,
	//	2, 2,               // TODO: 행 및 열의 개수를 조정합니다.
	//	CSize(10, 10),      // TODO: 최소 창 크기를 조정합니다.
	//	pContext);
	
	m_wndSplitter01.CreateView(0, 0, RUNTIME_CLASS(CProject1View),CSize(80,80),pContext);

	m_wndSplitter02.CreateView(1, 0, RUNTIME_CLASS(COtherView), CSize(30, 30), pContext);

	m_wndSplitter03.CreateView(0, 0, RUNTIME_CLASS(Dibview), CSize(40, 40), pContext);

	m_wndSplitter04.CreateView(0, 0, RUNTIME_CLASS(CAnimationView), CSize(50, 50), pContext);

	m_wndSplitter04.CreateView(1, 0, RUNTIME_CLASS(CPivotView), CSize(50, 50), pContext);


	_infoView =((CProject1View*)m_wndSplitter01.GetPane(0, 0));
	_SpriteView = ((COtherView*)m_wndSplitter02.GetPane(1, 0));
	_DibView = ((Dibview*)m_wndSplitter03.GetPane(0, 0));
	_AniView = ((CAnimationView*)m_wndSplitter04.GetPane(0, 0));
	_PivotView = ((CPivotView*)m_wndSplitter04.GetPane(1, 0));

	m_blsSplitter = TRUE;

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ResizeSplitter();
}


void CMainFrame::OnBmpBmp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CProject1Doc* pDoc = (CProject1Doc*)GetActiveDocument();
	CString str = _T("bmp files(*.bmp)|*.bmp|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString PathName = dlg.GetPathName();
		CString FileName = PathName.Right(PathName.GetLength() - PathName.ReverseFind('\\') - 1);
		CString ExName = PathName.Right(PathName.GetLength() - PathName.Find('.') - 1);
		CString EXTName = dlg.GetFileExt();

		_infoView->_FileName = FileName;
		_infoView->_FileExt = EXTName;
		_SpriteView->_FileName = FileName;
		_AniView->_IMGNAME_ANI = FileName;
		_DibView->_IMGNAME = FileName;
		_PivotView->_IMGNAME_Pivot = FileName;
		//if (ExName.CompareNoCase("bmp") == 0)
		//{
		//	pDoc->m_Dib.LoadFile(PathName);
			//_infoView->UpdateData(FALSE);
		//}
		


		MessageBox(dlg.GetPathName());
	}

	

	_infoView -> UpdateData(FALSE);
	_DibView->UpdateData(FALSE);
	_AniView->UpdateData(FALSE);
	_SpriteView->UpdateData(FALSE);

	InvalidateRect(NULL);
	//CImage spriteimage;
	//spriteimage.Load(str);

}
