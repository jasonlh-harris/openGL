// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "lab.h"
#include "ChildView.h"
#include "SceneFactory.h"
#include "SgTranslate.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
	//15, 10, 30
    m_camera.Set(20, 15, 60, 20, 0, 0, 0, 1, 0);
	m_camera.SetZNearRange(0.01);
	m_camera.SetZFarRange(20);
    m_spinangle = 0.;
    m_spintimer = 0;
    m_wireframe = false;

    SetDoubleBuffer(true);

	m_dorm = new CSgComposite();
	m_factory = new CSgMasterFactory;
	m_factory->SetTime(&m_time);
	m_factory->Create(m_dorm);
	//m_GramaphoneFactory->Create(m_dorm);


}

CChildView::~CChildView()
{
	//delete m_dorm;
	delete m_factory;

}


BEGIN_MESSAGE_MAP(CChildView,COpenGLWnd )
    //{{AFX_MSG_MAP(CChildView)
    ON_COMMAND(ID_FILE_SAVEBMPFILE, OnFileSavebmpfile)
    ON_COMMAND(ID_STEP_SPIN, OnStepSpin)
    ON_UPDATE_COMMAND_UI(ID_STEP_SPIN, OnUpdateStepSpin)
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_VIEW_WIREFRAME, &CChildView::OnViewWireframe)
    ON_UPDATE_COMMAND_UI(ID_VIEW_WIREFRAME, &CChildView::OnUpdateViewWireframe)
    ON_WM_RBUTTONDOWN()
    ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ANIMATION_RUN, &CChildView::OnAnimationRun)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
    if (!COpenGLWnd::PreCreateWindow(cs))
        return FALSE;

    cs.dwExStyle |= WS_EX_CLIENTEDGE;
    cs.style &= ~WS_BORDER;
    cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
        ::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

    return TRUE;
}




void CChildView::OnGLDraw(CDC *pDC)
{
    GLfloat gray = 0.3f;
    glClearColor(gray, gray, gray, 0.0f) ;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    // Set up the camera
    //

    int wid, hit;
    GetSize(wid, hit);
    m_camera.Apply(wid, hit);

    //
    // Some standard parameters
    //

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Cull backfacing polygons
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Enable or disable the wireframe mode
    glPolygonMode(GL_FRONT, m_wireframe ? GL_LINE : GL_FILL);

    //
    // Enable and configure lighting
    //

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);

    GLfloat light[] = {0.8f, 0.8f, 0.8f, 1.0f};


    GLfloat lightpos[] = {4., 8., 4, 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light);

    GLfloat lightpos1[] = {12.5, 8., 4, 1.};
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light);

	GLfloat lightpos2[] = {21., 8., 4, 1.};
    glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light);

	GLfloat lightpos3[] = {29.5, 8., 4, 1.};
    glLightfv(GL_LIGHT3, GL_POSITION, lightpos3);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light);

	GLfloat lightpos4[] = {42.5, 8., 4, 1.};
    glLightfv(GL_LIGHT4, GL_POSITION, lightpos4);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, light);
    glPushMatrix();

    // Note that I'm texture mapping most of the following
    // objects.  So, I'm setting the color to white.  The
    // actual color will be the object color multiplied 
    // by the texture color.  If I set a color it, it will
    // tint the texture.  Maybe that's what you'll want 
    // sometimes?

    //GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    //GLfloat shininess[] = {100};
    //glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

    //
    // Switch for the three lab examples
    //

	//Units in meters
	m_dorm -> Render();
	//CSgPtr<CSgTranslate> l_closetTrans = new CSgTranslate(1,2,-10);
	//l_closetTrans->AddChild(m_closet);
	//m_closet -> Render();
	//m_dresser->Render();


    glPopMatrix();

    glFlush();
}

double Normal3dv(double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void CChildView::OnFileSavebmpfile() 
{
    OnSaveImage();	
}


void CChildView::OnStepSpin() 
{
    //if(m_spintimer)
    //{
    //    KillTimer(m_spintimer);
    //    m_spintimer = 0;
    //}
    //else
    //{
    //    m_spintimer = SetTimer(1, 30, NULL);
    //}
}

void CChildView::OnUpdateStepSpin(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_spintimer != 0);	
}

