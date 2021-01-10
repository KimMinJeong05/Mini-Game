
// 2018111384_Final1View.cpp : CMy2018111384_Final1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CMy2018111384_Final1View 생성/소멸

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
	// TODO: 여기에 생성 코드를 추가합니다.

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
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

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
	GetDlgItem(IDC_EDIT_CHANCE2)->SetWindowText(_T("남은 기회: "));
	//그림 그리기
	m_nPenSize = 2;
	m_nEraserSize = 4;
	m_colorPen = RGB(0, 0, 0);
}


// CMy2018111384_Final1View 진단

#ifdef _DEBUG
void CMy2018111384_Final1View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy2018111384_Final1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy2018111384_Final1Doc* CMy2018111384_Final1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2018111384_Final1Doc)));
	return (CMy2018111384_Final1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2018111384_Final1View 메시지 처리기


void CMy2018111384_Final1View::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMy2018111384_Final1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (m_nGame == 0) { //틀린그림 찾기
		CDC mendc;
		mendc.CreateCompatibleDC(pDC); //메모리 생성
		CBitmap bitmap1, *oldbitmap1;

		CDC mendc2;
		mendc2.CreateCompatibleDC(pDC); //메모리 생성
		CBitmap bitmap2, *oldbitmap2;
		if (m_ncurLevel == 1) {
			bitmap1.LoadBitmap(IDB_BITMAP1_1);//비트맵 읽기
			bitmap2.LoadBitmap(IDB_BITMAP1_2);//비트맵 읽기
		}else if (m_ncurLevel == 2) {
			bitmap1.LoadBitmap(IDB_BITMAP2_1);//비트맵 읽기
			bitmap2.LoadBitmap(IDB_BITMAP2_2);//비트맵 읽기
		}
		else if(m_ncurLevel == 3) {
			bitmap1.LoadBitmap(IDB_BITMAP3_1);//비트맵 읽기
			bitmap2.LoadBitmap(IDB_BITMAP3_2);//비트맵 읽기
		}
		else {
			return;
		}

		oldbitmap1 = mendc.SelectObject(&bitmap1);//메모리DC에 비트맵 설정
		BITMAP bmpinfo1;//비트맵 정보
		bitmap1.GetBitmap(&bmpinfo1);//리소스에서 비트맴 정보 가져오기
		mendc.SelectObject(&bitmap1);
		BLENDFUNCTION bf1; //투명도 설정
		bf1.BlendOp = AC_SRC_OVER;
		bf1.BlendFlags = 0;
		bf1.AlphaFormat = 0;
		int sizeControl1 = (m_picture1_rect.right - m_picture1_rect.left) - bmpinfo1.bmWidth;
		if (bmpinfo1.bmHeight + sizeControl1 > m_picture1_rect.bottom - m_picture1_rect.top) {
			sizeControl1 = (m_picture1_rect.bottom - m_picture1_rect.top) - bmpinfo1.bmHeight;
		}
		pDC->StretchBlt(m_picture1_rect.left, m_picture1_rect.top, bmpinfo1.bmWidth + sizeControl1, bmpinfo1.bmHeight + sizeControl1, &mendc, 0, 0, bmpinfo1.bmWidth, bmpinfo1.bmHeight, SRCCOPY);

		oldbitmap2 = mendc.SelectObject(&bitmap2);//메모리DC에 비트맵 설정
		BITMAP bmpinfo2;//비트맵 정보
		bitmap2.GetBitmap(&bmpinfo2);//리소스에서 비트맴 정보 가져오기
		mendc.SelectObject(&bitmap2);
		BLENDFUNCTION bf2; //투명도 설정
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
		for (int i = 0;i < m_nAnswerSize;i++) { //정답 동그라미
			if (m_bCorrect[i] == true) {
				graphics.DrawEllipse(&RedPen, m_pAnswer[i].x - 15, m_pAnswer[i].y - 15, 30, 30);
			}
		}
	}
	else if(m_nGame == 1){//미니 그림판
		CImage m_img;
		CWnd *pWnd = (CWnd*)GetDlgItem(IDC_PICTURE_2);
		CDC *dc = pWnd->GetDC();

		if (m_nDrawObject == 4 && m_strFilePath != "") {//새로 이미지 불러오기
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
		if (m_nDrawObject == 3 && m_strPreFilePath != "") { //이미지 크기 조절
			m_img.Load(m_strPreFilePath);
			int sizeControl = (m_picture2_rect.right - m_picture2_rect.left) - m_img.GetWidth();
			if (m_img.GetHeight() + sizeControl > m_picture2_rect.bottom - m_picture2_rect.top) {
				sizeControl = (m_picture2_rect.bottom - m_picture2_rect.top) - m_img.GetHeight();
			}
			m_ptPictureSize.x = (m_img.GetWidth() + sizeControl)*(float)(m_nImageSize / 100.0);
			m_ptPictureSize.y = (m_img.GetHeight() + sizeControl)*(float)(m_nImageSize / 100.0);
		}
		if (m_nDrawObject == 5 && m_strPreFilePath != "") {//이미지 투명 조절
			m_img.Load(m_strPreFilePath);
		}
		if (m_nDrawObject == 7 && m_strPreFilePath != "") {//이미지 위치 조절
			m_img.Load(m_strPreFilePath);
			m_nDrawObject = 0;
		}
		if (!m_img.IsNull()) {//출력
							  //255가 불투명인데 중간부터 255까지는 별 차이가 없다.
			m_img.AlphaBlend(dc->m_hDC, m_ptPicture.x, m_ptPicture.y, m_ptPictureSize.x, m_ptPictureSize.y, 0, 0, m_img.GetWidth(), m_img.GetHeight(), 255 * (float)(m_nImageBlended / 100.0));
		}
	}
}


void CMy2018111384_Final1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//메인프레임 포인터
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CString strPoint;
	strPoint.Format(_T("마우스 위치 x: %d, y: %d"), point.x, point.y);
	pFrame->m_wndStatusBar.SetPaneText(1, strPoint);//팬에 출력

	//그림 그리기
	if (m_nGame == 1&& nFlags == MK_LBUTTON) {
		CClientDC dc(this);
		Graphics graphics(dc);
		Gdiplus::Color clr;
		clr.SetFromCOLORREF(m_colorPen);

		if (m_nDrawObject == 1 &&m_bLButtonDown&& nFlags == MK_LBUTTON) {//펜 그리기
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_Pen);
			SetCursor(hCursor);
			Pen pen(Color(clr), m_nPenSize);
			graphics.DrawLine(&pen, m_ptDrawPrev.x, m_ptDrawPrev.y, point.x, point.y);
			m_ptDrawPrev = point;
		}
		if (m_nDrawObject == 2 && m_bLButtonDown&& nFlags == MK_LBUTTON) {//지우개로 지우기
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ERASER);
			SetCursor(hCursor);
			Pen pen(Color(240, 240, 240), m_nEraserSize);;
			graphics.DrawLine(&pen, m_ptDrawPrev.x, m_ptDrawPrev.y, point.x, point.y);
			m_ptDrawPrev = point;
		}
		if (m_nDrawObject == 6&& m_bLButtonDown && nFlags == MK_LBUTTON) {//이미지 자르기할 때 경계
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nGame == 0) { // 틀린그림찾기
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
				&& m_picture2_rect.top <= point.y && m_picture2_rect.bottom >= point.y) { //왼쪽 picture contorl 밖이면 mius안함
				m_nheart--;
				m_strChance.Format(_T("%d"), m_nheart);
				UpdateData(FALSE);
				if (m_nheart == 0) {//남은 기회가 없을 때
					KillTimer(1);
					AfxMessageBox(_T("남은 기회가 없습니다!\n다시 처음부터 시작해주세요"), MB_ICONINFORMATION);
					Game1Reset();
					SetTimer(1, 1000, NULL);
				}
				m_strChance.Format(_T("%d"), m_nheart);
				UpdateData(FALSE);
			}
		}
		Invalidate();
		bool finish = true; // 다 찾음
		for (int i = 0; i < m_nAnswerSize; i++) {
			if (!m_bCorrect[i]) {
				finish = false;
				break;
			}
		}
		if (finish) {
			KillTimer(1);
			AfxMessageBox(_T("틀린 그림을 다 찾았습니다!\n다른 게임도 해보세요!"), MB_ICONINFORMATION);
		}
	}
	else if(m_nGame==1){//미니 그림판
		m_ptDrawPrev = point;
		if (m_ptDrawPrev.x<m_picture2_rect.left|| m_ptDrawPrev.x>m_picture2_rect.right
			|| m_ptDrawPrev.y<m_picture2_rect.top|| m_ptDrawPrev.y>m_picture2_rect.bottom) {
			//그림판 밖에서 클릭하면 아무일도 안 일어나게 함.
			m_bLButtonDown = false;
			return;
		}
		CRect rectP2;
		SetCapture();
		GetDlgItem(IDC_PICTURE_2)->GetWindowRect(&rectP2);
		m_bLButtonDown = true;
		if (m_nDrawObject == 1) {//펜 그리기
			rectP2.DeflateRect(m_nPenSize, m_nPenSize, m_nPenSize, m_nPenSize);
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_Pen);
			SetCursor(hCursor);
		}
		else if (m_nDrawObject == 2) {//지우개로 지우기
			rectP2.DeflateRect(m_nEraserSize-1, m_nEraserSize-1, m_nEraserSize-1, m_nEraserSize-1);//그림판 테두리 지워지지 않도록
			HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ERASER);
			SetCursor(hCursor);
		}
		else if (m_nDrawObject == 6) {//이미지 자르기
			m_ptCutStart = m_ptCutPre = point;
		}
		else if (m_nDrawObject == 7) {//이미지 옮기기
			m_ptPicture.x= point.x - m_picture2_rect.left; m_ptPicture.y=point.y - m_picture2_rect.top;
			//이미지가 그림판 밖으로 나가지 못 하도록 위치 조정
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
		::ClipCursor(&rectP2); //그림판 안으로 마우스 고정
	}
	CFormView::OnLButtonDown(nFlags, point);
}

