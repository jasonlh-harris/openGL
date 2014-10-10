#include "stdafx.h"
#include "YueFactory.h"
#include "SgPolygon.h"
#include "SgComposite.h"
#include "graphics\GrVector.h"
#include "SgPtr.h"
#include "SgTranslate.h"
#include "SgMaterial.h"
#include "SgRotateAroundPoint.h"
#include "SgMesh.h"
#include "SgPartSegment.h"
#include "SgTexture.h"
#include "SgCylinder.h"
#include "SgRotate.h"
#include "SgSphere.h"
#include "SgHole.h"

double PI2 = 3.1415926 * 2;

CYueFactory::CYueFactory(void)
{
}


CYueFactory::~CYueFactory(void)
{
}

void CYueFactory::Create(CSgComposite *root)
{

	CSgPtr <CSgComposite > dorm = new CSgComposite();
	CreateDorm(dorm);

	CSgPtr <CSgComposite > bed = new CSgComposite();
	Ball(bed);

	CSgPtr <CSgHole> hole = new CSgHole(0., 0., 0., 5. );

	CSgPtr <CSgTranslate> tran = new CSgTranslate( 0., 1.0,20.5 ); 
	tran->AddChild(hole);

	CSgPtr <CSgRotateAroundPoint> m_rt = new CSgRotateAroundPoint();
	m_rt->SetNormal(1, 0, 0);
	m_rt->SetAngle(180);
	m_rt->AddChild(hole);

	/*CSgPtr <CSgComposite > bed2 = new CSgComposite();
	CreateUnmadeBed(bed2);

	CSgPtr <CSgTranslate> tran2 = new CSgTranslate( 10., 1.0,20.5 ); 
	tran2->AddChild(bed2);*/

	/*CSgPtr <CSgComposite > make = new CSgComposite();
	MadeBed(make);

	CSgPtr <CSgTranslate> tran2 = new CSgTranslate( 0., 1.0,30.5 ); 
	tran2->AddChild(make);

	CSgPtr <CSgComposite > pil = new CSgComposite();
	Pillow(pil);

	CSgPtr <CSgTranslate> tran3 = new CSgTranslate( 0., 5.0,30.5 ); 
	tran3->AddChild(pil);*/

	root->AddChild(dorm);
	root->AddChild(m_rt);
	//root->AddChild(tran2);
	//root->AddChild(tran3);
	//m_root->AddChild(bed);
}

void CYueFactory::CreateMadeBed(CSgComposite *parent)
{
	CSgPtr <CSgMaterial> woodColor = new CSgMaterial();
	woodColor->SetDiffuseColor(0.398f, 0.199f, 0.f, 1.0f);
	woodColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	woodColor->SetShininess(5.f);

	CSgPtr <CSgMaterial> bedSetColor = new CSgMaterial();
	bedSetColor->SetDiffuseColor(0.f, 0.380f, 0.110f, 1.0f);
	bedSetColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	bedSetColor->SetShininess(5.f);
	
	CSgPtr <CSgComposite > bed = new CSgComposite();
	BedFrame(bed);

	CSgPtr <CSgComposite > make = new CSgComposite();
	MadeBed(make);

	CSgPtr <CSgComposite> pillow = new CSgComposite();
	Pillow(pillow);

	woodColor->AddChild(bed);

	CSgPtr <CSgTranslate> tran = new CSgTranslate( 0.2, 0.7, 2.4 ); 
	tran->AddChild(make);

	CSgPtr <CSgTranslate> tran2 = new CSgTranslate( 0.2, 2.6, 2.4 ); 
	tran2->AddChild(make);

	CSgPtr <CSgRotateAroundPoint> m_rt = new CSgRotateAroundPoint();
	m_rt->SetNormal(0, 1, 0);
	m_rt->SetAngle(-90);
	m_rt->AddChild(pillow);

	CSgPtr <CSgTranslate> m_tr = new CSgTranslate(0., 0., 1.3);
	m_tr->AddChild(m_rt);

	CSgPtr <CSgTranslate> tran3 = new CSgTranslate( 2.2, 0.7, 0.8 ); 
	tran3->AddChild(m_rt);

	CSgPtr <CSgTranslate> tran4 = new CSgTranslate( 2.2, 2.6, 0.8 ); 
	tran4->AddChild(m_rt);

	bedSetColor->AddChild(tran);
	bedSetColor->AddChild(tran2);
	bedSetColor->AddChild(tran3);
	bedSetColor->AddChild(tran4);

	parent->AddChild(woodColor);
	parent->AddChild(bedSetColor);
}

void CYueFactory::CreateUnmadeBed(CSgComposite *parent)
{
	CSgPtr <CSgMaterial> woodColor = new CSgMaterial();
	woodColor->SetDiffuseColor(.8f, .8f, .8f, 1.0f);
	woodColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	woodColor->SetShininess(5.f);

	CSgPtr <CSgMaterial> bedSetColor = new CSgMaterial();
	bedSetColor->SetDiffuseColor(0.804f, 0.608f, 0.114f, 1.0f);
	bedSetColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	bedSetColor->SetShininess(5.f);
	
	CSgPtr <CSgComposite > bed = new CSgComposite();
	BedFrame(bed);

	CSgPtr <CSgComposite > unmake = new CSgComposite();
	UnmadeBed(unmake);

	CSgPtr <CSgComposite > make = new CSgComposite();
	MadeBed(make);

	CSgPtr <CSgComposite> pillow = new CSgComposite();
	Pillow(pillow);

	woodColor->AddChild(bed);

	CSgPtr <CSgTranslate> tran = new CSgTranslate( 0.2, 0.7, 2.4 ); 
	tran->AddChild(make);

	CSgPtr <CSgTranslate> tran2 = new CSgTranslate( 1.775, 2.6, 2.4 ); 
	tran2->AddChild(unmake);

	CSgPtr <CSgRotateAroundPoint> m_rt = new CSgRotateAroundPoint();
	m_rt->SetNormal(0, 1, 0);
	m_rt->SetAngle(-90);
	m_rt->AddChild(pillow);

	CSgPtr <CSgTranslate> m_tr = new CSgTranslate(0., 0., 1.3);
	m_tr->AddChild(m_rt);

	CSgPtr <CSgTranslate> tran3 = new CSgTranslate( 2.2, 0.7, 0.8 ); 
	tran3->AddChild(m_rt);

	CSgPtr <CSgTranslate> tran4 = new CSgTranslate( 2.2, 2.6, 0.8 ); 
	tran4->AddChild(m_rt);

	bedSetColor->AddChild(tran);
	bedSetColor->AddChild(tran2);
	bedSetColor->AddChild(tran3);
	bedSetColor->AddChild(tran4);

	parent->AddChild(woodColor);
	parent->AddChild(bedSetColor);
}

