#pragma once
#include "afxcmn.h"


// CImageBlendedDlg ��ȭ �����Դϴ�.

class CImageBlendedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageBlendedDlg)

public:
	CImageBlendedDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageBlendedDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_BLENDED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	UINT m_nBlended;
	CSliderCtrl m_sldBlend;
};
