// KugouUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CKugouUIApp:
// �йش����ʵ�֣������ KugouUI.cpp
//

class CKugouUIApp : public CWinApp
{
public:
	CKugouUIApp();

// ��д
	public:
	virtual BOOL InitInstance();

public:
	ULONG_PTR m_gdiplusToken;  
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CKugouUIApp theApp;