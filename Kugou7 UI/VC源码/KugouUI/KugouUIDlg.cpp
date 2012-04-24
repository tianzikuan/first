// KugouUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KugouUI.h"
#include "KugouUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKugouUIDlg �Ի���




CKugouUIDlg::CKugouUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKugouUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bTracking=m_Play=false;
}

void CKugouUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKugouUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
END_MESSAGE_MAP()


// CKugouUIDlg ��Ϣ�������

BOOL CKugouUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetWindowText(_T("Kugou7 UI"));
	InitUI();
	DrawUI();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKugouUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CKugouUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKugouUIDlg::InitUI(void)
{
	//����UI������Ŀ������
m_KugouUI.width = 204;
m_KugouUI.height = 209;
m_KugouUI.main = MakeUiItem (48, 48, 106, 106, 0, 0,true);
m_KugouUI.left = MakeUiItem (0, 54, 98, 100, 110, 0);
m_KugouUI.top = MakeUiItem (53, 0, 98, 100, 110, 0);
m_KugouUI.right = MakeUiItem (106, 54, 98, 100, 110, 0);
m_KugouUI.bottom = MakeUiItem (53, 109, 98, 100, 110, 0);
m_KugouUI.Item [0] = MakeUiItem (30, 90, 24, 24, 113, 179);
m_KugouUI.Item [1] = MakeUiItem (91, 24, 24, 24, 113, 154);
m_KugouUI.Item [2] = MakeUiItem (158, 90, 24, 24, 138, 179);
m_KugouUI.Item [3] = MakeUiItem (91, 157, 24, 24, 138, 154);
	//--------------------------
	LoadResImage(IDR_PNG1,m_pSrcImage);//������Դ�е�Ƥ��PNGͼƬ
	ModifyStyleEx(0,WS_EX_LAYERED);
}

void CKugouUIDlg::DrawUI(void)
{
	HDC hDC=::GetDC(m_hWnd);
	HDC hMemDC=::CreateCompatibleDC(hDC);
	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = m_KugouUI.height;
	bitmapinfo.bmiHeader.biWidth = m_KugouUI.width;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression=BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter=0;
	bitmapinfo.bmiHeader.biYPelsPerMeter=0;
	bitmapinfo.bmiHeader.biClrUsed=0;
	bitmapinfo.bmiHeader.biClrImportant=0;
	bitmapinfo.bmiHeader.biSizeImage = bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight * bitmapinfo.bmiHeader.biBitCount / 8;
	HBITMAP hBitmap=::CreateDIBSection (hMemDC,&bitmapinfo, 0,NULL, 0, 0);
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hMemDC,hBitmap);
	Graphics g(hMemDC);
	//������������Ԫ��----------------------
	DrawItem(&g,m_KugouUI.left);
	DrawItem(&g,m_KugouUI.top);
	DrawItem(&g,m_KugouUI.right);
	DrawItem(&g,m_KugouUI.bottom);
	DrawItem(&g,m_KugouUI.main);
	for(int i=0;i<4;i++)
		DrawItem(&g,m_KugouUI.Item[i]);	
	//����͸������-------------------------------------------------
	CPoint DestPt(0,0);
	CSize psize(m_KugouUI.width,m_KugouUI.height);
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;
	::UpdateLayeredWindow(m_hWnd,hDC,NULL,&psize,hMemDC,&DestPt,0,&blendFunc32bpp,ULW_ALPHA);
	//�ͷ���Դ-------------------------------------------------
	::SelectObject (hMemDC,hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::ReleaseDC(m_hWnd,hDC);
}
void CKugouUIDlg::DrawItem(Graphics *g,UIITEM item)
{
	if(!item.Show)return;
	g->DrawImage(m_pSrcImage,RectF(item.x,item.y,item.width,item.height),item.SrcX,item.SrcY,item.width,item.height,UnitPixel,NULL,NULL,NULL);
}
void CKugouUIDlg::PlayMouseOver()
{
	m_Play=true;
	//--------------------------
	m_KugouUI.main.SrcY=110;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.top.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.right.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.bottom.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.left.Show=true;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	ShowItem(true);
	m_Play=false;
}
void CKugouUIDlg::PlayMouseOut()
{
	m_Play=false;
	ShowItem(false);
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.left.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.bottom.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.right.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.top.Show=false;
	DrawUI();
	doEvents();
	Sleep(PLAYTIME);
	//--------------------------
	m_KugouUI.main.SrcY=0;
	DrawUI();
	doEvents();
	//--------------------------	
	m_Play=false;
}
void CKugouUIDlg::ShowItem(bool bShow)
{
	for(int i=0;i<4;i++)
		m_KugouUI.Item[i].Show=bShow;	
	DrawUI();
}
UIITEM CKugouUIDlg::MakeUiItem(int x,int y,int width,int height,int SrcX,int SrcY,bool Show)
{
	UIITEM item;
item.x = x;
item.y = y;
item.width = width;
item.height = height;
item.SrcX = SrcX;
item.SrcY = SrcY;
item.Show = Show;
return item;
}
void CKugouUIDlg::doEvents()
{
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	} 
}
void CKugouUIDlg::LoadResImage(int nResID,Image * &lpImage)
{
	HINSTANCE hIns=AfxGetInstanceHandle();
	HRSRC hRsrc = ::FindResource (hIns,MAKEINTRESOURCE(nResID),_T("PNG")); // type 
	if (!hRsrc) 
		return; 
	// load resource into memory 
	DWORD len = SizeofResource(hIns, hRsrc); 
	BYTE* lpRsrc = (BYTE*)LoadResource(hIns, hRsrc); 
	if (!lpRsrc) 
		return; 
	// Allocate global memory on which to create stream 
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, len); 
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem); 
	memcpy(pmem,lpRsrc,len); 
	IStream* pstm; 
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm); 
	// load from stream 
	lpImage=Gdiplus::Image::FromStream(pstm); 
	// free/release stuff 
	GlobalUnlock(m_hMem); 
	pstm->Release(); 
	FreeResource(lpRsrc);
}
void CKugouUIDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CDialog::OnMouseMove(nFlags, point);
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 50;
		m_bTracking = (bool)_TrackMouseEvent(&tme);
	}
}
LRESULT CKugouUIDlg::OnMouseHover(WPARAM   wParam,   LPARAM   lParam)
{
	if(!m_Play)PlayMouseOver();
	return 0;
}
LRESULT CKugouUIDlg::OnMouseLeave(WPARAM   wParam,   LPARAM   lParam)
{
	m_bTracking=false;
	if(!m_Play)PlayMouseOut();
	return 0;
}
void CKugouUIDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonDown(nFlags, point);
	ReleaseCapture ();
	SendMessage (WM_NCLBUTTONDOWN, HTCAPTION, 0);
}
