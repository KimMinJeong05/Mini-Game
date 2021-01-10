#pragma once
#include "afxcmn.h"


// CImageSizeDlg 대화 상자입니다.

class CImageSizeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageSizeDlg)

public:
	CImageSizeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageSizeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_SIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nImageSize;
	CSliderCtrl m_sldImageSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
