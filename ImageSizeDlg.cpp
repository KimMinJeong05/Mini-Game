// ImageSizeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "2018111384_Final1.h"
#include "ImageSizeDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "2018111384_Final1Doc.h"
#include "2018111384_Final1View.h"


// CImageSizeDlg ��ȭ �����Դϴ�.

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


// CImageSizeDlg �޽��� ó�����Դϴ�.


BOOL CImageSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2018111384_Final1View *pView = (CMy2018111384_Final1View*)pFrame->GetActiveView();

	m_sldImageSize.SetRange(1, 100);
	m_nImageSize = pView->m_nImageSize;
	m_sldImageSize.SetPos(m_nImageSize);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CImageSizeDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(IDC_SLIDER_IMAGE_SIZE == pScrollBar->GetDlgCtrlID()) {
		m_nImageSize = m_sldImageSize.GetPos();
		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
