
// 2018111384_Final1View.cpp : CMy2018111384_Final1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "2018111384_Final1.h"
#endif

#include "2018111384_Final1Doc.h"
#include "2018111384_Final1View.h"
#include "MainFrm.h"
#include "PenSizeDlg.h"
#include "EraserSizeDlg.h"
#include "ImageSizeDlg.h"
#include "ImageBlendedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2018111384_Final1View

IMPLEMENT_DYNCREATE(CMy2018111384_Final1View, CFormView)

BEGIN_MESSAGE_MAP(CMy2018111384_Final1View, CFormView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_PEN_SIZE, &CMy2018111384_Final1View::OnPenSize)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMy2018111384_Final1View::OnClickedButtonSave)
	ON_COMMAND(ID_ERASER_SIZE, &CMy2018111384_Final1View::OnEraserSize)
	ON_COMMAND(ID_PEN_COLOR, &CMy2018111384_Final1View::OnPenColor)
	ON_CBN_SELCHANGE(IDC_COMBO_GAME, &CMy2018111384_Final1View::OnSelchangeComboGame)
	ON_COMMAND(IDC_RADIO_LEVEL1, &CMy2018111384_Final1View::OnRadioLevel1)
	ON_COMMAND(IDC_RADIO_LEVEL2, &CMy2018111384_Final1View::OnRadioLevel2)
	ON_COMMAND(ID_PEN, &CMy2018111384_Final1View::OnPen)
	ON_COMMAND(ID_ERASER, &CMy2018111384_Final1View::OnEraser)
	ON_BN_CLICKED(IDC_BUTTON_HINT, &CMy2018111384_Final1View::OnClickedButtonHint)
	ON_COMMAND(IDC_RADIO_LEVEL3, &CMy2018111384_Final1View::OnRadioLevel3)
	ON_COMMAND(ID_IMAGE_LOAD, &CMy2018111384_Final1View::OnImageLoad)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_IMAGE_SIZE, &CMy2018111384_Final1View::OnImageSize)
	ON_COMMAND(ID_IMAGE_BLENDED, &CMy2018111384_Final1View::OnImageBlended)
	ON_COMMAND(ID_IMAGE_CUT, &CMy2018111384_Final1View::OnImageCut)
	ON_COMMAND(ID_IMAGE_POSITION, &CMy2018111384_Final1View::OnImagePosition)
	ON_COMMAND(ID_NEW, &CMy2018111384_Final1View::OnNew)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CMy2018111384_Final1View ����/�Ҹ�

CMy2018111384_Final1View::CMy2018111384_Final1View()
	: CFormView(IDD_MY2018111384_FINAL1_FORM)
	, m_ncurLevel(0)
	, m_nPenSize(0)
	, m_ptDrawPrev(0)
	, m_nEraserSize(0)
	, m_nGame(0)
	, m_nDrawObject(0)
	, m_nheart(0)
	, m_strChance(_T(""))
	, m_nhint(0)
	, m_nAnswerSize(0)
	, m_strFilePath(_T(""))
	, m_bLButtonDown(false)
	, m_nImageSize(100)
	, m_strPreFilePath(_T(""))
	, m_ptPicture(0)
	, m_nImageBlended(100)
	, m_ptCutStart(0)
	, m_ptCutPre(0)
	, m_ntime1(0)
	, m_ntime2(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMy2018111384_Final1View::~CMy2018111384_Final1View()
{
}

void CMy2018111384_Final1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_GAME, m_cbGame);
	DDX_Control(pDX, IDC_PICTURE_2, m_Pic2);
	//  DDX_Control(pDX, IDC_EDIT_CHANCE, m_strChance);
	DDX_Text(pDX, IDC_EDIT_CHANCE, m_strChance);
}

BOOL CMy2018111384_Final1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CFormView::PreCreateWindow(cs);
}

void CMy2018111384_Final1View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	GetDlgItem(IDC_PICTURE_1)->GetWindowRect(&m_picture1_rect);
	ScreenToClient(&m_picture1_rect);
	m_picture1_rect.DeflateRect(1, 1, 1, 1);
	GetDlgItem(IDC_PICTURE_2)->GetWindowRect(&m_picture2_rect);
	ScreenToClient(&m_picture2_rect);
	m_picture2_rect.DeflateRect(1, 1, 1, 1);

	m_nAnswerSize = 7;
	for (int i = 0;i < m_nAnswerSize;i++) m_bCorrect[i] = false;
	m_nGame = -1;
	m_nheart = 5;
	m_nhint = 0;
	GetDlgItem(IDC_EDIT_CHANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_HINT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CHANCE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_LEVEL1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_LEVEL2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RADIO_LEVEL3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_CHANCE2)->SetWindowText(_T("���� ��ȸ: "));
	//�׸� �׸���
	m_nPenSize = 2;
	m_nEraserSize = 4;
	m_colorPen = RGB(0, 0, 0);
}


// CMy2018111384_Final1View ����

