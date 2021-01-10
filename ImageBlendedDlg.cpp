// ImageBlendedDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "2018111384_Final1.h"
#include "ImageBlendedDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "2018111384_Final1Doc.h"
#include "2018111384_Final1View.h"


// CImageBlendedDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageBlendedDlg, CDialogEx)

CImageBlendedDlg::CImageBlendedDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMAGE_BLENDED, pParent)
	, m_nBlended(0)
{

}

CImageBlendedDlg::~CImageBlendedDlg()
{
}

void CImageBlendedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BLENDED, m_nBlended);
	DDX_Control(pDX, IDC_SLIDER_BLENDED, m_sldBlend);
}


BEGIN_MESSAGE_MAP(CImageBlendedDlg, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CImageBlendedDlg 메시지 처리기입니다.


BOOL CImageBlendedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2018111384_Final1View *pView = (CMy2018111384_Final1View*)pFrame->GetActiveView();

	m_sldBlend.SetRange(1, 100);
	m_nBlended = pView->m_nImageBlended;
	m_sldBlend.SetPos(m_nBlended);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CImageBlendedDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_SLIDER_BLENDED == pScrollBar->GetDlgCtrlID()) {
		m_nBlended = m_sldBlend.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
