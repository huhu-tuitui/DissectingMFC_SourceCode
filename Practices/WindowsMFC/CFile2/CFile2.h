// CFile2.h : main header file for the CFILE2 application
//

#if !defined(AFX_CFILE2_H__29A38BF8_103A_4775_829D_9DE04E19C329__INCLUDED_)
#define AFX_CFILE2_H__29A38BF8_103A_4775_829D_9DE04E19C329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCFile2App:
// See CFile2.cpp for the implementation of this class
//

class CCFile2App : public CWinApp
{
public:
	CCFile2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCFile2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCFile2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFILE2_H__29A38BF8_103A_4775_829D_9DE04E19C329__INCLUDED_)
