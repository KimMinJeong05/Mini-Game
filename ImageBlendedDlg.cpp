// ImageBlendedDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "2018111384_Final1.h"
#include "ImageBlendedDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "2018111384_Final1Doc.h"
#include "2018111384_Final1View.h"


// CImageBlendedDlg ��ȭ �����Դϴ�.

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


// CImageBlendedDlg �޽��� ó�����Դϴ�.


BOOL CImageBlendedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2018111384_Final1View *pView = (CMy2018111384_Final1View*)pFrame->GetActiveView();

	m_sldBlend.SetRange(1, 100);
	m_nBlended = pView->m_nImageBlended;
	m_sldBlend.SetPos(m_nBlended);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CImageBlendedDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (IDC_SLIDER_BLENDED == pScrollBar->GetDlgCtrlID()) {
		m_nBlended = m_sldBlend.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
