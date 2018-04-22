// MySocket.cpp: Implementierung der Klasse CMySocket.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "MySocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CMySocket::CMySocket()
{

}

CMySocket::~CMySocket()
{

}

void CMySocket::OnReceive(int nErrorCode)
{
	CAsyncProxySocket::OnReceive(nErrorCode);
	if (nErrorCode)
	{
		AfxMessageBox("Fatal error! Network subsystem failed!",MB_ICONSTOP);
		Close();
		return;
	}
	for(;;)
	{
		char buffer;
		int res=Receive(&buffer,1);
		if (res==SOCKET_ERROR || !res)
		{
			if (GetLastError()!=WSAEWOULDBLOCK || !res)
			{
				AfxMessageBox("Error! Connection has been closed!",MB_ICONEXCLAMATION);
				return;
			}
			break;
		}
		CString str;
		m_pResponse->GetWindowText(str);
		str+=buffer;	
		m_pResponse->SetWindowText(str);
	}
}


void CMySocket::OnProxyOperationFailed(int nOpID)
{
	AfxMessageBox("Error! Could not connect through proxy!",MB_ICONEXCLAMATION);
}

void CMySocket::OnListenFinished(unsigned long &retProxyIp,int &retProxyPort)
{
}
	
void CMySocket::OnConnect(int nErrorCode)
{
	CAsyncProxySocket::OnConnect(nErrorCode);
	if (nErrorCode)
	{
		if (GetProxyType())
			AfxMessageBox("Error! Could not connect to proxy server!",MB_ICONEXCLAMATION);
		else
			AfxMessageBox("Error! Could not connect to server!",MB_ICONEXCLAMATION);
		Close();
	}
}