void CYueFactory::CreateDorm(CSgComposite *parent)
{
	CSgPtr <CSgMesh> m_dorm = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},
	{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_dorm->AddNormal(n[x]);
	}

	for (int x = 0; x< 5; x++)
	{
		GLdouble v[22][4] = {
			{.5 + x * 8.5, 0., 0., 0.},
			{.5 + x * 8.5, 0., 9., 0.},
			{9. + x * 8.5, 0., 9., 0.},
			{9. + x * 8.5, 0., 0., 0.},

			{.5 + x * 8.5, 1., 0.5, 0.},
			{.5 + x * 8.5, 1., 9., 0.},
			{8.5 + x * 8.5, 1., 9., 0.},
			{8.5 + x * 8.5, 1., 0.5, 0.},

			{.5 + x * 8.5, 8., 0., 0.},
			{.5 + x * 8.5, 8., 0.5, 0.},
			{8.5 + x * 8.5, 8., 9., 0.},
			{9. + x * 8.5, 8., 9., 0.},
			{9. + x * 8.5, 8., 0., 0.},
			{8.5 + x * 8.5, 8., 0.5, 0.},

			{3.5 + x * 8.5, 6., 0.5, 0.},
			{3.5 + x * 8.5, 4., 0.5, 0.},
			{5.5 + x * 8.5, 4., 0.5, 0.},
			{5.5 + x * 8.5, 6., 0.5, 0.},

			{3.5 + x * 8.5, 6., 0., 0.},
			{3.5 + x * 8.5, 4., 0., 0.},
			{5.5 + x * 8.5, 4., 0., 0.},
			{5.5 + x * 8.5, 6., 0., 0.},
		};

		for (int y = 0; y<22; y++)
		{
			m_dorm->AddVertex(v[y]);
		}

		m_dorm->AddSelfTexturedQuad(0 + x*22, 3 + x*22, 2 + x*22, 1 + x*22, 3);
		m_dorm->AddSelfTexturedQuad(4 + x*22, 5 + x*22, 6 + x*22, 7 + x*22, 2);

		m_dorm->AddSelfTexturedQuad(5 + x*22, 1 + x*22, 2 + x*22, 6 + x*22, 4);
		m_dorm->AddSelfTexturedQuad(6 + x*22, 2 + x*22, 11 + x*22, 10 + x*22, 4);

		m_dorm->AddSelfTexturedQuad(10 + x*22, 13 + x*22, 7 + x*22, 6 + x*22, 1);

		m_dorm->AddSelfTexturedQuad(8 + x*22, 9 + x*22, 13 + x*22, 12 + x*22, 2);
		m_dorm->AddSelfTexturedQuad(12 + x*22, 13 + x*22, 10 + x*22, 11 + x*22, 2);

		m_dorm->AddSelfTexturedQuad(9 + x*22, 14 + x*22, 17 + x*22, 13 + x*22, 4);
		m_dorm->AddSelfTexturedQuad(9 + x*22, 4 + x*22, 15 + x*22, 14 + x*22, 4);
		m_dorm->AddSelfTexturedQuad(4 + x*22, 7 + x*22, 16 + x*22, 15 + x*22, 4);
		m_dorm->AddSelfTexturedQuad(7 + x*22, 13 + x*22, 17 + x*22, 16 + x*22, 4);

		m_dorm->AddSelfTexturedQuad(8 + x*22, 12 + x*22, 21 + x*22, 18 + x*22, 5);
		m_dorm->AddSelfTexturedQuad(19 + x*22, 0 + x*22, 8 + x*22, 18 + x*22, 5);
		m_dorm->AddSelfTexturedQuad(20 + x*22, 3 + x*22, 0 + x*22, 19 + x*22, 5);
		m_dorm->AddSelfTexturedQuad(20 + x*22, 21 + x*22, 12 + x*22, 3 + x*22, 5);

		m_dorm->AddSelfTexturedQuad(14 + x*22, 17 + x*22, 21 + x*22, 18 + x*22, 3);
		m_dorm->AddSelfTexturedQuad(19 + x*22, 15 + x*22, 16 + x*22, 20 + x*22, 2);
		m_dorm->AddSelfTexturedQuad(15 + x*22, 19 + x*22, 18 + x*22, 14 + x*22, 0);
		m_dorm->AddSelfTexturedQuad(20 + x*22, 16 + x*22, 17 + x*22, 21 + x*22, 1);

	}

	GLdouble v2[5][4]= { 
		{0., 0., 0., 0.}, 
		{0., 0., 9.0, 0.}, 
		{0., 8.0, 9.0, 0. },
		{.5, 8.0, 9.0, 0. },
		{0., 8.0, 0.0, 0. }
	};

	for (int x=0; x<5; x++)
	{
		m_dorm->AddVertex(v2[x]);
	}

	m_dorm->AddSelfTexturedQuad(110, 111, 112, 114, 1);
	m_dorm->AddSelfTexturedQuad(112, 113, 8, 114, 2);
	m_dorm->AddSelfTexturedQuad(111, 1, 113, 112, 4);
	m_dorm->AddSelfTexturedQuad(114, 8, 0, 110, 5);
	m_dorm->AddSelfTexturedQuad(110, 0, 1, 111, 3);

	m_dorm->AddSelfTexturedQuad(113, 5, 4, 9, 0);
	m_dorm->AddSelfTexturedQuad(11, 27, 26, 31, 0);
	m_dorm->AddSelfTexturedQuad(33, 49, 48, 53, 0);
	m_dorm->AddSelfTexturedQuad(55, 71, 70, 75, 0);
	m_dorm->AddSelfTexturedQuad(77, 93, 92, 97, 0);
	m_dorm->AddSelfTexturedQuad(99, 90, 91, 100, 0);

	CSgPtr <CSgMaterial> woodColor = new CSgMaterial();
	woodColor->SetDiffuseColor(1.f, 1.f, 1.f, 1.0f);
	woodColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	woodColor->SetShininess(5.f);

	woodColor->AddChild(m_dorm);

	CSgPtr<CSgTexture> m_dormTex = new CSgTexture(L"textures/plank01.bmp");

	m_dormTex->AddChild(woodColor);

	parent->AddChild(m_dormTex);
}

