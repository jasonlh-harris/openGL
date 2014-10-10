// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__50C8628F_112A_40D0_9AB2_53368988C69B__INCLUDED_)
#define AFX_CHILDVIEW_H__50C8628F_112A_40D0_9AB2_53368988C69B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"	// Added by ClassView
#include "graphics/GrCamera.h"
#include "AnimationTime.h"
#include "SgPolygon.h"
#include "SgMesh.h"
#include "SgMasterFactory.h"
#include "AnimationTime.h"
#include "SgComposite.h"


#include "SgClosetFactory.h"
#include "SgGramaphoneFactory.h"

#include "SGDresserFactory.h"
#include "SgCanFactory.h"

/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnGLDraw(CDC *pDC);
	virtual ~CChildView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnFileSavebmpfile();
	afx_msg void OnStepSpin();
	afx_msg void OnUpdateStepSpin(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStepBox();
	afx_msg void OnUpdateStepBox(CCmdUI* pCmdUI);
	afx_msg void OnStepSphere();
	afx_msg void OnUpdateStepSphere(CCmdUI* pCmdUI);
	afx_msg void OnStepTorus();
	afx_msg void OnUpdateStepTorus(CCmdUI* pCmdUI);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnStepMesh();
    afx_msg void OnUpdateStepMesh(CCmdUI *pCmdUI);
    afx_msg void OnViewWireframe();
    afx_msg void OnUpdateViewWireframe(CCmdUI *pCmdUI);
    afx_msg void OnStepTorus2();
    afx_msg void OnUpdateStepTorus2(CCmdUI *pCmdUI);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    //}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
    bool m_wireframe;
	bool m_project1;

	UINT m_spintimer;
	double m_spinangle;

    CGrCamera       m_camera;


	//Peng's Dorm
	//CPengFactory *peng_dorm;
	//CSgComposite *m_dorm;

	//Jason's Closet & Gramaphone
	//CSgClosetFactory* m_ClosetFactory;
	//CSgGramaphoneFactory* m_GramaphoneFactory;

	//Ben's dresser
	//CSGDresserFactory* m_DresserFactory;

	//CWindowFactory *m_windowFactory;

	//Yue's Dorm
	//CYueFactory *yue_dorm;

	CSgPtr<CSgComposite> m_dorm;
	CSgMasterFactory *m_factory;

	CAnimationTime m_time;
	

public:
	afx_msg void OnUpdateStepProject1(CCmdUI *pCmdUI);
	afx_msg void OnStepProject1();

	afx_msg void OnAnimationRun();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__50C8628F_112A_40D0_9AB2_53368988C69B__INCLUDED_)
