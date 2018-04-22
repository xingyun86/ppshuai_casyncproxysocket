// CAsyncProxyDemo.h : Haupt-Header-Datei für die Anwendung CASYNCPROXYDEMO
//

#if !defined(AFX_CASYNCPROXYDEMO_H__A4D74D47_0260_4732_B233_4D8266BE96B8__INCLUDED_)
#define AFX_CASYNCPROXYDEMO_H__A4D74D47_0260_4732_B233_4D8266BE96B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CCAsyncProxyDemoApp:
// Siehe CAsyncProxyDemo.cpp für die Implementierung dieser Klasse
//

class CCAsyncProxyDemoApp : public CWinApp
{
public:
	CCAsyncProxyDemoApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CCAsyncProxyDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CCAsyncProxyDemoApp)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_CASYNCPROXYDEMO_H__A4D74D47_0260_4732_B233_4D8266BE96B8__INCLUDED_)