void CYueFactory::CreateBed(CSgComposite *parent)
{
	CSgPtr <CSgMesh> m_bed = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_bed->AddNormal(n[x]);
	}

	const int vetNum = 72;

	GLdouble v[vetNum][4] = {
		{0., 0., 0., 0.},
		{0., 0., 0.1, 0.},
		{0.1, 0., 0.1, 0.},
		{0.1, 0., 0., 0.},

		{.9, 0., 0., 0.},
		{.9, 0., 0.1, 0.},
		{1., 0., 0.1, 0.},
		{1., 0., 0., 0.},

		{0., 0., 2.1, 0.},
		{0., 0., 2.2, 0.},
		{0.1, 0., 2.2, 0.},
		{0.1, 0., 2.1, 0.},

		{0.9, 0., 2.1, 0.},
		{0.9, 0, 2.2, 0.},
		{1., 0., 2.2, 0.},
		{1., 0., 2.1, 0.},

		{0., 0.3, 0., 0.},
		{0., 0.3, 0.1, 0.},
		{0.1, 0.3, 0.1, 0.},
		{0.1, 0.3, 0., 0.},

		{0.9, 0.3, 0., 0.},
		{0.9, 0.3, 0.1, 0.},
		{1., 0.3, 0.1, 0.},
		{1., 0.3, 0., 0.},

		{0., 0.3, 2.1, 0.},
		{0., 0.3, 2.2, 0.},
		{0.1, 0.3, 2.2, 0.},
		{0.1, 0.3, 2.1, 0.},

		{0.9, 0.3, 2.1, 0.},
		{0.9, 0.3, 2.2, 0.},
		{1., 0.3, 2.2, 0.},
		{1., 0.3, 2.1, 0.},


		{0., 0.4, 0., 0.},
		{0., 0.4, 0.1, 0.},
		{0.1, 0.4, 0.1, 0.},
		{0.1, 0.4, 0., 0.},

		{0.9, 0.4, 0., 0.},
		{0.9, 0.4, 0.1, 0.},
		{1., 0.4, 0.1, 0.},
		{1., 0.4, 0., 0.},

		{0., 0.4, 2.1, 0.},
		{0., 0.4, 2.2, 0.},
		{0.1, 0.4, 2.2, 0.},
		{0.1, 0.4, 2.1, 0.},

		{0.9, 0.4, 2.1, 0.},
		{0.9, 0.4, 2.2, 0.},
		{1., 0.4, 2.2, 0.},
		{1., 0.4, 2.1, 0.},


		{0.2, 0.4, 0.1, 0.},
		{0.2, 0.4, 2.1, 0.},
		{0.8, 0.4, 2.1, 0.},
		{0.8, 0.4, 0.1, 0.},

		{0.2, 0.5, 0.1, 0.},
		{0.2, 0.5, 2.1, 0.},
		{0.8, 0.5, 2.1, 0.},
		{0.8, 0.5, 0.1, 0.},

		{0., 0.8, 0., 0.},
		{0., 0.8, 0.1, 0.},
		{0.1, 0.8, 0.1, 0.},
		{0.1, 0.8, 0., 0.},

		{0.9, 0.8, 0., 0.},
		{0.9, 0.8, 0.1, 0.},
		{1., 0.8, 0.1, 0.},
		{1., 0.8, 0., 0.},

		{0., 0.8, 2.1, 0.},
		{0., 0.8, 2.2, 0.},
		{0.1, 0.8, 2.2, 0.},
		{0.1, 0.8, 2.1, 0.},

		{0.9, 0.8, 2.1, 0.},
		{0.9, 0.8, 2.2, 0.},
		{1., 0.8, 2.2, 0.},
		{1., 0.8, 2.1, 0.},
	};

	for (int x = 0; x<vetNum; x++)
	{
		m_bed->AddVertex(v[x]);
	}

	m_bed->AddSelfTexturedQuad(0, 3, 2, 1, 3);
	m_bed->AddSelfTexturedQuad(4, 7, 6, 5, 3);
	m_bed->AddSelfTexturedQuad(12, 15, 14, 13, 3);
	m_bed->AddSelfTexturedQuad(8, 11, 10, 9, 3);

	/*m_bed->AddSelfTexturedQuad(16, 17, 18, 19, 2);
	m_bed->AddSelfTexturedQuad(20, 21, 22, 23, 2);
	m_bed->AddSelfTexturedQuad(24, 25, 26, 27, 2);
	m_bed->AddSelfTexturedQuad(28, 29, 30, 31, 2);*/

	m_bed->AddSelfTexturedQuad(0, 16, 19, 3, 5);
	m_bed->AddSelfTexturedQuad(4, 20, 23, 7, 5);
	m_bed->AddSelfTexturedQuad(9, 10, 26, 25, 4);
	m_bed->AddSelfTexturedQuad(13, 14, 30, 29, 4);

	m_bed->AddSelfTexturedQuad(1, 2, 18, 17, 4);
	m_bed->AddSelfTexturedQuad(5, 6, 22, 21, 4);
	m_bed->AddSelfTexturedQuad(11, 8, 24, 27, 5);
	m_bed->AddSelfTexturedQuad(15, 12, 28, 31, 5);

	m_bed->AddSelfTexturedQuad(2, 3, 19, 18, 0);
	m_bed->AddSelfTexturedQuad(6, 7, 23, 22, 0);
	m_bed->AddSelfTexturedQuad(10, 11, 27, 26, 0);
	m_bed->AddSelfTexturedQuad(14, 15, 31, 30, 0);

	m_bed->AddSelfTexturedQuad(0, 1, 17, 16, 1);
	m_bed->AddSelfTexturedQuad(4, 5, 21, 20, 1);
	m_bed->AddSelfTexturedQuad(8, 9, 25, 24, 1);
	m_bed->AddSelfTexturedQuad(12, 13, 29, 28, 1);

	m_bed->AddSelfTexturedQuad(18, 21, 28, 27, 3);
	m_bed->AddSelfTexturedQuad(26, 27, 28, 29, 3);
	m_bed->AddSelfTexturedQuad(17, 18, 27, 24, 3);
	m_bed->AddSelfTexturedQuad(21, 22, 31, 28, 3);
	m_bed->AddSelfTexturedQuad(18, 19, 20, 21, 3);

	m_bed->AddSelfTexturedQuad(35, 34, 37, 36, 2);
	m_bed->AddSelfTexturedQuad(33, 40, 43, 34, 2);
	m_bed->AddSelfTexturedQuad(43, 42, 45, 44, 2);
	m_bed->AddSelfTexturedQuad(37, 44, 47, 38, 2);

	m_bed->AddSelfTexturedQuad(41, 25, 26, 42, 4);
	m_bed->AddSelfTexturedQuad(42, 26, 29, 45, 4);
	m_bed->AddSelfTexturedQuad(45, 29, 30, 46, 4);

	m_bed->AddSelfTexturedQuad(32, 35, 19, 16, 5);
	m_bed->AddSelfTexturedQuad(35, 36, 20, 19, 5);
	m_bed->AddSelfTexturedQuad(36, 39, 23, 20, 5);

	m_bed->AddSelfTexturedQuad(47, 46, 30, 31, 0);
	m_bed->AddSelfTexturedQuad(38, 47, 31, 22, 0);
	m_bed->AddSelfTexturedQuad(39, 38, 22, 23, 0);

	m_bed->AddSelfTexturedQuad(33, 32, 16, 17, 1);
	m_bed->AddSelfTexturedQuad(40, 33, 17, 24, 1);
	m_bed->AddSelfTexturedQuad(41, 40, 24, 25, 1);
	//m_bed->AddSelfTexturedQuad(37, 44, 47, 38, 2);

	m_bed->AddSelfTexturedQuad(34, 43, 49, 48, 2);
	m_bed->AddSelfTexturedQuad(51, 50, 44, 37, 2);

	m_bed->AddSelfTexturedQuad(52, 53, 54, 55, 2);

	m_bed->AddSelfTexturedQuad(55, 54, 50, 51, 0);
	m_bed->AddSelfTexturedQuad(53, 52, 48, 49, 1);
	m_bed->AddSelfTexturedQuad(54, 53, 49, 50, 4);
	m_bed->AddSelfTexturedQuad(52, 55, 51, 48, 5);

	for (int x=0; x<4; x++)
	{
		m_bed->AddSelfTexturedQuad(34+4*x, 35+4*x, 59+4*x, 58+4*x, 0);
		m_bed->AddSelfTexturedQuad(32+4*x, 33+4*x, 57+4*x, 56+4*x, 1);
		m_bed->AddSelfTexturedQuad(33+4*x, 34+4*x, 58+4*x, 57+4*x, 4);
		m_bed->AddSelfTexturedQuad(56+4*x, 59+4*x, 35+4*x, 32+4*x, 5);
	}

	parent->AddChild(m_bed);
}