void CMy2018111384_Final1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_nGame == 1) {//미니 그림판
		if (m_bLButtonDown) {//그림판 안으로 고정된 마우스 해제
			ReleaseCapture();
			::ClipCursor(NULL);
			if (m_nDrawObject == 6) {//이미지 자르기
				m_nDrawObject = 0;
				CClientDC dc(this); //DC생성
				CPen my_pen(PS_SOLID, 1, RGB(240, 240, 240));
				dc.SelectObject(&my_pen); //  생성한 팬을 DC에 연결한다.
				SelectObject(dc, GetStockObject(DC_BRUSH));
				SetDCBrushColor(dc, RGB(240, 240, 240));
				dc.Rectangle(m_picture2_rect.left, m_picture2_rect.top, m_picture2_rect.right, m_ptCutStart.y + 1); // 사각형을 그려준다.
				dc.Rectangle(m_picture2_rect.left, m_picture2_rect.top, m_ptCutStart.x + 1, m_picture2_rect.bottom);
				dc.Rectangle(point.x - 1, m_picture2_rect.top, m_picture2_rect.right, m_picture2_rect.bottom);
				dc.Rectangle(m_picture2_rect.left, point.y - 1, m_picture2_rect.right, m_picture2_rect.bottom);
			}
			m_bLButtonDown = false;
		}
	}
	CFormView::OnLButtonUp(nFlags, point);
}

