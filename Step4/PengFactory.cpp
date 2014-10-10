#include "stdafx.h"
#include "PengFactory.h"
#include "SgPolygon.h"
#include "SgComposite.h"
#include "graphics\GrVector.h"
#include "SgPtr.h"
#include "SgTranslate.h"
#include "SgMaterial.h"
#include "SgRotateAroundPoint.h"
#include "SgMesh.h"
#include "SgCylinder.h"
#include "AnimationPengCar.h"

const double PI = 3.1415926535897932384626433832795;

CPengFactory::CPengFactory(void)
{
	carBodyText = new CSgTexture(L"textures/carBody.bmp");
	tireMiddleText = new CSgTexture(L"textures/middleTire.bmp");
	rimText = new CSgTexture(L"textures/carRim.bmp");
	fireText = new CSgTexture(L"textures/fire.bmp");
	deskFrontText = new CSgTexture(L"textures/drawer.bmp");
	posterText = new CSgTexture(L"textures/mao.bmp");
}


CPengFactory::~CPengFactory(void)
{
}

void CPengFactory::Create(CSgComposite *root)
{

	

	/* Create Desk*/
	CSgPtr <CSgComposite > desk = new CSgComposite();
	root->AddChild(desk);
	CreateDesk(desk, 0);

	/* Creat Car*/
	CSgPtr <CSgComposite> car = new CSgComposite();
	CreateCar(car);
	root->AddChild(car);
	
	/* Creat Poster*/
	CSgPtr <CSgComposite> poster = new CSgComposite();
	root->AddChild(poster);
	CreatePoster(poster);

}



