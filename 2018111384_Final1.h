
// 2018111384_Final1.h : 2018111384_Final1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMy2018111384_Final1App:
// �� Ŭ������ ������ ���ؼ��� 2018111384_Final1.cpp�� �����Ͻʽÿ�.
//

class CMy2018111384_Final1App : public CWinApp
{
public:
	CMy2018111384_Final1App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2018111384_Final1App theApp;
