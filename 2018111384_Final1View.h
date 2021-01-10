
// 2018111384_Final1View.h : CMy2018111384_Final1View Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"
#include "afxwin.h"
#include "atlimage.h"


class CMy2018111384_Final1View : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CMy2018111384_Final1View();
	DECLARE_DYNCREATE(CMy2018111384_Final1View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY2018111384_FINAL1_FORM };
#endif

// Ư���Դϴ�.
public:
	CMy2018111384_Final1Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CMy2018111384_Final1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	int m_ncurLevel;
	virtual void OnDraw(CDC* /*pDC*/);
	CRect m_picture1_rect;
	CRect m_picture2_rect;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint m_pAnswer[7];
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	bool m_bCorrect[7];
	CComboBox m_cbGame;
	int m_nPenSize;
	afx_msg void OnPenSize();
	CPoint m_ptDrawPrev;
	CStatic m_Pic2;
	afx_msg void OnClickedButtonSave();
	int m_nEraserSize;
	COLORREF m_colorPen;
	afx_msg void OnEraserSize();
	afx_msg void OnPenColor();
	afx_msg void OnSelchangeComboGame();
	int m_nGame;
	afx_msg void OnRadioLevel1();
	afx_msg void OnRadioLevel2();
	int m_nDrawObject;
	afx_msg void OnPen();
	afx_msg void OnEraser();
	int m_nheart;
	CString m_strChance;
	afx_msg void OnClickedButtonHint();
	int m_nhint;
	afx_msg void OnRadioLevel3();
	int m_nAnswerSize;
	afx_msg void OnImageLoad();
	CString m_strFilePath;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	bool m_bLButtonDown;
	afx_msg void OnImageSize();
	int m_nImageSize;
	CString m_strPreFilePath;
	CPoint m_ptPicture;
	CPoint m_ptPictureSize;
	int m_nImageBlended;
	afx_msg void OnImageBlended();
	afx_msg void OnImageCut();
	CPoint m_ptCutStart;
	CPoint m_ptCutPre;
	afx_msg void OnImagePosition();
	afx_msg void OnNew();
	int m_ntime1;
	int m_ntime2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Game1Reset();
	void Game2Reset();
};

#ifndef _DEBUG  // 2018111384_Final1View.cpp�� ����� ����
inline CMy2018111384_Final1Doc* CMy2018111384_Final1View::GetDocument() const
   { return reinterpret_cast<CMy2018111384_Final1Doc*>(m_pDocument); }
#endif