void CYueFactory::BedFrame(CSgComposite *parent)
{
	CSgPtr <CSgMesh> m_bed = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_bed->AddNormal(n[x]);
	}

	GLdouble Length = 6.0;
	GLdouble Height = 3.0;
	GLdouble Width = 3.0;

	GLdouble HeightPoints[10] = { 0., 0.5, 0.7, 1.2, 1.4, 2.4, 2.6, 3.1, 3.3, 3.5 };

	for (int x = 0; x < 10; x++)
	{
		m_bed->AddVertex(0. ,HeightPoints[x], 0.);
		m_bed->AddVertex(0.,HeightPoints[x], 0.4);
		m_bed->AddVertex(0.4,HeightPoints[x], 0.4);
		m_bed->AddVertex(0.4,HeightPoints[x], 0.);

		m_bed->AddVertex(0. ,HeightPoints[x] ,Length - 0.4 );
		m_bed->AddVertex(0. ,HeightPoints[x] ,Length );
		m_bed->AddVertex(0.4 ,HeightPoints[x] ,Length );
		m_bed->AddVertex(0.4 ,HeightPoints[x] , Length - 0.4);
		
		
		m_bed->AddVertex(Width - 0.4 ,HeightPoints[x] , 0.);
		m_bed->AddVertex(Width - 0.4 ,HeightPoints[x] , 0.4);
		m_bed->AddVertex(Width ,HeightPoints[x] , 0.4);
		m_bed->AddVertex(Width ,HeightPoints[x] , 0.);



		m_bed->AddVertex(Width - 0.4 ,HeightPoints[x] , Length - 0.4);
		m_bed->AddVertex(Width - 0.4 ,HeightPoints[x] , Length);
		m_bed->AddVertex(Width ,HeightPoints[x] , Length);
		m_bed->AddVertex(Width ,HeightPoints[x] , Length - 0.4);
		
	}

	GLdouble SideHeightPoints[8] = { 0.5, 0.7, 1.2, 1.4, 2.4, 2.6, 3.1, 3.3 };

	for (int x = 0; x < 8; x++)
	{
		m_bed->AddVertex(0.85 ,SideHeightPoints[x], 0.);
		m_bed->AddVertex(0.85,SideHeightPoints[x], 0.4);
		m_bed->AddVertex(1.05,SideHeightPoints[x], 0.4);
		m_bed->AddVertex(1.05,SideHeightPoints[x], 0.);

		m_bed->AddVertex(0.85 ,SideHeightPoints[x] ,Length - 0.4 );
		m_bed->AddVertex(0.85 ,SideHeightPoints[x] ,Length );
		m_bed->AddVertex(1.05 ,SideHeightPoints[x] ,Length );
		m_bed->AddVertex(1.05 ,SideHeightPoints[x] , Length - 0.4);

		m_bed->AddVertex(Width - 1.05, SideHeightPoints[x] , 0.);
		m_bed->AddVertex(Width - 1.05, SideHeightPoints[x] , 0.4);
		m_bed->AddVertex(Width - 0.85, SideHeightPoints[x] , 0.4);
		m_bed->AddVertex(Width - 0.85, SideHeightPoints[x] , 0.);

		m_bed->AddVertex(Width - 1.05, SideHeightPoints[x] , Length - 0.4);
		m_bed->AddVertex(Width - 1.05, SideHeightPoints[x] , Length);
		m_bed->AddVertex(Width - 0.85, SideHeightPoints[x] , Length);
		m_bed->AddVertex(Width -0.85, SideHeightPoints[x] , Length - 0.4);
	}

	for (int x = 0; x <9; x++)
	{
		m_bed->AddSelfTexturedQuad( 3+x*16, 0+x*16, 16+x*16, 19+x*16, 5);
		m_bed->AddSelfTexturedQuad( 11+x*16, 8+x*16, 24+x*16, 27+x*16, 5);

		m_bed->AddSelfTexturedQuad( 5+x*16, 6+x*16, 22+x*16, 21+x*16, 4);
		m_bed->AddSelfTexturedQuad( 13+x*16, 14+x*16, 30+x*16, 29+x*16, 4);

		m_bed->AddSelfTexturedQuad( 10+x*16, 11+x*16, 27+x*16, 26+x*16, 0);
		m_bed->AddSelfTexturedQuad( 14+x*16, 15+x*16, 31+x*16, 30+x*16, 0);

		m_bed->AddSelfTexturedQuad( 0+x*16, 1+x*16, 17+x*16, 16+x*16, 1);
		m_bed->AddSelfTexturedQuad( 4+x*16, 5+x*16, 21+x*16, 20+x*16, 1);
	}

	for (int x = 0; x<2; x++)
	{
		m_bed->AddSelfTexturedQuad( 22+4*x*16, 29+4*x*16, 45+4*x*16, 38+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 181+4*x*16, 182+4*x*16, 198+4*x*16, 197+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 189+4*x*16, 190+4*x*16, 206+4*x*16, 205+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 54+4*x*16, 61+4*x*16, 77+4*x*16, 70+4*x*16, 4);

		m_bed->AddSelfTexturedQuad( 24+4*x*16, 19+4*x*16, 35+4*x*16, 40+4*x*16, 5);
		m_bed->AddSelfTexturedQuad( 179+4*x*16, 176+4*x*16, 192+4*x*16, 195+4*x*16, 5);
		m_bed->AddSelfTexturedQuad( 187+4*x*16, 184+4*x*16, 200+4*x*16, 203+4*x*16, 5);
		m_bed->AddSelfTexturedQuad( 56+4*x*16, 51+4*x*16, 67+4*x*16, 72+4*x*16, 5);

		m_bed->AddSelfTexturedQuad( 31+4*x*16, 26+4*x*16, 42+4*x*16, 47+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 17+4*x*16, 20+4*x*16, 36+4*x*16, 33+4*x*16, 1);

		m_bed->AddSelfTexturedQuad( 178+4*x*16, 179+4*x*16, 195+4*x*16, 194+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 186+4*x*16, 187+4*x*16, 203+4*x*16, 202+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 182+4*x*16, 183+4*x*16, 199+4*x*16, 198+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 190+4*x*16, 191+4*x*16, 207+4*x*16, 206+4*x*16, 0);

		m_bed->AddSelfTexturedQuad( 176+4*x*16, 177+4*x*16, 193+4*x*16, 192+4*x*16, 1);
		m_bed->AddSelfTexturedQuad( 180+4*x*16, 181+4*x*16, 197+4*x*16, 196+4*x*16, 1);
		m_bed->AddSelfTexturedQuad( 184+4*x*16, 185+4*x*16, 201+4*x*16, 200+4*x*16, 1);
		m_bed->AddSelfTexturedQuad( 188+4*x*16, 189+4*x*16, 205+4*x*16, 204+4*x*16, 1);

		m_bed->AddSelfTexturedQuad( 177+4*x*16, 178+4*x*16, 194+4*x*16, 193+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 185+4*x*16, 186+4*x*16, 202+4*x*16, 201+4*x*16, 4);
		
		m_bed->AddSelfTexturedQuad( 183+4*x*16, 180+4*x*16, 196+4*x*16, 199+4*x*16, 5);
		m_bed->AddSelfTexturedQuad( 191+4*x*16, 188+4*x*16, 204+4*x*16, 207+4*x*16, 5);

		m_bed->AddSelfTexturedQuad( 34+4*x*16, 39+4*x*16, 44+4*x*16, 41+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 18+4*x*16, 25+4*x*16, 28+4*x*16, 23+4*x*16, 3);

		m_bed->AddSelfTexturedQuad( 71+4*x*16, 70+4*x*16, 77+4*x*16, 76+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 67+4*x*16, 66+4*x*16, 73+4*x*16, 72+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 22+4*x*16, 23+4*x*16, 28+4*x*16, 29+4*x*16, 3);
		m_bed->AddSelfTexturedQuad( 18+4*x*16, 19+4*x*16, 24+4*x*16, 25+4*x*16, 3);

		m_bed->AddSelfTexturedQuad( 33+4*x*16, 36+4*x*16, 39+4*x*16, 34+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 41+4*x*16, 44+4*x*16, 47+4*x*16, 42+4*x*16, 2);

		m_bed->AddSelfTexturedQuad( 18+4*x*16, 23+4*x*16, 20+4*x*16, 17+4*x*16, 3);
		m_bed->AddSelfTexturedQuad( 25+4*x*16, 26+4*x*16, 31+4*x*16, 28+4*x*16, 3);

		m_bed->AddSelfTexturedQuad( 50+4*x*16, 57+4*x*16, 73+4*x*16, 66+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 60+4*x*16, 55+4*x*16, 71+4*x*16, 76+4*x*16, 5);
		//m_bed->AddSelfTexturedQuad( 190+4*x*16, 191+4*x*16, 207+4*x*16, 206+4*x*16, 2);

		m_bed->AddSelfTexturedQuad( 39+4*x*16, 38+4*x*16, 181+4*x*16, 180+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 183+4*x*16, 182+4*x*16, 189+4*x*16, 188+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 191+4*x*16, 190+4*x*16, 45+4*x*16, 44+4*x*16, 2);

		m_bed->AddSelfTexturedQuad( 35+4*x*16, 34+4*x*16, 177+4*x*16, 176+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 179+4*x*16, 178+4*x*16, 185+4*x*16, 184+4*x*16, 2);
		m_bed->AddSelfTexturedQuad( 187+4*x*16, 186+4*x*16, 41+4*x*16, 40+4*x*16, 2);

		m_bed->AddSelfTexturedQuad( 51+4*x*16, 192+4*x*16, 193+4*x*16, 50+4*x*16, 3);
		m_bed->AddSelfTexturedQuad( 195+4*x*16, 200+4*x*16, 201+4*x*16, 194+4*x*16, 3);
		m_bed->AddSelfTexturedQuad( 203+4*x*16, 56+4*x*16, 57+4*x*16, 202+4*x*16, 3);

		m_bed->AddSelfTexturedQuad( 55+4*x*16, 196+4*x*16, 197+4*x*16, 54+4*x*16, 3);
		m_bed->AddSelfTexturedQuad( 199+4*x*16, 204+4*x*16, 205+4*x*16, 198+4*x*16, 3);
		m_bed->AddSelfTexturedQuad( 207+4*x*16, 60+4*x*16, 61+4*x*16, 206+4*x*16, 3);

		m_bed->AddSelfTexturedQuad( 34+4*x*16, 35+4*x*16, 51+4*x*16, 50+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 38+4*x*16, 39+4*x*16, 55+4*x*16, 54+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 40+4*x*16, 41+4*x*16, 57+4*x*16, 56+4*x*16, 1);
		m_bed->AddSelfTexturedQuad( 44+4*x*16, 45+4*x*16, 61+4*x*16, 60+4*x*16, 1);

		m_bed->AddSelfTexturedQuad( 33+4*x*16, 34+4*x*16, 50+32+4*x*16, 49+32+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 41+4*x*16, 42+4*x*16, 58+32+4*x*16, 57+32+4*x*16, 4);
		m_bed->AddSelfTexturedQuad( 39+4*x*16, 36+4*x*16, 52+32+4*x*16, 55+32+4*x*16, 5);
		m_bed->AddSelfTexturedQuad( 47+4*x*16, 44+4*x*16, 60+32+4*x*16, 63+32+4*x*16, 5);

		m_bed->AddSelfTexturedQuad( 6+64+4*x*16, 7+64+4*x*16, 23+64+4*x*16, 22+64+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 2+64+4*x*16, 3+64+4*x*16, 19+64+4*x*16, 18+64+4*x*16, 0);
		m_bed->AddSelfTexturedQuad( 12+64+4*x*16, 13+64+4*x*16, 29+64+4*x*16, 28+64+4*x*16, 1);
		m_bed->AddSelfTexturedQuad( 8+64+4*x*16, 9+64+4*x*16, 25+64+4*x*16, 24+64+4*x*16, 1);

	}

	m_bed->AddSelfTexturedQuad( 0+16*9, 1+16*9, 2+16*9, 3+16*9, 2);
	m_bed->AddSelfTexturedQuad( 4+16*9, 5+16*9, 6+16*9, 7+16*9, 2);
	m_bed->AddSelfTexturedQuad( 8+16*9, 9+16*9, 10+16*9, 11+16*9, 2);
	m_bed->AddSelfTexturedQuad( 12+16*9, 13+16*9, 14+16*9, 15+16*9, 2);

	m_bed->AddSelfTexturedQuad( 0, 3, 2, 1, 3);
	m_bed->AddSelfTexturedQuad( 4, 7, 6, 5, 3);
	m_bed->AddSelfTexturedQuad( 8, 11, 10, 9, 3);
	m_bed->AddSelfTexturedQuad( 12, 15, 14, 13, 3);

	m_bed->AddSelfTexturedQuad( 1, 2, 18, 17, 4);
	m_bed->AddSelfTexturedQuad( 9, 10, 26, 25, 4);
	m_bed->AddSelfTexturedQuad( 7, 4, 20, 23, 5);
	m_bed->AddSelfTexturedQuad( 15, 12, 28, 31, 5);

	m_bed->AddSelfTexturedQuad( 6, 7, 23, 22, 0);
	m_bed->AddSelfTexturedQuad( 2, 3, 19, 18, 0);
	m_bed->AddSelfTexturedQuad( 12, 13, 29, 28, 1);
	m_bed->AddSelfTexturedQuad( 8, 9, 25, 24, 1);


	CSgPtr<CSgTexture> m_bedTex = new CSgTexture(L"textures/light_wood_texture.jpg");

	m_bedTex->AddChild(m_bed);

	parent->AddChild(m_bedTex);
}