#ifdef _DEBUG
void CMy2018111384_Final1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy2018111384_Final1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy2018111384_Final1Doc* CMy2018111384_Final1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2018111384_Final1Doc)));
	return (CMy2018111384_Final1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2018111384_Final1View �޽��� ó����


void CMy2018111384_Final1View::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CMy2018111384_Final1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	if (m_nGame == 0) { //Ʋ���׸� ã��
		CDC mendc;
		mendc.CreateCompatibleDC(pDC); //�޸� ����
		CBitmap bitmap1, *oldbitmap1;

		CDC mendc2;
		mendc2.CreateCompatibleDC(pDC); //�޸� ����
		CBitmap bitmap2, *oldbitmap2;
		if (m_ncurLevel == 1) {
			bitmap1.LoadBitmap(IDB_BITMAP1_1);//��Ʈ�� �б�
			bitmap2.LoadBitmap(IDB_BITMAP1_2);//��Ʈ�� �б�
		}else if (m_ncurLevel == 2) {
			bitmap1.LoadBitmap(IDB_BITMAP2_1);//��Ʈ�� �б�
			bitmap2.LoadBitmap(IDB_BITMAP2_2);//��Ʈ�� �б�
		}
		else if(m_ncurLevel == 3) {
			bitmap1.LoadBitmap(IDB_BITMAP3_1);//��Ʈ�� �б�
			bitmap2.LoadBitmap(IDB_BITMAP3_2);//��Ʈ�� �б�
		}
		else {
			return;
		}

		oldbitmap1 = mendc.SelectObject(&bitmap1);//�޸�DC�� ��Ʈ�� ����
		BITMAP bmpinfo1;//��Ʈ�� ����
		bitmap1.GetBitmap(&bmpinfo1);//���ҽ����� ��Ʈ�� ���� ��������
		mendc.SelectObject(&bitmap1);
		BLENDFUNCTION bf1; //���� ����
		bf1.BlendOp = AC_SRC_OVER;
		bf1.BlendFlags = 0;
		bf1.AlphaFormat = 0;
		int sizeControl1 = (m_picture1_rect.right - m_picture1_rect.left) - bmpinfo1.bmWidth;
		if (bmpinfo1.bmHeight + sizeControl1 > m_picture1_rect.bottom - m_picture1_rect.top) {
			sizeControl1 = (m_picture1_rect.bottom - m_picture1_rect.top) - bmpinfo1.bmHeight;
		}
		pDC->StretchBlt(m_picture1_rect.left, m_picture1_rect.top, bmpinfo1.bmWidth + sizeControl1, bmpinfo1.bmHeight + sizeControl1, &mendc, 0, 0, bmpinfo1.bmWidth, bmpinfo1.bmHeight, SRCCOPY);

		oldbitmap2 = mendc.SelectObject(&bitmap2);//�޸�DC�� ��Ʈ�� ����
		BITMAP bmpinfo2;//��Ʈ�� ����
		bitmap2.GetBitmap(&bmpinfo2);//���ҽ����� ��Ʈ�� ���� ��������
		mendc.SelectObject(&bitmap2);
		BLENDFUNCTION bf2; //���� ����
		bf2.BlendOp = AC_SRC_OVER;
		bf2.BlendFlags = 0;
		bf2.AlphaFormat = 0;
		int sizeControl2 = (m_picture2_rect.right - m_picture2_rect.left) - bmpinfo2.bmWidth;
		if (bmpinfo2.bmHeight + sizeControl2 > m_picture2_rect.bottom-m_picture2_rect.top) {
			sizeControl2 = (m_picture2_rect.bottom - m_picture2_rect.top) - bmpinfo2.bmHeight;
		}
		pDC->StretchBlt(m_picture2_rect.left, m_picture2_rect.top, bmpinfo2.bmWidth + sizeControl2, bmpinfo2.bmHeight + sizeControl2, &mendc, 0, 0, bmpinfo2.bmWidth, bmpinfo2.bmHeight, SRCCOPY);

		//GDI
		Graphics graphics(*pDC);
		Pen RedPen(Color(200, 255, 0, 0), 5);
		for (int i = 0;i < m_nAnswerSize;i++) { //���� ���׶��
			if (m_bCorrect[i] == true) {
				graphics.DrawEllipse(&RedPen, m_pAnswer[i].x - 15, m_pAnswer[i].y - 15, 30, 30);
			}
		}
	}
	else if(m_nGame == 1){//�̴� �׸���
		CImage m_img;
		CWnd *pWnd = (CWnd*)GetDlgItem(IDC_PICTURE_2);
		CDC *dc = pWnd->GetDC();

		if (m_nDrawObject == 4 && m_strFilePath != "") {//���� �̹��� �ҷ�����
			m_strPreFilePath = m_strFilePath;
			m_img.Load(m_strFilePath);
			int sizeControl = (m_picture2_rect.right - m_picture2_rect.left) - m_img.GetWidth();
			if (m_img.GetHeight() + sizeControl > m_picture2_rect.bottom - m_picture2_rect.top) {
				sizeControl = (m_picture2_rect.bottom - m_picture2_rect.top) - m_img.GetHeight();
			}
			m_ptPictureSize.x = (m_img.GetWidth() + sizeControl);
			m_ptPictureSize.y = (m_img.GetHeight() + sizeControl);
			m_strFilePath = "";
		}
		if (m_nDrawObject == 3 && m_strPreFilePath != "") { //�̹��� ũ�� ����
			m_img.Load(m_strPreFilePath);
			int sizeControl = (m_picture2_rect.right - m_picture2_rect.left) - m_img.GetWidth();
			if (m_img.GetHeight() + sizeControl > m_picture2_rect.bottom - m_picture2_rect.top) {
				sizeControl = (m_picture2_rect.bottom - m_picture2_rect.top) - m_img.GetHeight();
			}
			m_ptPictureSize.x = (m_img.GetWidth() + sizeControl)*(float)(m_nImageSize / 100.0);
			m_ptPictureSize.y = (m_img.GetHeight() + sizeControl)*(float)(m_nImageSize / 100.0);
		}
		if (m_nDrawObject == 5 && m_strPreFilePath != "") {//�̹��� ���� ����
			m_img.Load(m_strPreFilePath);
		}
		if (m_nDrawObject == 7 && m_strPreFilePath != "") {//�̹��� ��ġ ����
			m_img.Load(m_strPreFilePath);
			m_nDrawObject = 0;
		}
		if (!m_img.IsNull()) {//���
							  //255�� �������ε� �߰����� 255������ �� ���̰� ����.
			m_img.AlphaBlend(dc->m_hDC, m_ptPicture.x, m_ptPicture.y, m_ptPictureSize.x, m_ptPictureSize.y, 0, 0, m_img.GetWidth(), m_img.GetHeight(), 255 * (float)(m_nImageBlended / 100.0));
		}
	}
}


