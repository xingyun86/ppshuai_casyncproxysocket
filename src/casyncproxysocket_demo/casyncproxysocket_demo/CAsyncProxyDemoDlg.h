// CAsyncProxyDemoDlg.h : Header-Datei
//

#if !defined(AFX_CASYNCPROXYDEMODLG_H__CA73F5B6_5A33_457D_8BFB_9BE92E4B4BBE__INCLUDED_)
#define AFX_CASYNCPROXYDEMODLG_H__CA73F5B6_5A33_457D_8BFB_9BE92E4B4BBE__INCLUDED_

#include "MySocket.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCAsyncProxyDemoDlg Dialogfeld
class CMySocket;

class CCAsyncProxyDemoDlg : public CDialog
{
// Konstruktion
public:
	CMySocket *m_pMySocket;
	CCAsyncProxyDemoDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CCAsyncProxyDemoDlg)
	enum { IDD = IDD_CASYNCPROXYDEMO_DIALOG };
	CStatic	m_cResponse;
	CString	m_Host;
	int		m_nPort;
	CString	m_ProxyPass;
	CString	m_ProxyHost;
	CString	m_ProxyUser;
	BOOL	m_bUseAuth;
	int		m_nProxyType;
	int		m_nProxyPort;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCAsyncProxyDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CCAsyncProxyDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CASYNCPROXYDEMODLG_H__CA73F5B6_5A33_457D_8BFB_9BE92E4B4BBE__INCLUDED_)