void CYueFactory::UnmadeBed(CSgComposite *parent)
{
	CSgPtr <CSgMesh> m_mesh = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_mesh->AddNormal(n[x]);
	}

	GLdouble Length = 3.0;
	GLdouble Width = 1.1;
	GLdouble Thick = 0.25;

	m_mesh->AddVertex( 0.125, 0.0, 0.0 );
	m_mesh->AddVertex( 0.125, 0.0, Length );
	m_mesh->AddVertex( 0.125+Width, 0.0, Length );
	m_mesh->AddVertex( 0.125+Width, 0.0, 0.0 );

	m_mesh->AddVertex( 0.125, Thick, 0.0 );
	m_mesh->AddVertex( 0.125, Thick, Length );
	m_mesh->AddVertex( 0.125+Width, Thick, Length );
	m_mesh->AddVertex( 0.125+Width, Thick, 0.0 );

	m_mesh->AddFlatQuad( 4, 5, 6, 7, 2 );
	m_mesh->AddFlatQuad( 0, 3, 2, 1, 3 );
	m_mesh->AddFlatQuad( 5, 1, 2, 6, 4 );
	m_mesh->AddFlatQuad( 4, 7, 3, 0, 5 );

    CSgPtr <CSgPartSegment> m_ps = new CSgPartSegment();
	m_ps->SetProperties( 0.125, 0., 1., 0., 0.125, 3., 1., 0., 16);
	CSgPtr <CSgPartSegment> m_psb = new CSgPartSegment();
	m_psb->SetProperties( 0., 0., 0., -1., 0.125, 0., 0., -1., 16);
	CSgPtr <CSgPartSegment> m_pst = new CSgPartSegment();
	m_pst->SetProperties( 0.125, 3., 0., 1., 0., 3., 0., 1., 16);
	
	CSgPtr <CSgComposite> m_c = new CSgComposite();
	m_c->AddChild(m_ps);
	m_c->AddChild(m_psb);
	m_c->AddChild(m_pst);
	
	CSgPtr <CSgTranslate> m_tr = new CSgTranslate(0.125, 0, 0.125);
	m_tr->AddChild(m_c);

	CSgPtr <CSgRotateAroundPoint> m_rt = new CSgRotateAroundPoint();
	m_rt->SetNormal(0, 1, 0);
	m_rt->SetAngle(90);
	m_rt->AddChild(m_tr);

	CSgPtr <CSgRotateAroundPoint> m_rt2 = new CSgRotateAroundPoint();
	m_rt2->SetNormal(1, 0, 0);
	m_rt2->SetAngle(90);
	m_rt2->AddChild(m_rt);

	CSgPtr <CSgComposite> m_c2 = new CSgComposite();
	m_c2->AddChild(m_rt2);
	m_c2->AddChild(m_mesh);

	CSgPtr <CSgRotateAroundPoint> m_rt3 = new CSgRotateAroundPoint();
	m_rt3->SetTranslation(1.475, -1.225, 0);
	m_rt3->SetNormal(0, 0, 1);
	m_rt3->SetAngle(90);
	m_rt3->AddChild(m_c2);

	CSgPtr <CSgPartSegment> m_ps2 = new CSgPartSegment();
	m_ps2->SetProperties( 0.25, 0., 1., 0., 0.25, 3., 1., 0., 24);
	CSgPtr <CSgPartSegment> m_psb2 = new CSgPartSegment();
	m_psb2->SetProperties( 0., 0., 0., -1., 0.25, 0., 0., -1., 24);
	CSgPtr <CSgPartSegment> m_pst2 = new CSgPartSegment();
	m_pst2->SetProperties( 0.25, 3., 0., 1., 0., 3., 0., 1., 24);

	CSgPtr <CSgRotateAroundPoint> m_rt4 = new CSgRotateAroundPoint();
	m_rt4->SetTranslation(1.225, 0, 0);
	m_rt4->SetNormal(1, 0, 0);
	m_rt4->SetAngle(90);
	m_rt4->AddChild(m_ps2);
	m_rt4->AddChild(m_pst2);
	m_rt4->AddChild(m_psb2);

	parent->AddChild(m_c2);
	parent->AddChild(m_rt3);
	parent->AddChild(m_rt4);
}