void CMy2018111384_Final1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	//���������� ������
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("���콺 ��ġ x: %d, y: %d"), point.x, point.y);
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);//�ҿ� ���

	//�׸� �׸���
	if (m_nGame == 1&& nFlags == MK_LBUTTON) {
		CClientDC dc(this);
		Graphics graphics(dc);
		Gdiplus::Color clr;
		clr.SetFromCOLORREF(m_colorPen);

		if (m_nDrawObject == 1 &&m_bLButtonDown&& nFlags == MK_LBUTTON) {//�� �׸���
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_Pen);
			SetCursor(hCursor);
			Pen pen(Color(clr), m_nPenSize);
			graphics.DrawLine(&pen, m_ptDrawPrev.x, m_ptDrawPrev.y, point.x, point.y);
			m_ptDrawPrev = point;
		}
		if (m_nDrawObject == 2 && m_bLButtonDown&& nFlags == MK_LBUTTON) {//���찳�� �����
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ERASER);
			SetCursor(hCursor);
			Pen pen(Color(240, 240, 240), m_nEraserSize);;
			graphics.DrawLine(&pen, m_ptDrawPrev.x, m_ptDrawPrev.y, point.x, point.y);
			m_ptDrawPrev = point;
		}
		if (m_nDrawObject == 6&& m_bLButtonDown && nFlags == MK_LBUTTON) {//�̹��� �ڸ����� �� ���
			CPen pen, *oldpen;
			pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
			oldpen = dc.SelectObject(&pen);
			dc.SetROP2(R2_NOTXORPEN);
			dc.Rectangle(m_ptCutStart.x, m_ptCutStart.y, m_ptCutPre.x, m_ptCutPre.y);
			dc.Rectangle(m_ptCutStart.x, m_ptCutStart.y, point.x, point.y);
			m_ptCutPre = point;
			dc.SelectObject(oldpen);
			pen.DeleteObject();
		}
	}
	CFormView::OnMouseMove(nFlags, point);
}


