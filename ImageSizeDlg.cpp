// ImageSizeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "2018111384_Final1.h"
#include "ImageSizeDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "2018111384_Final1Doc.h"
#include "2018111384_Final1View.h"


// CImageSizeDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageSizeDlg, CDialogEx)

CImageSizeDlg::CImageSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_SIZE, pParent)
	, m_nImageSize(0)
{

}

CImageSizeDlg::~CImageSizeDlg()
{
}

void CImageSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IMAGE_SIZE, m_nImageSize);
	DDX_Control(pDX, IDC_SLIDER_IMAGE_SIZE, m_sldImageSize);
}


BEGIN_MESSAGE_MAP(CImageSizeDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CImageSizeDlg 메시지 처리기입니다.


BOOL CImageSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2018111384_Final1View *pView = (CMy2018111384_Final1View*)pFrame->GetActiveView();

	m_sldImageSize.SetRange(1, 100);
	m_nImageSize = pView->m_nImageSize;
	m_sldImageSize.SetPos(m_nImageSize);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CImageSizeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(IDC_SLIDER_IMAGE_SIZE == pScrollBar->GetDlgCtrlID()) {
		m_nImageSize = m_sldImageSize.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