void CYueFactory::MadeBed(CSgComposite *parent)
{
	CSgPtr <CSgMesh> m_mesh = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_mesh->AddNormal(n[x]);
	}

	GLdouble Length = 3.0;
	GLdouble Width = 2.2;
	GLdouble Thick = 0.25;

	m_mesh->AddVertex( 0.125, 0.0, 0.0 );
	m_mesh->AddVertex( 0.125, 0.0, Length );
	m_mesh->AddVertex( 0.125+Width, 0.0, Length );
	m_mesh->AddVertex( 0.125+Width, 0.0, 0.0 );

	m_mesh->AddVertex( 0.125, Thick, 0.0 );
	m_mesh->AddVertex( 0.125, Thick, Length );
	m_mesh->AddVertex( 0.125+Width, Thick, Length );
	m_mesh->AddVertex( 0.125+Width, Thick, 0.0 );

	m_mesh->AddFlatQuad( 4, 5, 6, 7, 2 );
	m_mesh->AddFlatQuad( 0, 3, 2, 1, 3 );
	m_mesh->AddFlatQuad( 5, 1, 2, 6, 4 );
	m_mesh->AddFlatQuad( 4, 7, 3, 0, 5 );

    CSgPtr <CSgPartSegment> m_ps = new CSgPartSegment();
	m_ps->SetProperties( 0.125, 0., 1., 0., 0.125, 3., 1., 0., 16);
	CSgPtr <CSgPartSegment> m_psb = new CSgPartSegment();
	m_psb->SetProperties( 0., 0., 0., -1., 0.125, 0., 0., -1., 16);
	CSgPtr <CSgPartSegment> m_pst = new CSgPartSegment();
	m_pst->SetProperties( 0.125, 3., 0., 1., 0., 3., 0., 1., 16);
	
	CSgPtr <CSgComposite> m_c = new CSgComposite();
	m_c->AddChild(m_ps);
	m_c->AddChild(m_psb);
	m_c->AddChild(m_pst);
	
	CSgPtr <CSgTranslate> m_tr = new CSgTranslate(0.125, 0, 0.125);
	m_tr->AddChild(m_c);

	CSgPtr <CSgRotateAroundPoint> m_rt = new CSgRotateAroundPoint();
	m_rt->SetNormal(0, 1, 0);
	m_rt->SetAngle(90);
	m_rt->AddChild(m_tr);

	CSgPtr <CSgRotateAroundPoint> m_rt2 = new CSgRotateAroundPoint();
	m_rt2->SetNormal(1, 0, 0);
	m_rt2->SetAngle(90);
	m_rt2->AddChild(m_rt);

	CSgPtr <CSgPartSegment> m_ps2 = new CSgPartSegment();
	m_ps2->SetProperties( 0.125, 0., 1., 0., 0.125, 3., 1., 0., 16);
	CSgPtr <CSgPartSegment> m_psb2 = new CSgPartSegment();
	m_psb2->SetProperties( 0., 0., 0., -1., 0.125, 0., 0., -1., 16);
	CSgPtr <CSgPartSegment> m_pst2 = new CSgPartSegment();
	m_pst2->SetProperties( 0.125, 3., 0., 1., 0., 3., 0., 1., 16);
	
	CSgPtr <CSgComposite> m_c2 = new CSgComposite();
	m_c2->AddChild(m_ps2);
	m_c2->AddChild(m_psb2);
	m_c2->AddChild(m_pst2);

	CSgPtr <CSgTranslate> m_tr2 = new CSgTranslate(0.125, -3., -2.3125);
	m_tr2->AddChild(m_c2);

	CSgPtr <CSgRotateAroundPoint> m_rt3 = new CSgRotateAroundPoint();
	m_rt3->SetNormal(0, 1, 0);
	m_rt3->SetAngle(-90);
	m_rt3->AddChild(m_tr2);

	CSgPtr <CSgRotateAroundPoint> m_rt4 = new CSgRotateAroundPoint();
	m_rt4->SetNormal(1, 0, 0);
	m_rt4->SetAngle(-90);
	m_rt4->AddChild(m_rt3);

	//CSgPtr <CSgCylinder> m_c = new CSgCylinder();
	//m_c->SetProperties(5.0, 5.0);

    
	//parent->AddChild(m_c);
	parent->AddChild(m_rt2);
	parent->AddChild(m_rt4);
	parent->AddChild(m_mesh);
}