void CPengFactory::CreateDesk(CSgComposite *parent, double deskOpen)
{
	if (deskOpen > 1)
		deskOpen = 0;


	CSgPtr <CSgMaterial> woodColor = new CSgMaterial();
	woodColor->SetDiffuseColor(0.398f, 0.199f, 0.f, 1.0f);
	woodColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	woodColor->SetShininess(5.f);

	CSgPtr <CSgMesh> leg = new CSgMesh();
	woodColor->AddChild(leg);

	GLdouble p[20][3]=
	{{0., 0., 0.},{0., 2, 0.},{.1, 2, 0.},{.1, 0., 0.},{.1, 0., 2},{.1, 2, 2},{0., 2, 2},{0., 0., 2},
	{0,2.1,2},{0,2.1,0}, {3,2.1,0}, {3,2.1,2}, {3,2,2}, {3,2,0}, {2.9,2,0}, {2.9,2,2},
	{2.9,0,2}, {3,0,2}, {3,0,0}, {2.9,0,0}};

	for (int n = 0; n < 20; n++)
	{
		leg->AddVertex(p[n]);
		
	}

	leg->AddNormal(CGrVector(0,0,1));	//0
	leg->AddNormal(CGrVector(0,0,-1));	//1
	leg->AddNormal(CGrVector(-1,0,0));	//2
	leg->AddNormal(CGrVector(1,0,0));	//3
	leg->AddNormal(CGrVector(0,1,0));	//4
	leg->AddNormal(CGrVector(0,-1,0));	//5

	leg->AddFlatQuad(1,2,3,0,1);
	leg->AddFlatQuad(5,6,7,4,0);
	leg->AddFlatQuad(6,1,0,7,2);
	leg->AddFlatQuad(2,5,4,3,3);
	
	leg->AddFlatQuad(9,8,11,10,4);		//board top
	leg->AddFlatQuad(8,6,12,11,0);		//board front
	leg->AddFlatQuad(1,9,10,13,1);	    //board back
	leg->AddFlatQuad(9,1,6,8,2);		//board left
	leg->AddFlatQuad(10,11,12,13,3);    //board right
	leg->AddFlatQuad(2,14,15,5,5);		//board bottom

	leg->AddFlatQuad(15,16,17,12,0);    //leg front
	leg->AddFlatQuad(15,14,19,16,2);	//leg left
	leg->AddFlatQuad(11,17,18,10,3);	//leg right
	leg->AddFlatQuad(14,13,18,19,1);	//leg back


	CSgPtr <CSgTranslate> deskTrans = new CSgTranslate(17.75, 1.0, 1.0);
	deskTrans->AddChild(woodColor);

	

	CSgPtr <CSgMaterial> drawerColor = new CSgMaterial();
	drawerColor->SetDiffuseColor(1.f, 1.f, 1.f, 1.0f);
	drawerColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	drawerColor->SetShininess(1.f);

	CSgPtr <CSgMesh> drawer = new CSgMesh();
	drawerColor->AddChild(drawer);

	CSgPtr <CSgMesh> deskFrontT = new CSgMesh();
	deskFrontText->AddChild(deskFrontT);
	drawerColor->AddChild(deskFrontText);

	GLdouble d[16][3]=
	{{0., 0., 0.},{0., 0.4, 0.},{2.8, 0.4, 0.},{2.8, 0, 0.},{2.8, 0., 2},{2.8, 0.4, 2},{0., 0.4, 2},{0., 0., 2},
	{0.01, 0, 0.01}, {0.01, 0.4, 0.01}, {2.799, 0.4, 0.01}, {2.799, 0, 0.01}, {2.799, 0, 1.99}, {2.799, 0.4, 1.99}, {0.01, 0.4, 1.99}, {0.01, 0, 1.99}};

		for (int n = 0; n < 16; n++)
	{
		drawer->AddVertex(d[n]);
		
	}
	
	// deskFront with texture
	deskFrontT->AddVertex(d[5]);
	deskFrontT->AddVertex(d[6]);
	deskFrontT->AddVertex(d[7]);
	deskFrontT->AddVertex(d[4]);

	deskFrontT->AddNormal(CGrVector(0,0,1));

	deskFrontT->AddTexCoord(CGrVector(0, 1));
	deskFrontT->AddTexCoord(CGrVector(0, 0));
	deskFrontT->AddTexCoord(CGrVector(1, 0));
	deskFrontT->AddTexCoord(CGrVector(1, 1));

	deskFrontT->AddTriangleVertex(1,0,0);
	deskFrontT->AddTriangleVertex(2,0,1);
	deskFrontT->AddTriangleVertex(3,0,2);
	deskFrontT->AddTriangleVertex(1,0,0);
	deskFrontT->AddTriangleVertex(3,0,2);
	deskFrontT->AddTriangleVertex(0,0,3);

	drawer->AddNormal(CGrVector(0,0,1));	//0
	drawer->AddNormal(CGrVector(0,0,-1));	//1
	drawer->AddNormal(CGrVector(-1,0,0));	//2
	drawer->AddNormal(CGrVector(1,0,0));	//3
	drawer->AddNormal(CGrVector(0,1,0));	//4
	drawer->AddNormal(CGrVector(0,-1,0));	//5

	//drawer outside
	drawer->AddFlatQuad(1,2,3,0,1);
	//drawer->AddFlatQuad(5,6,7,4,0);
	drawer->AddFlatQuad(6,1,0,7,3);
	drawer->AddFlatQuad(2,5,4,3,2);	
	drawer->AddFlatQuad(0,3,4,7,5);

	//drawer inside 
	drawer->AddFlatQuad(10,9,8,11,0);
	drawer->AddFlatQuad(14,12,12,15,1);
	drawer->AddFlatQuad(13,10,11,12,2);
	drawer->AddFlatQuad(9,14,15,8,3);	
	drawer->AddFlatQuad(8,15,12,11,4);

	//connect inside and outside 
	drawer->AddFlatQuad(2,10,13,5,4);
	drawer->AddFlatQuad(2,1,9,10,4);
	drawer->AddFlatQuad(1,6,14,9,4);
	drawer->AddFlatQuad(14,6,5,13,4);

	CSgPtr <CSgTranslate> drawerTrans = new CSgTranslate (0.1,1.6,deskOpen);
	drawerTrans->AddChild(drawerColor);

	deskTrans->AddChild(drawerTrans);
	parent->AddChild(deskTrans);
	//parent->AddChild(drawerTrans);
}