void CMy2018111384_Final1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_nGame == 0) { // Ʋ���׸�ã��
		bool mius = true;
		for (int i = 0;i < m_nAnswerSize;i++) {
				if (point.x <= m_pAnswer[i].x + 20 && point.x >= m_pAnswer[i].x - 20
					&& point.y <= m_pAnswer[i].y + 20 && point.y >= m_pAnswer[i].y - 20) {
					m_bCorrect[i] = true;
					mius = false;
					break;
				}
		}
		if (mius) {
			if (m_picture2_rect.left <= point.x && m_picture2_rect.right >= point.x
				&& m_picture2_rect.top <= point.y && m_picture2_rect.bottom >= point.y) { //���� picture contorl ���̸� mius����
				m_nheart--;
				m_strChance.Format(_T("%d"), m_nheart);
				UpdateData(FALSE);
				if (m_nheart == 0) {//���� ��ȸ�� ���� ��
					KillTimer(1);
					AfxMessageBox(_T("���� ��ȸ�� �����ϴ�!\n�ٽ� ó������ �������ּ���"), MB_ICONINFORMATION);
					Game1Reset();
					SetTimer(1, 1000, NULL);
				}
				m_strChance.Format(_T("%d"), m_nheart);
				UpdateData(FALSE);
			}
		}
		Invalidate();
		bool finish = true; // �� ã��
		for (int i = 0; i < m_nAnswerSize; i++) {
			if (!m_bCorrect[i]) {
				finish = false;
				break;
			}
		}
		if (finish) {
			KillTimer(1);
			AfxMessageBox(_T("Ʋ�� �׸��� �� ã�ҽ��ϴ�!\n�ٸ� ���ӵ� �غ�����!"), MB_ICONINFORMATION);
		}
	}
	else if(m_nGame==1){//�̴� �׸���
		m_ptDrawPrev = point;
		if (m_ptDrawPrev.x<m_picture2_rect.left|| m_ptDrawPrev.x>m_picture2_rect.right
			|| m_ptDrawPrev.y<m_picture2_rect.top|| m_ptDrawPrev.y>m_picture2_rect.bottom) {
			//�׸��� �ۿ��� Ŭ���ϸ� �ƹ��ϵ� �� �Ͼ�� ��.
			m_bLButtonDown = false;
			return;
		}
		CRect rectP2;
		SetCapture();
		GetDlgItem(IDC_PICTURE_2)->GetWindowRect(&rectP2);
		m_bLButtonDown = true;
		if (m_nDrawObject == 1) {//�� �׸���
			rectP2.DeflateRect(m_nPenSize, m_nPenSize, m_nPenSize, m_nPenSize);
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_Pen);
			SetCursor(hCursor);
		}
		else if (m_nDrawObject == 2) {//���찳�� �����
			rectP2.DeflateRect(m_nEraserSize-1, m_nEraserSize-1, m_nEraserSize-1, m_nEraserSize-1);//�׸��� �׵θ� �������� �ʵ���
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ERASER);
			SetCursor(hCursor);
		}
		else if (m_nDrawObject == 6) {//�̹��� �ڸ���
			m_ptCutStart = m_ptCutPre = point;
		}
		else if (m_nDrawObject == 7) {//�̹��� �ű��
			m_ptPicture.x= point.x - m_picture2_rect.left; m_ptPicture.y=point.y - m_picture2_rect.top;
			//�̹����� �׸��� ������ ������ �� �ϵ��� ��ġ ����
			if (m_ptPicture.x<m_ptPictureSize.x / 2) {
				m_ptPicture.x = 0;
			}
			else if (m_ptPicture.x > m_picture2_rect.right - m_picture2_rect.left - (m_ptPictureSize.x / 2)) {
				m_ptPicture.x = m_picture2_rect.right - m_picture2_rect.left - m_ptPictureSize.x;
			}
			else {
				m_ptPicture.x -= m_ptPictureSize.x / 2;
			}
			if (m_ptPicture.y<m_ptPictureSize.y / 2) {
				m_ptPicture.y = 0;
			}
			else if (m_ptPicture.y > m_picture2_rect.bottom - m_picture2_rect.top - (m_ptPictureSize.y / 2)) {
				m_ptPicture.y = m_picture2_rect.bottom - m_picture2_rect.top - m_ptPictureSize.y;
			}
			else {
				m_ptPicture.y -= m_ptPictureSize.y / 2;
			}
			Invalidate();
		}
		::ClipCursor(&rectP2); //�׸��� ������ ���콺 ����
	}
	CFormView::OnLButtonDown(nFlags, point);
}

void CMy2018111384_Final1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_nGame == 1) {//�̴� �׸���
		if (m_bLButtonDown) {//�׸��� ������ ������ ���콺 ����
			ReleaseCapture();
			::ClipCursor(NULL);
			if (m_nDrawObject == 6) {//�̹��� �ڸ���
				m_nDrawObject = 0;
				CClientDC dc(this); //DC����
				CPen my_pen(PS_SOLID, 1, RGB(240, 240, 240));
				dc.SelectObject(&my_pen); //  ������ ���� DC�� �����Ѵ�.
				SelectObject(dc, GetStockObject(DC_BRUSH));
				SetDCBrushColor(dc, RGB(240, 240, 240));
				dc.Rectangle(m_picture2_rect.left, m_picture2_rect.top, m_picture2_rect.right, m_ptCutStart.y + 1); // �簢���� �׷��ش�.
				dc.Rectangle(m_picture2_rect.left, m_picture2_rect.top, m_ptCutStart.x + 1, m_picture2_rect.bottom);
				dc.Rectangle(point.x - 1, m_picture2_rect.top, m_picture2_rect.right, m_picture2_rect.bottom);
				dc.Rectangle(m_picture2_rect.left, point.y - 1, m_picture2_rect.right, m_picture2_rect.bottom);
			}
			m_bLButtonDown = false;
		}
	}
	CFormView::OnLButtonUp(nFlags, point);
}

//���� �׸� �� �̹��� �����ϱ�(������Ʈ ���Ͽ� �̴ϱ׸���_(��¥).bmp�� �����)
void CMy2018111384_Final1View::OnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int YN = AfxMessageBox(_T("������ ���� �����Ͻðڽ��ϱ�?"), MB_YESNO);
	if (YN == IDYES) {
		CDC* pDC = m_Pic2.GetDC(); HDC hDC = pDC->m_hDC; //picture control ũ�� 
		RECT rc; m_Pic2.GetClientRect(&rc); //��Ʈ�ʻ��� 
		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
		HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap);
		BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hBmpOld); DeleteDC(hMemDC); //��Ʈ�ʻ�缳�� 
		BITMAPINFOHEADER bmih;
		ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = rc.right;
		bmih.biHeight = rc.bottom;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB; // ��Ʈ��(DIB) ������ ���� 
		GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		LPBYTE lpBits = new BYTE[bmih.biSizeImage];
		GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		ReleaseDC(pDC); DeleteObject(hBitmap); // ��Ʈ�� ���� ��� ���� 
		BITMAPFILEHEADER bmfh;
		bmfh.bfType = 'MB';
		bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage;
		bmfh.bfReserved1 = 0; bmfh.bfReserved2 = 0;
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // ���ϸ���
		SYSTEMTIME time; GetLocalTime(&time);
		CString Name;
		Name.Format(_T("�̴ϱ׸���_%4d%2d%2d_%2d%2d%2d.bmp"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		_bstr_t gg(Name); BSTR lpszFileName = gg.copy(); // ��Ʈ�� ���� ���� �� ������ ���� 
		DWORD dwWritten;
		HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);
		CloseHandle(hFile);
		delete[] lpBits;
	}
}