void CChildView::OnTimer(UINT nIDEvent) 
{
    //m_spinangle += 10;
	m_time.Update();
    Invalidate();

    COpenGLWnd ::OnTimer(nIDEvent);
}

void CChildView::OnViewWireframe()
{
    m_wireframe = !m_wireframe;
    Invalidate();
}

void CChildView::OnUpdateViewWireframe(CCmdUI *pCmdUI)
{
    pCmdUI->SetCheck(m_wireframe);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y);

    COpenGLWnd ::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if(m_camera.MouseMove(point.x, point.y, nFlags))
        Invalidate();

    COpenGLWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y, 2);

    COpenGLWnd::OnRButtonDown(nFlags, point);
}


BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    m_camera.MouseWheel(zDelta);
    Invalidate();

    return COpenGLWnd::OnMouseWheel(nFlags, zDelta, pt);
}




void CChildView::OnAnimationRun()
{
	// TODO: Add your command handler code here
	if(m_spintimer)
    {
        KillTimer(m_spintimer);
        m_spintimer = 0;
    }
    else
    {
        m_spintimer = SetTimer(1, 30, NULL);
    }
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CGrVector lookAt = CGrVector(m_camera.CenterX() - m_camera.EyeX(),
	m_camera.CenterY() - m_camera.EyeY(),
	m_camera.CenterZ() - m_camera.EyeZ());
	CGrVector Up = CGrVector(m_camera.UpX(), m_camera.UpY(), m_camera.UpZ());
	// lookAt cross Up
	CGrVector right = CGrVector((lookAt.Y()*Up.Z())-(Up.Y()*lookAt.Z()), 
		-(lookAt.X()*Up.Z())+(Up.X()*lookAt.Z()),
		(lookAt.X()*Up.Y())-(Up.X()*lookAt.Y()));

	// Right cross Up
	CGrVector forward = CGrVector((Up.Y()*right.Z())-(right.Y()*Up.Z()),
    (Up.X()*right.Z())+(right.X()*Up.Z()),
    (Up.X()*right.Y())-(Up.Y()*right.X()));

	double distance = 0.1;
	switch(nChar)
	{
	case 0x41:		
		// A (track left)
		m_camera.SetEye(m_camera.EyeX() - (right.X() * distance), 
			m_camera.EyeY() - (right.Y() * distance), 
			m_camera.EyeZ() - (right.Z() * distance));
		m_camera.SetCenter(m_camera.CenterX() - (right.X() * distance), 
			m_camera.CenterY() - (right.Y() * distance), 
			m_camera.CenterZ() - (right.Z() * distance));
		break;
	case 0x57:
		// W (move closer)
		m_camera.SetEye(m_camera.EyeX() + (lookAt.X() * distance), 
			m_camera.EyeY() + (lookAt.Y() * distance), 
			m_camera.EyeZ() + (lookAt.Z() * distance));
		m_camera.SetCenter(m_camera.CenterX() + (lookAt.X() * distance), 
			m_camera.CenterY() + (lookAt.Y() * distance), 
			m_camera.CenterZ() + (lookAt.Z() * distance));
		break; 
	case 0x44:
		// D (track right)
		m_camera.SetEye(m_camera.EyeX() + (right.X() * distance), 
			m_camera.EyeY() + (right.Y() * distance), 
			m_camera.EyeZ() + (right.Z() * distance));
		m_camera.SetCenter(m_camera.CenterX() + (right.X() * distance), 
			m_camera.CenterY() + (right.Y() * distance), 
			m_camera.CenterZ() + (right.Z() * distance));
		break;
	case 0x53:
		// S (move further)
		m_camera.SetEye(m_camera.EyeX() - (lookAt.X() * distance), 
			m_camera.EyeY() - (lookAt.Y() * distance), 
			m_camera.EyeZ() - (lookAt.Z() * distance));
		m_camera.SetCenter(m_camera.CenterX() - (lookAt.X() * distance), 
			m_camera.CenterY() - (lookAt.Y() * distance), 
			m_camera.CenterZ() - (lookAt.Z() * distance));
		break;
	}
	Invalidate();
	COpenGLWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