//왼쪽 그림 판 이미지 저장하기(프로젝트 파일에 미니그림판_(날짜).bmp로 저장됨)
void CMy2018111384_Final1View::OnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int YN = AfxMessageBox(_T("오른쪽 판을 저장하시겠습니까?"), MB_YESNO);
	if (YN == IDYES) {
		CDC* pDC = m_Pic2.GetDC(); HDC hDC = pDC->m_hDC; //picture control 크기 
		RECT rc; m_Pic2.GetClientRect(&rc); //비트맵생성 
		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rc.right, rc.bottom);
		HBITMAP hBmpOld = (HBITMAP)SelectObject(hMemDC, hBitmap);
		BitBlt(hMemDC, 0, 0, rc.right, rc.bottom, hDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hBmpOld); DeleteDC(hMemDC); //비트맵사양설정 
		BITMAPINFOHEADER bmih;
		ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = rc.right;
		bmih.biHeight = rc.bottom;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB; // 비트맵(DIB) 데이터 추출 
		GetDIBits(hDC, hBitmap, 0, rc.bottom, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		LPBYTE lpBits = new BYTE[bmih.biSizeImage];
		GetDIBits(hDC, hBitmap, 0, rc.bottom, lpBits, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
		ReleaseDC(pDC); DeleteObject(hBitmap); // 비트맵 파일 헤더 설정 
		BITMAPFILEHEADER bmfh;
		bmfh.bfType = 'MB';
		bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmih.biSizeImage;
		bmfh.bfReserved1 = 0; bmfh.bfReserved2 = 0;
		bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // 파일명설정
		SYSTEMTIME time; GetLocalTime(&time);
		CString Name;
		Name.Format(_T("미니그림판_%4d%2d%2d_%2d%2d%2d.bmp"), time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		_bstr_t gg(Name); BSTR lpszFileName = gg.copy(); // 비트맵 파일 생성 및 데이터 저장 
		DWORD dwWritten;
		HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, &bmfh, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
		WriteFile(hFile, &bmih, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
		WriteFile(hFile, lpBits, bmih.biSizeImage, &dwWritten, NULL);
		CloseHandle(hFile);
		delete[] lpBits;
	}
}

void CMy2018111384_Final1View::OnPenSize() //펜 사이즈 조절
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 펜의 크기 -"));
	explain.Append(_T("\r\n펜의 크기를 조절해보세요."));
	explain.Append(_T("\r\n펜의 크기를 조절한 후, 펜을 선택해서 그려보세요."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	CPenSizeDlg* pdlgPen = new CPenSizeDlg;
	if (pdlgPen->DoModal() == IDOK) m_nPenSize = pdlgPen->m_nPenSize;
}

void CMy2018111384_Final1View::OnEraserSize() //지우개 사이즈 조절
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 지우개의 크기 -"));
	explain.Append(_T("\r\n지우개의 크기를 조절해보세요."));
	explain.Append(_T("\r\n지우개의 크기를 조절한 후, 지우개을 선택해서 그림을 지워보세요."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	CEraserSizeDlg* pdlgEraser = new CEraserSizeDlg;
	if (pdlgEraser->DoModal() == IDOK) m_nEraserSize = pdlgEraser->m_nEraserSize;
}

void CMy2018111384_Final1View::OnPenColor() //펜 색 정하기
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 펜의 색상 -"));
	explain.Append(_T("\r\n펜의 색을 원하는 색상으로 바꿔보세요."));
	explain.Append(_T("\r\n원하는 색상을 고른 후, 펜을 선택해서 그림을 그려보세요."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	CColorDialog colorDlg;
	if (colorDlg.DoModal() == IDOK) m_colorPen = colorDlg.GetColor();
}

void CMy2018111384_Final1View::OnSelchangeComboGame() //게임을 바꿀 때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nGame = m_cbGame.GetCurSel();
	CString explain;
	if (m_nGame == 0) { //틀린그림찾기 선택
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
		explain.Format(_T("<틀린그림찾기 설명서>"));
		explain.Append(_T("\r\n1. LEVEL을 선택해주세요."));
		explain.Append(_T("\r\n2. 왼쪽 그림과 비교해 오른쪽 그림에서 다른 것을 마우스 왼쪽 버튼으로 클릭해주세요."));
		explain.Append(_T("\r\n3. 클릭한 답이 맞으면 빨간 동그라미가, 틀리면 기회가 1 줄어듭니다."));
		explain.Append(_T("\r\n4. 기회가 0이 되면 게임을 실패로 끝납니다. 그 후 다시 처음으로 리셋됩니다."));
		explain.Append(_T("\r\n5. 답을 모르겠으면 기회 1개를 사용하고 힌트를 받아보세요.(힌트는 문제당 총 3개)"));
		explain.Append(_T("\r\n   힌트를 누르고 기회 1개를 사용 안 한다고 하면 이전에 얻은 힌트만 볼 수 있습니다."));
		AfxMessageBox(explain, MB_ICONINFORMATION);
	}else if (m_nGame == 1) { //미니 그림판 선택
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
		explain.Format(_T("<미니 그림판 설명서>"));
		explain.Append(_T("\r\n미니 그림판은 위의 메뉴를 주로 사용합니다."));
		explain.Append(_T("\r\n* 왼쪽 박스에 해당 메뉴에 대한 설명이 나오니 참고해주세요."));
		AfxMessageBox(explain, MB_ICONINFORMATION);

		explain.Format(_T("<미니 그림판 설명서>"));
		explain.Append(_T("\r\n- 이미지 편집- "));
		explain.Append(_T("\r\n이미지를 편집하고 싶으면 메뉴의 '이미지(사진) 도구'를 이용하세요"));
		explain.Append(_T("\r\n'사진 불러오기': 원하는 사진을 선택하여 오른쪽 그림판에 불러오기"));
		explain.Append(_T("\r\n'이미지 크기 조절': 이미지의 크기를 오른쪽 그림판 크기 기준으로 1~100% 사이로 바꾸기"));
		explain.Append(_T("\r\n'이미지 위치 조절': 이미지의 위치를 오른쪽 그림판 안에서 조절하기"));
		explain.Append(_T("\r\n'이미지 투명도 조절': 이미지의 투명도를 1~100%로 바꾸기"));
		explain.Append(_T("\r\n'이미지 자르기': 이미지를 원하는 부분만 사각형 형태로 자르기"));
		explain.Append(_T("\r\n'새로 만들기': 오른쪽 그림판을 다 지우기"));
		explain.Append(_T("\r\n* '자르기'를 하면 다른 편집을 할 때, 자르기 이전 상태로 돌아갑니다."));
		explain.Append(_T("\r\n\r\n- 그림 그리기 -"));
		explain.Append(_T("\r\n그림을 그리고 싶다면 메뉴의 '그리기 도구'를 이용하세요"));
		explain.Append(_T("\r\n'펜 선택': 펜으로 그림을 그리기"));
		explain.Append(_T("\r\n'지우개 선택': 지우개로 그림이나 사진을 지우기"));
		explain.Append(_T("\r\n'펜 크기': 펜 크기를 조절하기"));
		explain.Append(_T("\r\n'펜 색상': 원하는 색상으로 펜의 색을 바꾸기"));
		explain.Append(_T("\r\n'지우개 크기': 지우개 크기를 조절하기"));
		GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	}
	Invalidate();
}

void CMy2018111384_Final1View::OnRadioLevel1()//틀린그림찾기 Level1
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

void CMy2018111384_Final1View::OnRadioLevel2()//틀린그림찾기 Level2
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

void CMy2018111384_Final1View::OnRadioLevel3()//틀린그림찾기 Level3
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

void CMy2018111384_Final1View::OnPen()//펜 선택
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawObject = 1;
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 펜 선택 -"));
	explain.Append(_T("\r\n오른쪽 그림판에 안에서 마우스의 왼쪽을 누르고 그림을 그려보세요."));
	explain.Append(_T("\r\n펜의 색이나 크기를 바꾸고 싶으면 메뉴에서 바꾸세요."));
	explain.Append(_T("\r\n* 오른쪽 그림판을 벗어나면 그릴 수 없습니다!"));
	explain.Append(_T("\r\n* 오른쪽 그림판에서 마우스를 누르면 범위가 오른쪽 그림판으로 한정되어"));
	explain.Append(_T("\r\n  오른쪽 그림판에서만 그릴 수 있도록 되어 있습니다."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}

void CMy2018111384_Final1View::OnEraser()//지우개 선택
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawObject = 2;
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 지우개 선택 -"));
	explain.Append(_T("\r\n오른쪽 그림판에 안에서 마우스의 왼쪽을 누르고 그림(사진)을 지워보세요."));
	explain.Append(_T("\r\n지우개의 크기를 바꾸고 싶으면 메뉴에서 바꾸세요."));
	explain.Append(_T("\r\n* 오른쪽 그림판을 벗어나면 지울 수 없습니다!"));
	explain.Append(_T("\r\n* 오른쪽 그림판에서 마우스를 누르면 범위가 오른쪽 그림판으로 한정되어"));
	explain.Append(_T("\r\n  오른쪽 그림판에서만 지울 수 있도록 되어 있습니다."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}

void CMy2018111384_Final1View::OnClickedButtonHint()//틀린그림찾기에서 힌트보여주기
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//1일 때 사용못하게 하기
	int YN = AfxMessageBox(_T("힌트를 사용하면 기회가 1개 줄어듭니다."), MB_YESNO);
	CString level[3];
	if (m_ncurLevel == 1) {//level1
		level[0] = _T("정답은 5개입니다."); level[1] = _T("\n틀린 공간이 클 경우 가운데를 선택하세요.");level[2] = _T("\n새들을 자세히 보세요.");
	}
	else if (m_ncurLevel == 2) {//level2
		level[0] = _T("정답은 5개입니다."); level[1] = _T("\n물고기를 자세히 보세요.");level[2] = _T("\n오른쪽 위에 답이 2개있습니다.");
	}
	else if (m_ncurLevel == 3) {//level3
		level[0] = _T("정답은 7개입니다."); level[1] = _T("\n하늘을 자세히 보세요.");level[2] = _T("\n무늬같은 선들을 자세히 보세요.");
	}
	CString temp;
	temp.Format(_T("<현재 가지고 있는 힌트입니다>\n"));
	if (YN == IDYES) {//사용한다고 했다면
		if (m_nhint == 3) {//힌트 다 사용하면 기회 깍지 않고 이전 힌트 보여주기
			temp.Append(_T("!힌트를 다 사용했습니다!\n"));
			for (int i = 0;i < m_nhint;i++) {
				temp.Append(level[i]);
			}
			AfxMessageBox(temp, MB_ICONINFORMATION);
			return;
		}
		else {//기회 1감소하고 새로운 힌트 보여주기
			if (m_nheart == 1) {
				AfxMessageBox(_T("기회가 1개 남아서 힌트를 사용하지 못합니다."), MB_ICONINFORMATION);
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
	else {//힌트를 사용하지 않는다 하면, 이전에 얻는 힌트만 다시 보여주기
		for (int i = 0;i < m_nhint;i++) {
			temp.Append(level[i]);
		}
		AfxMessageBox(temp, MB_ICONINFORMATION);
	}
}

void CMy2018111384_Final1View::OnImageLoad() //새로운 이미지 로드
{
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 사진 불러오기 -"));
	explain.Append(_T("\r\n원하는 비트맵(.bmp)사진을 파일로 불러올 수 있습니다."));
	explain.Append(_T("\r\n이미지 파일을 선택해주세요!"));
	explain.Append(_T("\r\n이미지 파일은 오른쪽 그림판에 그려집니다."));
	explain.Append(_T("\r\n이미지를 편집하고 싶으면 메뉴의 '이미지(사진) 도구'를 이용하세요"));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
											 // _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
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

void CMy2018111384_Final1View::OnImageSize() //이미지 크기 조절
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageSizeDlg* pdlgImageSize = new CImageSizeDlg;
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 이미지 크기 조절 -"));
	explain.Append(_T("\r\n현재 로드된 이미지의 크기를 조절할 수 있습니다."));
	explain.Append(_T("\r\n* 오른쪽 그림판을 기준으로 1~100%까지 조절 할 수 있습니다."));
	explain.Append(_T("\r\n  100%이면 오른쪽 그림판에서 최대로 크게한 크기 입니다."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	if (pdlgImageSize->DoModal() == IDOK) {
		m_nDrawObject = 3;
		m_nImageSize = pdlgImageSize->m_nImageSize;
		Invalidate();
	}
}

void CMy2018111384_Final1View::OnImageBlended() //이미지 투명 조절
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageBlendedDlg* pdlgImageBlended = new CImageBlendedDlg;
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 이미지 투명도 조절 -"));
	explain.Append(_T("\r\n현재 로드된 이미지의 투명도를 조절할 수 있습니다."));
	explain.Append(_T("\r\n* 오른쪽 그림판을 기준으로 1~100%까지 조절 할 수 있습니다."));
	explain.Append(_T("\r\n  100%가 불투명입니다."));
	explain.Append(_T("\r\n  50~100%는 차이가 별로 없을 수 있습니다."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	if (pdlgImageBlended->DoModal() == IDOK) {
		m_nImageBlended = pdlgImageBlended->m_nBlended;
		m_nDrawObject = 5;
		Invalidate();
	}
}

void CMy2018111384_Final1View::OnImageCut() //이미지 자르기
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawObject = 6;
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 이미지 자르기 -"));
	explain.Append(_T("\r\n현재 로드된 이미지를 원하는 사각형 모양으로 자를 수 있습니다."));
	explain.Append(_T("\r\n* 원하는 부분의 왼쪽 상단을 왼쪽 마우스로 클릭하고 원하는 사각형이 나올 수 있도록 마우스를 움직여 주세요. 원하는 사각형이 나오면 왼쪽 마우스를 때주세요."));
	explain.Append(_T("\r\n* 자르기를 한 후 다른 이미지 조절을 하면 자르기 전으로 이미지가 복구됩니다."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}

void CMy2018111384_Final1View::OnImagePosition() //이미지 위치
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawObject = 7;
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 이미지 위치 조절 -"));
	explain.Append(_T("\r\n현재 로드된 이미지를 오른쪽 그림판 내에서 위치 조정을 할 수 있습니다."));
	explain.Append(_T("\r\n* '이미지 위치 조절'을 누른 후"));
	explain.Append(_T("\r\n오른쪽 그림판 안에서 원하는 위치에서 마우스 왼쪽을 누르면"));
	explain.Append(_T("\r\n그 지점을 중심으로 그림의 위치가 바뀝니다."));
	explain.Append(_T("\r\n* 그림판 밖을 클릭하면 아무일도 일어나지 않습니다."));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
}


void CMy2018111384_Final1View::OnNew()// 새로 만들기
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CString explain;
	explain.Format(_T("<미니 그림판 설명서>"));
	explain.Append(_T("\r\n- 새로 만들기 -"));
	explain.Append(_T("\r\n현재 오른쪽 그림판을 다 지워줍니다.(초기화시켜줍니다.)"));
	GetDlgItem(IDC_EDIT_EXPLAIN)->SetWindowText(explain);
	Game2Reset();
	Invalidate();
}


void CMy2018111384_Final1View::OnTimer(UINT_PTR nIDEvent) //틀린그림찾기에서 타이머
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString text1,text2;
	if (nIDEvent == 1) {
		if (m_ntime2 == 0) {
			m_ntime2 = 59;
			if (m_ntime1 != 0) {
				m_ntime1--;
			}
			else {
				KillTimer(1);
				AfxMessageBox(_T("시간 초과로 실패했습니다. 다시 도전해보세요!"), MB_ICONINFORMATION);
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


void CMy2018111384_Final1View::Game1Reset()//틀린그림찾기 초기화
{
	m_nheart = 5;
	m_nhint = 0;
	m_ntime1 = 3;
	m_ntime2 = 0;
	for (int i = 0;i < 7;i++) m_bCorrect[i] = false;
}


void CMy2018111384_Final1View::Game2Reset()//미니 그림판 초기화
{
	m_strPreFilePath = "";
	m_ptCutPre.x = 0;m_ptCutPre.y = 0;
	m_nImageBlended = 100;
	m_nImageSize = 100;
	m_nPenSize = 2;
	m_nEraserSize = 4;
	m_colorPen = RGB(0, 0, 0);
}