void CMy2018111384_Final1View::OnPenSize() //�� ������ ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- ���� ũ�� -"));
	explain.Append(_T("\r\n���� ũ�⸦ �����غ�����."));
	explain.Append(_T("\r\n���� ũ�⸦ ������ ��, ���� �����ؼ� �׷�������."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	CPenSizeDlg* pdlgPen = new CPenSizeDlg;
	if (pdlgPen->DoModal() == IDOK) m_nPenSize = pdlgPen->m_nPenSize;
}

void CMy2018111384_Final1View::OnEraserSize() //���찳 ������ ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- ���찳�� ũ�� -"));
	explain.Append(_T("\r\n���찳�� ũ�⸦ �����غ�����."));
	explain.Append(_T("\r\n���찳�� ũ�⸦ ������ ��, ���찳�� �����ؼ� �׸��� ����������."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	CEraserSizeDlg* pdlgEraser = new CEraserSizeDlg;
	if (pdlgEraser->DoModal() == IDOK) m_nEraserSize = pdlgEraser->m_nEraserSize;
}

void CMy2018111384_Final1View::OnPenColor() //�� �� ���ϱ�
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- ���� ���� -"));
	explain.Append(_T("\r\n���� ���� ���ϴ� �������� �ٲ㺸����."));
	explain.Append(_T("\r\n���ϴ� ������ �� ��, ���� �����ؼ� �׸��� �׷�������."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK) m_colorPen = colorDlg.GetColor();
}

void CMy2018111384_Final1View::OnSelchangeComboGame() //������ �ٲ� ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_nGame = m_cbGame.GetCurSel();
	CString explain;
	if (m_nGame == 0) { //Ʋ���׸�ã�� ����
		Game1Reset();
		m_ncurLevel = 0;
		m_strChance.Format(_T("%d"), m_nheart);
		CFont g_editFont; CString text1, text2;
		g_editFont.CreatePointFont(200, TEXT("Arial"));
		GetDlgItem(IDC_EDIT_TIME1)->SetFont(&g_editFont);
		GetDlgItem(IDC_EDIT_TIME2)->SetFont(&g_editFont);
		text1.Format(_T("%01d"), m_ntime1);
		text2.Format(_T(": %02d"), m_ntime2);
		GetDlgItem(IDC_EDIT_TIME1)->SetWindowText(text1);
		GetDlgItem(IDC_EDIT_TIME2)->SetWindowText(text2);
		UpdateData(FALSE);
		((CButton*)GetDlgItem(IDC_RADIO_LEVEL1))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_LEVEL2))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO_LEVEL3))->SetCheck(0);
		GetDlgItem(IDC_EDIT_CHANCE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_HINT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_LEVEL1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_LEVEL2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_RADIO_LEVEL3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_EXPLAIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_CHANCE2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TIME1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TIME2)->ShowWindow(SW_SHOW);
		explain.Format(_T("<Ʋ���׸�ã�� ����>"));
		explain.Append(_T("\r\n1. LEVEL�� �������ּ���."));
		explain.Append(_T("\r\n2. ���� �׸��� ���� ������ �׸����� �ٸ� ���� ���콺 ���� ��ư���� Ŭ�����ּ���."));
		explain.Append(_T("\r\n3. Ŭ���� ���� ������ ���� ���׶�̰�, Ʋ���� ��ȸ�� 1 �پ��ϴ�."));
		explain.Append(_T("\r\n4. ��ȸ�� 0�� �Ǹ� ������ ���з� �����ϴ�. �� �� �ٽ� ó������ ���µ˴ϴ�."));
		explain.Append(_T("\r\n5. ���� �𸣰����� ��ȸ 1���� ����ϰ� ��Ʈ�� �޾ƺ�����.(��Ʈ�� ������ �� 3��)"));
		explain.Append(_T("\r\n   ��Ʈ�� ������ ��ȸ 1���� ��� �� �Ѵٰ� �ϸ� ������ ���� ��Ʈ�� �� �� �ֽ��ϴ�."));
		AfxMessageBox(explain, MB_ICONINFORMATION);
	}else if (m_nGame == 1) { //�̴� �׸��� ����
		KillTimer(1);
		Game2Reset();
		GetDlgItem(IDC_EDIT_CHANCE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_HINT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_LEVEL1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_LEVEL2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_RADIO_LEVEL3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_EXPLAIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_CHANCE2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TIME1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TIME2)->ShowWindow(SW_HIDE);
		explain.Format(_T("<�̴� �׸��� ����>"));
		explain.Append(_T("\r\n�̴� �׸����� ���� �޴��� �ַ� ����մϴ�."));
		explain.Append(_T("\r\n* ���� �ڽ��� �ش� �޴��� ���� ������ ������ �������ּ���."));
		AfxMessageBox(explain, MB_ICONINFORMATION);

		explain.Format(_T("<�̴� �׸��� ����>"));
		explain.Append(_T("\r\n- �̹��� ����- "));
		explain.Append(_T("\r\n�̹����� �����ϰ� ������ �޴��� '�̹���(����) ����'�� �̿��ϼ���"));
		explain.Append(_T("\r\n'���� �ҷ�����': ���ϴ� ������ �����Ͽ� ������ �׸��ǿ� �ҷ�����"));
		explain.Append(_T("\r\n'�̹��� ũ�� ����': �̹����� ũ�⸦ ������ �׸��� ũ�� �������� 1~100% ���̷� �ٲٱ�"));
		explain.Append(_T("\r\n'�̹��� ��ġ ����': �̹����� ��ġ�� ������ �׸��� �ȿ��� �����ϱ�"));
		explain.Append(_T("\r\n'�̹��� ���� ����': �̹����� ������ 1~100%�� �ٲٱ�"));
		explain.Append(_T("\r\n'�̹��� �ڸ���': �̹����� ���ϴ� �κи� �簢�� ���·� �ڸ���"));
		explain.Append(_T("\r\n'���� �����': ������ �׸����� �� �����"));
		explain.Append(_T("\r\n* '�ڸ���'�� �ϸ� �ٸ� ������ �� ��, �ڸ��� ���� ���·� ���ư��ϴ�."));
		explain.Append(_T("\r\n\r\n- �׸� �׸��� -"));
		explain.Append(_T("\r\n�׸��� �׸��� �ʹٸ� �޴��� '�׸��� ����'�� �̿��ϼ���"));
		explain.Append(_T("\r\n'�� ����': ������ �׸��� �׸���"));
		explain.Append(_T("\r\n'���찳 ����': ���찳�� �׸��̳� ������ �����"));
		explain.Append(_T("\r\n'�� ũ��': �� ũ�⸦ �����ϱ�"));
		explain.Append(_T("\r\n'�� ����': ���ϴ� �������� ���� ���� �ٲٱ�"));
		explain.Append(_T("\r\n'���찳 ũ��': ���찳 ũ�⸦ �����ϱ�"));
		GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	}
	Invalidate();
}