void CPengFactory::CreateCar(CSgComposite *parent)
{
	
	


	/* Creating Car Tires*/
	//The whole tire 
	CSgPtr <CSgRotateAroundPoint> FrontViewTire = new CSgRotateAroundPoint();
	FrontViewTire->SetAngle(90);
	FrontViewTire->SetPoint(0., 0., 0.);
	FrontViewTire->SetNormal(1, 0, 0);

	//inner and outter side parts of the tire
	CSgPtr <CSgMesh> tire = new CSgMesh();

	// middle part of the tire
	CSgPtr <CSgMesh> tireMiddle = new CSgMesh();
	tireMiddleText->AddChild(tireMiddle);
	
	//assign material to tire
	CSgPtr <CSgMaterial> tireColor = new CSgMaterial();
	tireColor->SetDiffuseColor(0.25f, 0.25f, 0.25f, 1.0f);
	tireColor->SetSpecularColor(0.0f, 0.0f, 0.0f, 1.f);
	tireColor->SetShininess(5.f);
	tireColor->AddChild(tire);
	
	double inX1=0, inX2=0, 
		   inY1=0, inY2=0, 
		   outX1=0, outX2=0,
		   outY1=0, outY2=0;

	for (int i=0; i<50; i++)
	{
		//1->0,1, 0.4->0.04
		outX1 =  0 +0.1 * sin((2*PI/50)*i); 
		outY1 = 0 + 0.1 * cos((2*PI/50)*i);
		outX2 =  0 + 0.1* sin((2*PI/50)*(i+1)); 
		outY2 = 0 + 0.1 * cos((2*PI/50)*(i+1));
		inX1= 0 + 0.04 * sin((2*PI/50)*i);  
		inY1= 0 + 0.04 * cos((2*PI/50)*i); 
		inX2= 0 + 0.04 * sin((2*PI/50)*(i+1));
		inY2= 0 + 0.04 * cos((2*PI/50)*(i+1));

		//Outer side
		//1->0.1
		tire->AddNormal(CGrVector(0, -1, 0));
	    tire->AddVertex(CGrVector(outX1, 0.1, outY1));
		tire->AddVertex(CGrVector(outX2, 0.1, outY2));
		tire->AddVertex(CGrVector(inX2, 0.1, inY2));
		tire->AddVertex(CGrVector(inX1, 0.1, inY1));

		//Inner side
		tire->AddNormal(CGrVector(0, 1, 0));
		tire->AddVertex(CGrVector(inX1, 0, inY1));
		tire->AddVertex(CGrVector(inX2, 0, inY2));
		tire->AddVertex(CGrVector(outX2, 0, outY2));
		tire->AddVertex(CGrVector(outX1, 0, outY1));
	
		tireMiddle->AddNormal(CGrVector(outX1, 0, outY1));
		//First half of triangle
		//1->0.1
		tireMiddle->AddVertex(CGrVector(outX1, 0.1, outY1));
		tireMiddle->AddTexCoord(CGrVector(0,1));
		tireMiddle->AddVertex(CGrVector(outX1, 0, outY1));
		tireMiddle->AddTexCoord(CGrVector(0,0));
		tireMiddle->AddVertex(CGrVector(outX2, 0, outY2));
		tireMiddle->AddTexCoord(CGrVector(1,0));
		//Second half of triangle
		tireMiddle->AddVertex(CGrVector(outX2, 0, outY2));
		tireMiddle->AddTexCoord(CGrVector(1,0));
		tireMiddle->AddVertex(CGrVector(outX2, 0.1, outY2));
		tireMiddle->AddTexCoord(CGrVector(1,1));
		tireMiddle->AddVertex(CGrVector(outX1, 0.1, outY1));
		tireMiddle->AddTexCoord(CGrVector(0,1));
	}

	for (int i=0; i<400; i+=4)
	{
		tire->AddFlatQuad(i, i+1, i+2, i+3, i/4);
	}

	for(int i=0;i<300; i+=6)
	{
		tireMiddle->AddTriangleVertex(i,i/6,i);
		tireMiddle->AddTriangleVertex(i+1,i/6,i+1);
		tireMiddle->AddTriangleVertex(i+2,i/6,i+2);
		tireMiddle->AddTriangleVertex(i+3,i/6,i+3);
		tireMiddle->AddTriangleVertex(i+4,i/6,i+4);
		tireMiddle->AddTriangleVertex(i+5,i/6,i+5);
	}

	CSgPtr <CSgPolygon> rimFront = new CSgPolygon();
	CSgPtr <CSgPolygon> rimBack = new CSgPolygon();
	rimText->AddChild(rimFront);
	rimText->AddChild(rimBack);
	tireColor->AddChild(rimText);

	rimFront->AddNormal(CGrVector(0,1,0));
	rimFront->AddVertex3d(0.07,-0.001,-0.07);
	rimFront->AddTexCoord(CGrVector(1,0));
	rimFront->AddVertex3d(0.07,-0.001,0.07);
	rimFront->AddTexCoord(CGrVector(1,1));
	rimFront->AddVertex3d(-0.07,-0.001,0.07);
	rimFront->AddTexCoord(CGrVector(0,1));
	rimFront->AddVertex3d(-0.07,-0.01,-0.07);
	rimFront->AddTexCoord(CGrVector(0,0));

	rimBack->AddNormal(CGrVector(0,-1,0));
	rimBack->AddVertex3d(-0.07,0.101,-0.07);
	rimBack->AddTexCoord(CGrVector(0,0));
	rimBack->AddVertex3d(-0.07,0.101,0.07);
	rimBack->AddTexCoord(CGrVector(0,1));
	rimBack->AddVertex3d(0.07,0.101,0.07);
	rimBack->AddTexCoord(CGrVector(1,1));
	rimBack->AddVertex3d(0.07,0.101,-0.07);
	rimBack->AddTexCoord(CGrVector(1,0));

	FrontViewTire->AddChild(tireColor);
	FrontViewTire->AddChild(tireMiddleText);

	/* Making pipe connecting tires */

	CSgPtr <CSgCylinder> cylinder = new CSgCylinder();
	//cylinder->SetProperties(20,5,0.1);  //5->0.5, 0.1->0.01
		
	cylinder->SetProperties(0.5,0.01);  //5->0.5, 0.1->0.01

	//setup cylinder material
	CSgPtr <CSgMaterial> cylinderColor = new CSgMaterial();
	cylinderColor->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	cylinderColor->SetSpecularColor(0.0f, 0.0f, 0.0f, 1.0f);
	cylinderColor->AddChild(cylinder);

	CSgPtr <CSgRotateAroundPoint> rotateCylinderX = new CSgRotateAroundPoint();
	rotateCylinderX->SetAngle(90);
	rotateCylinderX->SetPoint(0., 0., 0.);
	rotateCylinderX->SetNormal(1, 0, 0);
	rotateCylinderX->AddChild(cylinderColor);

	//translate to car front to connect front tires
	CSgPtr<CSgTranslate> CylinderTransToFront = new CSgTranslate(0.52, 0, 0);
	CylinderTransToFront->AddChild(rotateCylinderX);


	CSgPtr <CSgRotateAroundPoint> rotateCylinderZ = new CSgRotateAroundPoint();
	rotateCylinderZ->SetAngle(90);
	rotateCylinderZ->SetPoint(0., 0., 0.);
	rotateCylinderZ->SetNormal(0, 0, -1);
	rotateCylinderZ->AddChild(cylinderColor);

	CSgPtr<CSgTranslate> cylinderTransH = new CSgTranslate(0.01, 0, 0.25);
	cylinderTransH->AddChild(rotateCylinderZ);

	//connecting the car
	CSgPtr<CSgTranslate> tireBackRight = new CSgTranslate(0.52, 0, 0);
	tireBackRight->AddChild(FrontViewTire);
	CSgPtr<CSgTranslate> tireFrontLeft = new CSgTranslate(0, 0, 0.4);
	tireFrontLeft->AddChild(FrontViewTire);
	CSgPtr<CSgTranslate> tireFrontRight = new CSgTranslate(0.52, 0, 0.4);
	tireFrontRight->AddChild(FrontViewTire);

	/* Making Car body */
	
	CSgPtr <CSgMaterial> bodyColor = new CSgMaterial();
	bodyColor->SetDiffuseColor(0.625f,0.625f,0.625f, 1.0f );
	bodyColor->SetSpecularColor(0.0f,0.0f,0.0f, 1.0f);

	CSgPtr <CSgMesh> CarBody = new CSgMesh();
	CSgPtr <CSgMesh> CarBodyT = new CSgMesh();
	CSgPtr <CSgMesh> CarWindow = new CSgMesh();
	carBodyText->AddChild(CarWindow);
	fireText->AddChild(CarBodyT);
	bodyColor->AddChild(CarBody);
	bodyColor->AddChild(fireText);
	bodyColor->AddChild(carBodyText);

		GLdouble v[16][3]=
	{
	{0., 0., 0.},{0., 0.1, 0.},{0.15, 0.1, 0.},{0.15, 0., 0.},
	{0.15, 0., 0.15},{0.15, 0.1, 0.15},{0., 0.1, 0.15},{0., 0., 0.15},
	{0.6,0.1,0},{0.6,0,0},{0.6,0,0.15},{0.6,0.1,0.15},
	{0.15,0.2,0},{0.35,0.2,0},{0.35,0.2,0.15},{0.15,0.2,0.15}};
	
	double a[4][2] = {{0., 0.},{1, 0.},{1, 1},{0., 1}};
	
	for (int i = 0; i<16; i++)
	{
		CarBody->AddVertex(v[i]);
		CarBodyT->AddVertex(v[i]);
		CarWindow->AddVertex(v[i]);
		
	}
	for (int i = 0; i<4; i++)
	{
		CarBody->AddTexCoord(a[i]);
		CarBodyT->AddTexCoord(a[i]);
		CarWindow->AddTexCoord(a[i]);
	}
	
	CarBody->AddNormal(CGrVector(0,0,1));
	CarBody->AddNormal(CGrVector(0,0,-1));
	CarBody->AddNormal(CGrVector(-1,0,0));
	CarBody->AddNormal(CGrVector(1,0,0));
	CarBody->AddNormal(CGrVector(0,-1,0));
	CarBody->AddNormal(CGrVector(0,1,0));

	CarBody->AddFlatQuad(1,2,3,0,1);
	CarBody->AddFlatQuad(5,6,7,4,0);
	CarBody->AddFlatQuad(6,1,0,7,2);
	CarBody->AddFlatQuad(0,3,4,7,4);

	CarBody->AddFlatQuad(3,9,10,4,4);
	CarBody->AddFlatQuad(8,11,10,9,3);
	CarBody->AddFlatQuad(2,8,9,3,1);
	CarBody->AddFlatQuad(5,4,10,11,0);

	/* Car window*/

	//top
	CarWindow->AddNormal(CGrVector(0,1,0));
	CarWindow->AddTriangleVertex(12,0,3);
	CarWindow->AddTriangleVertex(15,0,0);
	CarWindow->AddTriangleVertex(14,0,1);
	
	CarWindow->AddTriangleVertex(12,0,3);
	CarWindow->AddTriangleVertex(14,0,1);
	CarWindow->AddTriangleVertex(13,0,2);

	//front
	CarWindow->AddNormal(CGrVector(0,0,1));
	CarWindow->AddTriangleVertex(15,1,3);
	CarWindow->AddTriangleVertex(5,1,0);
	CarWindow->AddTriangleVertex(11,1,1);
	
	CarWindow->AddTriangleVertex(15,1,3);
	CarWindow->AddTriangleVertex(11,1,1);
	CarWindow->AddTriangleVertex(14,1,2);

	//back
	CarWindow->AddNormal(CGrVector(0,0,-1));
	CarWindow->AddTriangleVertex(12,2,3);
	CarWindow->AddTriangleVertex(13,2,0);
	CarWindow->AddTriangleVertex(8,2,1);
	
	CarWindow->AddTriangleVertex(12,2,3);
	CarWindow->AddTriangleVertex(8,2,1);
	CarWindow->AddTriangleVertex(2,2,2);

	//left
	CarWindow->AddNormal(CGrVector(-1,0,0));
	CarWindow->AddTriangleVertex(15,3,3);
	CarWindow->AddTriangleVertex(12,3,0);
	CarWindow->AddTriangleVertex(2,3,1);
	
	CarWindow->AddTriangleVertex(15,3,3);
	CarWindow->AddTriangleVertex(2,3,1);
	CarWindow->AddTriangleVertex(5,3,2);

	//right 
	double *n=Normal3dv(v[14],v[15],v[9]);
	CarWindow->AddNormal(CGrVector(CGrVector(n[0],n[1],n[2],1)));
	CarWindow->AddTriangleVertex(13,4,3);
	CarWindow->AddTriangleVertex(14,4,0);
	CarWindow->AddTriangleVertex(11,4,1);
	
	CarWindow->AddTriangleVertex(13,4,3);
	CarWindow->AddTriangleVertex(11,4,1);
	CarWindow->AddTriangleVertex(8,4,2);
	delete []n;

	/* Top of body with texture*/
	CarBodyT->AddNormal(CGrVector(0,1,0));
	CarBodyT->AddTriangleVertex(1,0,3);
	CarBodyT->AddTriangleVertex(6,0,0);
	CarBodyT->AddTriangleVertex(5,0,1);
	
	CarBodyT->AddTriangleVertex(1,0,3);
	CarBodyT->AddTriangleVertex(5,0,1);
	CarBodyT->AddTriangleVertex(2,0,2);

	CSgPtr <CSgTranslate> carBodyTrans = new CSgTranslate(-0.02,0,0.175);
	carBodyTrans->AddChild(bodyColor);
	
	CSgPtr <CSgTranslate> carTransToMyDorm = new CSgTranslate(18,3.2,1.5);
	carTransToMyDorm->AddChild(carBodyTrans);
	carTransToMyDorm->AddChild(FrontViewTire);
	carTransToMyDorm->AddChild(rotateCylinderX);
	carTransToMyDorm->AddChild(tireBackRight);
	carTransToMyDorm->AddChild(cylinderTransH);
	carTransToMyDorm->AddChild(tireFrontLeft);
	carTransToMyDorm->AddChild(CylinderTransToFront);
	carTransToMyDorm->AddChild(tireFrontRight);

	parent->AddChild(carTransToMyDorm);



	

	//parent->AddChild(carBodyTrans);


	//parent->AddChild(FrontViewTire);
	//parent->AddChild(rotateCylinderX);
	//parent->AddChild(tireBackRight);

	//parent->AddChild(cylinderTransH);
	//
	//parent->AddChild(tireFrontLeft);
	//parent->AddChild(CylinderTransToFront);
	//parent->AddChild(tireFrontRight);
}

