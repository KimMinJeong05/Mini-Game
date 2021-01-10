#pragma once
#include "afxcmn.h"


// CImageBlendedDlg 대화 상자입니다.

class CImageBlendedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageBlendedDlg)

public:
	CImageBlendedDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageBlendedDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMAGE_BLENDED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	UINT m_nBlended;
	CSliderCtrl m_sldBlend;
};