void CMy2018111384_Final1View::OnRadioLevel1()//Ʋ���׸�ã�� Level1
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Game1Reset();
	m_ncurLevel = 1;
	m_nAnswerSize = 5;
	KillTimer(1);
	SetTimer(1, 1000, NULL);
	m_strChance.Format(_T("%d"), m_nheart);
	m_pAnswer[0] = CPoint(585,300); m_pAnswer[1] = CPoint(775,410);
	m_pAnswer[2] = CPoint(930,510); m_pAnswer[3] = CPoint(580,540); m_pAnswer[4] = CPoint(885,237);
	UpdateData(FALSE); 
	Invalidate();
}

void CMy2018111384_Final1View::OnRadioLevel2()//Ʋ���׸�ã�� Level2
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Game1Reset();
	m_ncurLevel = 2;
	m_nAnswerSize = 5;
	KillTimer(1);
	SetTimer(1, 1000, NULL);
	m_strChance.Format(_T("%d"), m_nheart);
	m_pAnswer[0] = CPoint(750, 235); m_pAnswer[1] = CPoint(860, 270);
	m_pAnswer[2] = CPoint(685, 300); m_pAnswer[3] = CPoint(895, 460); m_pAnswer[4] = CPoint(642, 260);
	UpdateData(FALSE);
	Invalidate();
}

void CMy2018111384_Final1View::OnRadioLevel3()//Ʋ���׸�ã�� Level3
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	Game1Reset();
	m_ncurLevel = 3;
	m_nAnswerSize = 7;
	KillTimer(1);
	SetTimer(1, 1000, NULL);
	m_strChance.Format(_T("%d"), m_nheart);
	m_pAnswer[0] = CPoint(550,290); m_pAnswer[1] = CPoint(860,280);
	m_pAnswer[2] = CPoint(750,340); m_pAnswer[3] = CPoint(760,565); m_pAnswer[4] = CPoint(700,595);
	m_pAnswer[5] = CPoint(510,495); m_pAnswer[6] = CPoint(895, 380);
	UpdateData(FALSE);
	Invalidate();
}

