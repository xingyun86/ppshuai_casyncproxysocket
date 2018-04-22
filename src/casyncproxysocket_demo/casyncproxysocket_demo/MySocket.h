// MySocket.h: Schnittstelle für die Klasse CMySocket.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSOCKET_H__D972BDE0_B82B_4AAD_8232_2A5BAF040129__INCLUDED_)
#define AFX_MYSOCKET_H__D972BDE0_B82B_4AAD_8232_2A5BAF040129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AsyncProxySocket.h"

class CMySocket : public CAsyncProxySocket  
{
public:
	CStatic *m_pResponse;
	virtual void OnConnect(int nErrorCode);
	virtual void OnProxyOperationFailed(int nOpID);
	virtual void OnListenFinished(unsigned long &retProxyIp,int &retProxyPort);
	virtual void OnReceive(int nErrorCode);
	
	CMySocket();
	virtual ~CMySocket();

};

#endif // !defined(AFX_MYSOCKET_H__D972BDE0_B82B_4AAD_8232_2A5BAF040129__INCLUDED_)