void CYueFactory::Pillow(CSgComposite *parent)
{
	CSgPtr <CSgMesh> m_mesh = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_mesh->AddNormal(n[x]);
	}

	GLdouble Length = 1.6;
	GLdouble Width = 0.8;
	GLdouble Thick = 0.25;

	m_mesh->AddVertex( 0.125, 0.0, 0.0 );
	m_mesh->AddVertex( 0.125, 0.0, Length );
	m_mesh->AddVertex( 0.125+Width, 0.0, Length );
	m_mesh->AddVertex( 0.125+Width, 0.0, 0.0 );

	m_mesh->AddVertex( 0.125, Thick, 0.0 );
	m_mesh->AddVertex( 0.125, Thick, Length );
	m_mesh->AddVertex( 0.125+Width, Thick, Length );
	m_mesh->AddVertex( 0.125+Width, Thick, 0.0 );

	m_mesh->AddFlatQuad( 4, 5, 6, 7, 2 );
	m_mesh->AddFlatQuad( 0, 3, 2, 1, 3 );
	m_mesh->AddFlatQuad( 5, 1, 2, 6, 4 );
	m_mesh->AddFlatQuad( 4, 7, 3, 0, 5 );

    CSgPtr <CSgPartSegment> m_ps = new CSgPartSegment();
	m_ps->SetProperties( 0.125, 0., 1., 0., 0.125, 1.6, 1., 0., 16);
	CSgPtr <CSgPartSegment> m_psb = new CSgPartSegment();
	m_psb->SetProperties( 0., 0., 0., -1., 0.125, 0., 0., -1., 16);
	CSgPtr <CSgPartSegment> m_pst = new CSgPartSegment();
	m_pst->SetProperties( 0.125, 1.6, 0., 1., 0., 1.6, 0., 1., 16);
	
	CSgPtr <CSgComposite> m_c = new CSgComposite();
	m_c->AddChild(m_ps);
	m_c->AddChild(m_psb);
	m_c->AddChild(m_pst);
	
	CSgPtr <CSgTranslate> m_tr = new CSgTranslate(0.125, 0, 0.125);
	m_tr->AddChild(m_c);

	CSgPtr <CSgRotateAroundPoint> m_rt = new CSgRotateAroundPoint();
	m_rt->SetNormal(0, 1, 0);
	m_rt->SetAngle(90);
	m_rt->AddChild(m_tr);

	CSgPtr <CSgRotateAroundPoint> m_rt2 = new CSgRotateAroundPoint();
	m_rt2->SetNormal(1, 0, 0);
	m_rt2->SetAngle(90);
	m_rt2->AddChild(m_rt);

	CSgPtr <CSgPartSegment> m_ps2 = new CSgPartSegment();
	m_ps2->SetProperties( 0.125, 0., 1., 0., 0.125, 1.6, 1., 0., 16);
	CSgPtr <CSgPartSegment> m_psb2 = new CSgPartSegment();
	m_psb2->SetProperties( 0., 0., 0., -1., 0.125, 0., 0., -1., 16);
	CSgPtr <CSgPartSegment> m_pst2 = new CSgPartSegment();
	m_pst2->SetProperties( 0.125, 1.6, 0., 1., 0., 1.6, 0., 1., 16);
	
	CSgPtr <CSgComposite> m_c2 = new CSgComposite();
	m_c2->AddChild(m_ps2);
	m_c2->AddChild(m_psb2);
	m_c2->AddChild(m_pst2);

	CSgPtr <CSgTranslate> m_tr2 = new CSgTranslate(-0.125, 0., -0.9125);
	m_tr2->AddChild(m_c2);

	CSgPtr <CSgRotateAroundPoint> m_rt3 = new CSgRotateAroundPoint();
	m_rt3->SetNormal(0, 1, 0);
	m_rt3->SetAngle(270);
	m_rt3->AddChild(m_tr2);

	CSgPtr <CSgRotateAroundPoint> m_rt4 = new CSgRotateAroundPoint();
	m_rt4->SetNormal(1, 0, 0);
	m_rt4->SetAngle(90);
	m_rt4->AddChild(m_rt3);

   /* CSgPtr <CSgComposite> m_c3 = new CSgComposite();

	m_c3->AddChild(m_rt2);
	m_c3->AddChild(m_rt4);
	m_c3->AddChild(m_mesh);

	CSgPtr <CSgRotateAroundPoint> m_rt5 = new CSgRotateAroundPoint();
	m_rt5->SetNormal(0, 1, 0);
	m_rt5->SetAngle(90);
	m_rt5->AddChild(m_c3);

	CSgPtr <CSgTranslate> m_tr3 = new CSgTranslate(0., 0., 1.3);
	m_tr3->AddChild(m_rt5);*/

	parent->AddChild(m_mesh);
	parent->AddChild(m_rt2);
	parent->AddChild(m_rt4);
	
}

void CYueFactory::CreateHoop(CSgComposite *parent)
{
	CSgPtr <CSgComposite> m_base = new CSgComposite();
	HoopBase(m_base);

	CSgPtr <CSgComposite> m_rebound = new CSgComposite();
	Rebound(m_rebound);

	CSgPtr <CSgComposite> m_rim = new CSgComposite();
	Rim(m_rim);

	CSgPtr <CSgTranslate> tran = new CSgTranslate(-1.5, 4., -0.2);
	tran->AddChild(m_rebound);

	CSgPtr <CSgTranslate> tran2 = new CSgTranslate(0.3, 4., 0.5);
	tran2->AddChild(m_rim);

	parent->AddChild(m_base);
	parent->AddChild(tran);
	parent->AddChild(tran2);
}

void CYueFactory::HoopBase(CSgComposite *parent)
{
	CSgPtr <CSgMaterial> baseColor = new CSgMaterial();
	baseColor->SetDiffuseColor(0.f, 0.f, 0.f, 0.0f);
	baseColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	baseColor->SetShininess(10.f);

	CSgPtr <CSgPartSegment> round = new CSgPartSegment();
	round->SetProperties( 1.5, 0., 1., 0., 1.5, 0.3, 1., 0., 0);

	CSgPtr <CSgPartSegment> base = new CSgPartSegment();
	base->SetProperties( 0., 0., 0., -1., 1.5, 0., 0., -1., 0);

	CSgPtr <CSgPartSegment> baseTop = new CSgPartSegment();
	baseTop->SetProperties( 1.5, 0.3, 0., 1., 0.2, 0.3, 0., 1., 0);

	baseColor->AddChild(round);
	baseColor->AddChild(base);
	baseColor->AddChild(baseTop);

	CSgPtr <CSgMaterial> supportColor = new CSgMaterial();
	supportColor->SetDiffuseColor(0.412f, 0.412f, 0.412f, 0.0f);
	supportColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	supportColor->SetShininess(10.f);

	CSgPtr <CSgPartSegment> support = new CSgPartSegment();
	support->SetProperties( 0.2, 0.3, 1., 0., 0.2, 4.0, 1., 0., 0);

	supportColor->AddChild(support);

	parent->AddChild(baseColor);
	parent->AddChild(supportColor);
}