void CMy2018111384_Final1View::OnPen()//�� ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawObject = 1;
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- �� ���� -"));
	explain.Append(_T("\r\n������ �׸��ǿ� �ȿ��� ���콺�� ������ ������ �׸��� �׷�������."));
	explain.Append(_T("\r\n���� ���̳� ũ�⸦ �ٲٰ� ������ �޴����� �ٲټ���."));
	explain.Append(_T("\r\n* ������ �׸����� ����� �׸� �� �����ϴ�!"));
	explain.Append(_T("\r\n* ������ �׸��ǿ��� ���콺�� ������ ������ ������ �׸������� �����Ǿ�"));
	explain.Append(_T("\r\n  ������ �׸��ǿ����� �׸� �� �ֵ��� �Ǿ� �ֽ��ϴ�."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}

void CMy2018111384_Final1View::OnEraser()//���찳 ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawObject = 2;
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- ���찳 ���� -"));
	explain.Append(_T("\r\n������ �׸��ǿ� �ȿ��� ���콺�� ������ ������ �׸�(����)�� ����������."));
	explain.Append(_T("\r\n���찳�� ũ�⸦ �ٲٰ� ������ �޴����� �ٲټ���."));
	explain.Append(_T("\r\n* ������ �׸����� ����� ���� �� �����ϴ�!"));
	explain.Append(_T("\r\n* ������ �׸��ǿ��� ���콺�� ������ ������ ������ �׸������� �����Ǿ�"));
	explain.Append(_T("\r\n  ������ �׸��ǿ����� ���� �� �ֵ��� �Ǿ� �ֽ��ϴ�."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}

void CMy2018111384_Final1View::OnClickedButtonHint()//Ʋ���׸�ã�⿡�� ��Ʈ�����ֱ�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//1�� �� �����ϰ� �ϱ�
	int YN = AfxMessageBox(_T("��Ʈ�� ����ϸ� ��ȸ�� 1�� �پ��ϴ�."), MB_YESNO);
	CString level[3];
	if (m_ncurLevel == 1) {//level1
		level[0] = _T("������ 5���Դϴ�."); level[1] = _T("\nƲ�� ������ Ŭ ��� ����� �����ϼ���.");level[2] = _T("\n������ �ڼ��� ������.");
	}
	else if (m_ncurLevel == 2) {//level2
		level[0] = _T("������ 5���Դϴ�."); level[1] = _T("\n����⸦ �ڼ��� ������.");level[2] = _T("\n������ ���� ���� 2���ֽ��ϴ�.");
	}
	else if (m_ncurLevel == 3) {//level3
		level[0] = _T("������ 7���Դϴ�."); level[1] = _T("\n�ϴ��� �ڼ��� ������.");level[2] = _T("\n���̰��� ������ �ڼ��� ������.");
	}
	CString temp;
	temp.Format(_T("<���� ������ �ִ� ��Ʈ�Դϴ�>\n"));
	if (YN == IDYES) {//����Ѵٰ� �ߴٸ�
		if (m_nhint == 3) {//��Ʈ �� ����ϸ� ��ȸ ���� �ʰ� ���� ��Ʈ �����ֱ�
			temp.Append(_T("!��Ʈ�� �� ����߽��ϴ�!\n"));
			for (int i = 0;i < m_nhint;i++) {
				temp.Append(level[i]);
			}
			AfxMessageBox(temp, MB_ICONINFORMATION);
			return;
		}
		else {//��ȸ 1�����ϰ� ���ο� ��Ʈ �����ֱ�
			if (m_nheart == 1) {
				AfxMessageBox(_T("��ȸ�� 1�� ���Ƽ� ��Ʈ�� ������� ���մϴ�."), MB_ICONINFORMATION);
			}
			else {
				m_nheart--;
				m_strChance.Format(_T("%d"), m_nheart);
				m_nhint++;
				for (int i = 0;i < m_nhint;i++) {
					temp.Append(level[i]);
				}
				UpdateData(FALSE);
				AfxMessageBox(temp, MB_ICONINFORMATION);
			}
		}
	}
	else {//��Ʈ�� ������� �ʴ´� �ϸ�, ������ ��� ��Ʈ�� �ٽ� �����ֱ�
		for (int i = 0;i < m_nhint;i++) {
			temp.Append(level[i]);
		}
		AfxMessageBox(temp, MB_ICONINFORMATION);
	}
}

void CMy2018111384_Final1View::OnImageLoad() //���ο� �̹��� �ε�
{
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- ���� �ҷ����� -"));
	explain.Append(_T("\r\n���ϴ� ��Ʈ��(.bmp)������ ���Ϸ� �ҷ��� �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n�̹��� ������ �������ּ���!"));
	explain.Append(_T("\r\n�̹��� ������ ������ �׸��ǿ� �׷����ϴ�."));
	explain.Append(_T("\r\n�̹����� �����ϰ� ������ �޴��� '�̹���(����) ����'�� �̿��ϼ���"));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString str = _T("All files(*.*)|*.*|"); // ��� ���� ǥ��
											 // _T("Excel ���� (*.xls, *.xlsx) |*.xls; *.xlsx|"); �� ���� Ȯ���ڸ� �����Ͽ� ǥ���� �� ����
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	if (dlg.DoModal() == IDOK)
	{
		m_nDrawObject = 4;
		m_nImageSize=100;
		m_strFilePath= dlg.GetPathName();
		m_nImageBlended = 100;
		m_ptPicture.x = 0;m_ptPicture.y = 0;
		Invalidate();
	}
}

void CMy2018111384_Final1View::OnImageSize() //�̹��� ũ�� ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageSizeDlg* pdlgImageSize = new CImageSizeDlg;
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- �̹��� ũ�� ���� -"));
	explain.Append(_T("\r\n���� �ε�� �̹����� ũ�⸦ ������ �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n* ������ �׸����� �������� 1~100%���� ���� �� �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n  100%�̸� ������ �׸��ǿ��� �ִ�� ũ���� ũ�� �Դϴ�."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	if (pdlgImageSize->DoModal() == IDOK) {
		m_nDrawObject = 3;
		m_nImageSize = pdlgImageSize->m_nImageSize;
		Invalidate();
	}
}

void CMy2018111384_Final1View::OnImageBlended() //�̹��� ���� ����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageBlendedDlg* pdlgImageBlended = new CImageBlendedDlg;
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- �̹��� ���� ���� -"));
	explain.Append(_T("\r\n���� �ε�� �̹����� ������ ������ �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n* ������ �׸����� �������� 1~100%���� ���� �� �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n  100%�� �������Դϴ�."));
	explain.Append(_T("\r\n  50~100%�� ���̰� ���� ���� �� �ֽ��ϴ�."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	if (pdlgImageBlended->DoModal() == IDOK) {
		m_nImageBlended = pdlgImageBlended->m_nBlended;
		m_nDrawObject = 5;
		Invalidate();
	}
}

void CMy2018111384_Final1View::OnImageCut() //�̹��� �ڸ���
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawObject = 6;
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- �̹��� �ڸ��� -"));
	explain.Append(_T("\r\n���� �ε�� �̹����� ���ϴ� �簢�� ������� �ڸ� �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n* ���ϴ� �κ��� ���� ����� ���� ���콺�� Ŭ���ϰ� ���ϴ� �簢���� ���� �� �ֵ��� ���콺�� ������ �ּ���. ���ϴ� �簢���� ������ ���� ���콺�� ���ּ���."));
	explain.Append(_T("\r\n* �ڸ��⸦ �� �� �ٸ� �̹��� ������ �ϸ� �ڸ��� ������ �̹����� �����˴ϴ�."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}

void CMy2018111384_Final1View::OnImagePosition() //�̹��� ��ġ
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_nDrawObject = 7;
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- �̹��� ��ġ ���� -"));
	explain.Append(_T("\r\n���� �ε�� �̹����� ������ �׸��� ������ ��ġ ������ �� �� �ֽ��ϴ�."));
	explain.Append(_T("\r\n* '�̹��� ��ġ ����'�� ���� ��"));
	explain.Append(_T("\r\n������ �׸��� �ȿ��� ���ϴ� ��ġ���� ���콺 ������ ������"));
	explain.Append(_T("\r\n�� ������ �߽����� �׸��� ��ġ�� �ٲ�ϴ�."));
	explain.Append(_T("\r\n* �׸��� ���� Ŭ���ϸ� �ƹ��ϵ� �Ͼ�� �ʽ��ϴ�."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}


void CMy2018111384_Final1View::OnNew()// ���� �����
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CString explain;
	explain.Format(_T("<�̴� �׸��� ����>"));
	explain.Append(_T("\r\n- ���� ����� -"));
	explain.Append(_T("\r\n���� ������ �׸����� �� �����ݴϴ�.(�ʱ�ȭ�����ݴϴ�.)"));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	Game2Reset();
	Invalidate();
}


void CMy2018111384_Final1View::OnTimer(UINT_PTR nIDEvent) //Ʋ���׸�ã�⿡�� Ÿ�̸�
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CString text1,text2;
	if (nIDEvent == 1) {
		if (m_ntime2 == 0) {
			m_ntime2 = 59;
			if (m_ntime1 != 0) {
				m_ntime1--;
			}
			else {
				KillTimer(1);
				AfxMessageBox(_T("�ð� �ʰ��� �����߽��ϴ�. �ٽ� �����غ�����!"), MB_ICONINFORMATION);
				Game1Reset();
				m_strChance.Format(_T("%d"), m_nheart);
				Invalidate();
				SetTimer(1, 1000, NULL);
			}
		}
		else {
			m_ntime2--;
		}
		CFont g_editFont;
		g_editFont.CreatePointFont(200, TEXT("Arial"));
		GetDlgItem(IDC_EDIT_TIME1)->SetFont(&g_editFont);
		GetDlgItem(IDC_EDIT_TIME2)->SetFont(&g_editFont);
		text1.Format(_T("%01d"), m_ntime1);
		text2.Format(_T(": %02d"), m_ntime2);
		GetDlgItem(IDC_EDIT_TIME1)->SetWindowText(text1);
		GetDlgItem(IDC_EDIT_TIME2)->SetWindowText(text2);
		UpdateData(FALSE);
	}
	CFormView::OnTimer(nIDEvent);
}


void CMy2018111384_Final1View::Game1Reset()//Ʋ���׸�ã�� �ʱ�ȭ
{
	m_nheart = 5;
	m_nhint = 0;
	m_ntime1 = 3;
	m_ntime2 = 0;
	for (int i = 0;i < 7;i++) m_bCorrect[i] = false;
}


void CMy2018111384_Final1View::Game2Reset()//�̴� �׸��� �ʱ�ȭ
{
	m_strPreFilePath = "";
	m_ptCutPre.x = 0;m_ptCutPre.y = 0;
	m_nImageBlended = 100;
	m_nImageSize = 100;
	m_nPenSize = 2;
	m_nEraserSize = 4;
	m_colorPen = RGB(0, 0, 0);
}
