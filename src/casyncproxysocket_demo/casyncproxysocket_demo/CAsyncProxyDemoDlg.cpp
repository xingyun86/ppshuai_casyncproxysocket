// CAsyncProxyDemoDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CAsyncProxyDemo.h"
#include "CAsyncProxyDemoDlg.h"

#include "MySocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAsyncProxyDemoDlg Dialogfeld

CCAsyncProxyDemoDlg::CCAsyncProxyDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCAsyncProxyDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCAsyncProxyDemoDlg)
	m_Host = _T("");
	m_nPort = 0;
	m_ProxyPass = _T("");
	m_ProxyHost = _T("");
	m_ProxyUser = _T("");
	m_bUseAuth = FALSE;
	m_nProxyType = -1;
	m_nProxyPort = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCAsyncProxyDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCAsyncProxyDemoDlg)
	DDX_Control(pDX, IDC_RESPONSE, m_cResponse);
	DDX_Text(pDX, IDC_HOST, m_Host);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDV_MinMaxInt(pDX, m_nPort, 1, 65535);
	DDX_Text(pDX, IDC_PPASS, m_ProxyPass);
	DDV_MaxChars(pDX, m_ProxyPass, 255);
	DDX_Text(pDX, IDC_PHOST, m_ProxyHost);
	DDX_Text(pDX, IDC_PUSER, m_ProxyUser);
	DDV_MaxChars(pDX, m_ProxyUser, 255);
	DDX_Check(pDX, IDC_USEAUTH, m_bUseAuth);
	DDX_Radio(pDX, IDC_RADIO1, m_nProxyType);
	DDX_Text(pDX, IDC_PPORT, m_nProxyPort);
	DDV_MinMaxInt(pDX, m_nProxyPort, 1, 65535);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCAsyncProxyDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCAsyncProxyDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAsyncProxyDemoDlg Nachrichten-Handler

BOOL CCAsyncProxyDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Hinzufügen des Menübefehls "Info..." zum Systemmen?

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	m_pMySocket=0;
	m_nProxyType=0;
	UpdateData(FALSE);
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

void CCAsyncProxyDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CCAsyncProxyDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CCAsyncProxyDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCAsyncProxyDemoDlg::OnConnect() 
{
	//Validate all input fields
	if (!UpdateData(TRUE))
		return;
	if (m_nProxyType!=0)
	{
		if (m_ProxyHost=="")
		{
			AfxMessageBox("Please enter the proxy host!");
			return;
		}
		if (m_nProxyPort<1 || m_nProxyPort>65535)
		{
			AfxMessageBox("Please enter a valid port for the proxy!");
			return;
		}
	}
	if (((m_nProxyType==3) || (m_nProxyType==4)) && m_bUseAuth)
	{
		if (m_ProxyUser=="")
		{
			AfxMessageBox("Please enter the username for the proxy server!");
			return;
		}
		if (m_ProxyPass=="")
		{
			AfxMessageBox("Please enter the password for the proxy server!");
			return;
		}
	}
	if (m_Host=="")
	{
		AfxMessageBox("Please enter a server!");
		return;
	}
	if (m_nPort<1 || m_nPort>65535)
	{
		AfxMessageBox("Please enter a valid port for the server!");
		return;
	}

	//If connected, close old connection
	if (m_pMySocket)
		delete m_pMySocket;
	m_cResponse.SetWindowText("");
	m_pMySocket=new CMySocket;

	//Set the type of the proxy
	if (!m_nProxyType)
		m_pMySocket->SetProxy(PROXYTYPE_NOPROXY);
	else if (m_nProxyType==1)
		m_pMySocket->SetProxy(PROXYTYPE_SOCKS4,m_ProxyHost,m_nProxyPort);
	else if (m_nProxyType==2)
		m_pMySocket->SetProxy(PROXYTYPE_SOCKS4A,m_ProxyHost,m_nProxyPort);
	else if (m_nProxyType==3 && !m_bUseAuth)
		m_pMySocket->SetProxy(PROXYTYPE_SOCKS5,m_ProxyHost,m_nProxyPort);
	else if (m_nProxyType==3 && m_bUseAuth)
		m_pMySocket->SetProxy(PROXYTYPE_SOCKS5,m_ProxyHost,m_nProxyPort,m_ProxyUser,m_ProxyPass);
	else if (m_nProxyType==4 && !m_bUseAuth)
		m_pMySocket->SetProxy(PROXYTYPE_HTTP11,m_ProxyHost,m_nProxyPort);
	else if (m_nProxyType==4 && m_bUseAuth)
		m_pMySocket->SetProxy(PROXYTYPE_HTTP11,m_ProxyHost,m_nProxyPort,m_ProxyUser,m_ProxyPass);

	m_pMySocket->m_pResponse=&m_cResponse;
	m_pMySocket->Create();

	//Connect
	BOOL res=m_pMySocket->Connect(m_Host,m_nPort);
	if (!res)
		if (GetLastError()!=WSAEWOULDBLOCK)
			if (m_nProxyType)
				AfxMessageBox("Error! Can't connect to proxy server!",MB_ICONEXCLAMATION);
			else
				AfxMessageBox("Error! Can't connect to server!",MB_ICONEXCLAMATION);
}

void CCAsyncProxyDemoDlg::OnClose() 
{
	if (m_pMySocket)
		delete m_pMySocket;
	m_pMySocket=0;
	CDialog::OnClose();
}