void CYueFactory::Rebound(CSgComposite *parent)
{
	CSgPtr <CSgMesh> lowBoard = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		lowBoard->AddNormal(n[x]);
	}

	GLdouble v[14][4] = {
		{0., 0., 0., 0.},
		{0., 0., 0.4, 0.},
		{3., 0., 0.4, 0.},
		{3., 0., 0., 0.},

		{0., 1., 0., 0.},
		{0., 1., 0.4, 0.},
		{3., 1., 0.4, 0.},
		{3., 1., 0., 0.},

		{1.3, 0., 0., 0.},
		{1.3, 0., 0.4, 0.},
		{1.7, 0., 0.4, 0.},
		{1.7, 0., 0., 0.},

		{1.3, 0.2, 0.4, 0.},
		{1.7, 0.2, 0.4, 0.},
	};

	for ( int x = 0; x < 14; x ++)
	{
		lowBoard->AddVertex(v[x]);
	}

	CSgPtr <CSgHole> hole = new CSgHole(0., 0., 0., 0.4);

	CSgPtr <CSgRotateAroundPoint> holeRot = new CSgRotateAroundPoint();
	holeRot->SetTranslation(1.5, 0., 0.2);
	holeRot->SetNormal(1, 0, 0);
	holeRot->SetAngle(180);
	holeRot->AddChild(hole);

	lowBoard->AddFlatQuad(0, 1, 5, 4, 1);
	lowBoard->AddFlatQuad(2, 3, 7, 6, 0);
	lowBoard->AddFlatQuad(4, 7, 3, 0, 5);

	lowBoard->AddFlatQuad(0, 8, 9, 1, 3);
	lowBoard->AddFlatQuad(11, 3, 2, 10, 3);

	lowBoard->AddFlatQuad(5, 12, 13, 6, 4);
	lowBoard->AddFlatQuad(5, 1, 9, 12, 4);
	lowBoard->AddFlatQuad(6, 13, 10, 2, 4);

	CSgPtr <CSgPartSegment> reboundTopR = new CSgPartSegment();
	reboundTopR->SetProperties( 1.5, 0.0, 1., 0., 1.5, 0.4, 1., 0., 16);
	CSgPtr <CSgPartSegment> reboundTopF = new CSgPartSegment();
	reboundTopF->SetProperties( 0.0, 0.0, 0., -1., 1.5, 0.0, 0., -1., 16);
	CSgPtr <CSgPartSegment> reboundTopB = new CSgPartSegment();
	reboundTopB->SetProperties( 1.5, 0.4, 0., 1., 0.0, 0.4, 0., 1., 16);

	CSgPtr <CSgRotateAroundPoint> rt = new CSgRotateAroundPoint();
	rt->SetTranslation(1.5, 1., 0.);
	rt->SetNormal(1, 0, 0);
	rt->SetAngle(90);
	rt->AddChild(reboundTopR);
	rt->AddChild(reboundTopF);
	rt->AddChild(reboundTopB);

	CSgPtr <CSgMaterial> reboundColor = new CSgMaterial();
	reboundColor->SetDiffuseColor(0.612f, .4f, .122f, 0.0f);
	reboundColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	reboundColor->SetShininess(5.f);

	reboundColor->AddChild(lowBoard);
	reboundColor->AddChild(holeRot);
	reboundColor->AddChild(rt);

	parent->AddChild(reboundColor);
}

void CYueFactory::Rim(CSgComposite *parent)
{
	CSgPtr <CSgPartSegment> reboundTopF = new CSgPartSegment();
	reboundTopF->SetProperties( 1.025, 0.2, 0., 1., 0.925, 0.2, 0., 1., 0);
	CSgPtr <CSgPartSegment> reboundTopR = new CSgPartSegment();
	reboundTopR->SetProperties( 1.025, 0.0, 1., 0., 1.025, 0.2, 1., 0., 2);
	CSgPtr <CSgPartSegment> reboundTopB = new CSgPartSegment();
	reboundTopB->SetProperties( 0.925, 0.0, 0., -1., 1.025, 0.0, 0., -1., 0);
	CSgPtr <CSgPartSegment> reboundTopR2 = new CSgPartSegment();
	reboundTopR2->SetProperties( 0.925, 0.2, -1., 0., 0.925, 0.0, -1., 0., 0);

	CSgPtr <CSgRotateAroundPoint> rt= new CSgRotateAroundPoint();
	rt->SetTranslation(-0.925, 0, 0);
	rt->SetNormal(0, 1, 0);
	rt->SetAngle(11.25);
	rt->AddChild(reboundTopF);
	rt->AddChild(reboundTopR);
	rt->AddChild(reboundTopB);
	rt->AddChild(reboundTopR2);

	CSgPtr <CSgMesh> m_mesh = new CSgMesh();

	GLdouble n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};
	for (int x = 0; x< 6; x++)
	{
		m_mesh->AddNormal(n[x]);
	}

	GLdouble v[8][4] =
	{
		{0., 0., -0.2, 0.},
		{0., 0., 0.2, 0.},
		{0.3, 0., 0.2, 0.},
		{0.3, 0., -0.2, 0.},

		{0., 0.2, -0.2, 0.},
		{0., 0.2, 0.2, 0.},
		{0.3, 0.2, 0.2, 0.},
		{0.3, 0.2, -0.2, 0.},
	};

	for (int x=0; x<8; x++)
	{
		m_mesh->AddVertex(v[x]);
	}

	m_mesh->AddFlatQuad(4, 5, 6, 7, 2);
	m_mesh->AddFlatQuad(3, 2, 1, 0, 3);
	m_mesh->AddFlatQuad(5, 1, 2, 6, 4);
	m_mesh->AddFlatQuad(4, 7, 3, 0, 5);

	CSgPtr <CSgRotateAroundPoint> rt2= new CSgRotateAroundPoint();
	rt2->SetTranslation(-0.3, 0, 0.);
	rt2->SetNormal(0, 1, 0);
	rt2->SetAngle(90);
	rt2->AddChild(rt);
	rt2->AddChild(m_mesh);

	CSgPtr <CSgMaterial> rimColor = new CSgMaterial();
	rimColor->SetDiffuseColor(0.686f, .118f, .176f, 0.0f);
	rimColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	rimColor->SetShininess(5.f);

	rimColor->AddChild(rt2);

	parent->AddChild(rimColor);
	//parent->AddChild(m_mesh);
}

void CYueFactory::Ball(CSgComposite *parent)
{
	CSgPtr <CSgSphere> ball = new CSgSphere();
	ball->setRadius(0.6);
	ball->setRecurse(5);

	CSgPtr <CSgMaterial> ballColor = new CSgMaterial();
	ballColor->SetDiffuseColor(0.737f, .275f, .125f, 0.0f);
	ballColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	ballColor->SetShininess(5.f);

	ballColor->AddChild(ball);

	parent->AddChild(ballColor);
}