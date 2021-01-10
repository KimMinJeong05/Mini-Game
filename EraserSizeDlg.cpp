// EraserSizeDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "2018111384_Final1.h"
#include "EraserSizeDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "2018111384_Final1Doc.h"
#include "2018111384_Final1View.h"


// CEraserSizeDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CEraserSizeDlg, CDialogEx)

CEraserSizeDlg::CEraserSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ERASER, pParent)
	, m_nEraserSize(0)
{

}

CEraserSizeDlg::~CEraserSizeDlg()
{
}

void CEraserSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ERASER, m_nEraserSize);
	DDX_Control(pDX, IDC_SPIN_ERASER, m_spinEraser);
}


BEGIN_MESSAGE_MAP(CEraserSizeDlg, CDialogEx)
END_MESSAGE_MAP()


// CEraserSizeDlg �޽��� ó�����Դϴ�.


BOOL CEraserSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMy2018111384_Final1View *pView = (CMy2018111384_Final1View*)pFrame->GetActiveView();

	m_spinEraser.SetRange(2, 20);
	m_nEraserSize = pView->m_nEraserSize;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