void CPengFactory::CreatePoster(CSgComposite *parent)
{
	CSgPtr <CSgMaterial> posterColor = new CSgMaterial();
	posterColor->SetDiffuseColor( 0.996f, 0.695f, 0.398f, 1.0f);
	posterColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	posterColor->SetShininess(5.f);

	CSgPtr <CSgMaterial> posterImageColor = new CSgMaterial();
	posterImageColor->SetDiffuseColor(0.875f, 0.875f, 0.875f, 1.0f);
	posterImageColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	posterImageColor->SetShininess(5.f);

	CSgPtr <CSgMesh> posterMiddle= new CSgMesh();
	posterText->AddChild(posterMiddle);
	posterImageColor->AddChild(posterText);

	CSgPtr <CSgMesh> poster = new CSgMesh();
	posterColor->AddChild(poster);

	GLdouble p[16][3]=
	{{0., 0., 0.},{0., 0.1, 0.},{5, 0.1, 0.},{5, 0, 0.},{5, 0., 4.5},{5, 0.1, 4.5},{0., 0.1, 4.5},{0., 0., 4.5},
	{0.1, 0, 0.1}, {0.1, 0.1, 0.1}, {4.9, 0.1, 0.1}, {4.9, 0, 0.1}, {4.9, 0, 4.4}, {4.9, 0.1, 4.4}, {0.1, 0.1, 4.4}, {0.1, 0, 4.4}};

		for (int n = 0; n < 16; n++)
	{
		poster->AddVertex(p[n]);
		
	}

	poster->AddNormal(CGrVector(0,0,1));	//0
	poster->AddNormal(CGrVector(0,0,-1));	//1
	poster->AddNormal(CGrVector(-1,0,0));	//2
	poster->AddNormal(CGrVector(1,0,0));	//3
	poster->AddNormal(CGrVector(0,1,0));	//4
	poster->AddNormal(CGrVector(0,-1,0));	//5

	//poster frame outside 
	poster->AddFlatQuad(1,2,3,0,1);
	poster->AddFlatQuad(5,6,7,4,0);
	poster->AddFlatQuad(6,1,0,7,2);
	poster->AddFlatQuad(2,5,4,3,3);


	//poster frame inside 
	poster->AddFlatQuad(10,9,8,11,0);
	poster->AddFlatQuad(14,13,12,15,1);
	poster->AddFlatQuad(13,10,11,12,2);
	poster->AddFlatQuad(9,14,15,8,3);	

	//connect inside and outside 
	poster->AddFlatQuad(2,10,13,5,4);
	poster->AddFlatQuad(2,1,9,10,4);
	poster->AddFlatQuad(1,6,14,9,4);
	poster->AddFlatQuad(14,6,5,13,4);

	//poster image

	GLdouble d[4][3] = {
	{0.1, 0.05, 0.1},{0.1, 0.05, 4.4},{4.9,0.05,4.4},{4.9, 0.05, 0.1}};
	
	for (int n = 0; n < 4; n++)
	{
		posterMiddle->AddVertex(d[n]);
		
	}

	posterMiddle->AddNormal(CGrVector(0,1,0));
	posterMiddle->AddTexCoord(CGrVector(0, 1));
	posterMiddle->AddTexCoord(CGrVector(0, 0));
	posterMiddle->AddTexCoord(CGrVector(1, 0));
	posterMiddle->AddTexCoord(CGrVector(1, 1));

	posterMiddle->AddTriangleVertex(0,0,0);
	posterMiddle->AddTriangleVertex(1,0,1);
	posterMiddle->AddTriangleVertex(2,0,2);
	posterMiddle->AddTriangleVertex(0,0,0);
	posterMiddle->AddTriangleVertex(2,0,2);
	posterMiddle->AddTriangleVertex(3,0,3);

	CSgPtr <CSgRotateAroundPoint> posterRotate = new CSgRotateAroundPoint();
	posterRotate->SetAngle(90);
	posterRotate->SetPoint(0,0,0);
	posterRotate->SetNormal(1,0,0);
	posterRotate->AddChild(posterColor);
	posterRotate->AddChild(posterImageColor);

	CSgPtr <CSgRotateAroundPoint> posterRotate1 = new CSgRotateAroundPoint();
	posterRotate1->SetAngle(90);
	posterRotate1->SetPoint(0,0,0);
	posterRotate1->SetNormal(0,1,0);
	posterRotate1->AddChild(posterRotate);

	CSgPtr <CSgTranslate> posterTrans = new CSgTranslate(17.5, 7.0, 8.5);
	posterTrans->AddChild(posterRotate1);


	parent->AddChild(posterTrans);
}

double *CPengFactory::Normal3dv( const double *a,const double *b, const double *c)
{
	double l1[] = {b[0]-a[0], b[1]-a[1], b[2]-a[2]}; 
	double l2[] = {c[0]-a[0], c[1]-a[1], c[2]-a[2]};
	                                          //CrossProduct
	double v[]  = {l1[1]*l2[2]- l2[1]*l1[2],  //x
		           l1[2]*l2[0]-l2[2]*l2[0],   //y
				   l1[0]*l2[1]-l2[0]*l1[1]};  //z

    double tmp= sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	double *n = new double [3];
	n[0] = v[0]/tmp;
	n[1] = v[1]/tmp;
	n[2] = v[2]/tmp;
	return n;

}