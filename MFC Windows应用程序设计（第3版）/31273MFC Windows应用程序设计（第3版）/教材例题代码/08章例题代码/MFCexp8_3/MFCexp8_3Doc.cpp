// MFCexp8_3Doc.cpp : implementation of the CMFCexp8_3Doc class
//

#include "stdafx.h"
#include "MFCexp8_3.h"

#include "MFCexp8_3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCexp8_3Doc

IMPLEMENT_DYNCREATE(CMFCexp8_3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCexp8_3Doc, CDocument)
	//{{AFX_MSG_MAP(CMFCexp8_3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCexp8_3Doc construction/destruction

CMFCexp8_3Doc::CMFCexp8_3Doc()
{
	// TODO: add one-time construction code here

}

CMFCexp8_3Doc::~CMFCexp8_3Doc()
{
}

BOOL CMFCexp8_3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMFCexp8_3Doc serialization

void CMFCexp8_3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMFCexp8_3Doc diagnostics

#ifdef _DEBUG
void CMFCexp8_3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCexp8_3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCexp8_3Doc commands
