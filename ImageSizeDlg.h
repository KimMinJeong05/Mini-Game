#pragma once
#include "afxcmn.h"


// CImageSizeDlg ��ȭ �����Դϴ�.

class CImageSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageSizeDlg)

public:
	CImageSizeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageSizeDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_SIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nImageSize;
	CSliderCtrl m_sldImageSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
