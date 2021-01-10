
// 2018111384_Final1.h : 2018111384_Final1 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.


// CMy2018111384_Final1App:
// 이 클래스의 구현에 대해서는 2018111384_Final1.cpp을 참조하십시오.
//

class CMy2018111384_Final1App : public CWinApp
{
public:
	CMy2018111384_Final1App();


// 재정의입니다.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy2018111384_Final1App theApp;
