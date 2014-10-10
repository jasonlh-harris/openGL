#include "stdafx.h"
#include "WindowFactory.h"
#include "SgComposite.h"
#include "SgPtr.h"
#include "SgSphere.h"
#include "SgTranslate.h"
#include "SgMaterial.h"
#include "SgLatheObject.h"
#include "SgBentPipe.h"
#include "SgRotateAroundPoint.h"
#include "SgRotate.h"
#include "SgPolygon.h"
#include "SgAnimationRotate.h"

const double C_PI = 3.1415926535897932384626433832795;

CWindowFactory::CWindowFactory(void)
{
	//Load the metal texture 
	m_newtonTexture = new CSgTexture(L"textures/metal.bmp");
}


CWindowFactory::~CWindowFactory(void)
{
}

void CWindowFactory::Create(CSgComposite *root)
{
	//Create the window
	CreateWin(root);
	//Create newton cradle
	CreateNewtonCradle(root);
}

//Just creates the window mesh and adds it to root
void CWindowFactory::CreateWin(CSgComposite *root)
{

	CSgPtr <CSgComposite > window = new CSgComposite();
	double dimensions[4] = {2, 2, 0.6, 0};
	CreateDormWindow(window, dimensions, open);

	CSgPtr <CSgComposite > closedWindow = new CSgComposite();
	CreateDormWindow(closedWindow, dimensions, closed);

	CSgPtr <CSgTranslate > windowTrans1 = new CSgTranslate(3.5, 4, 0.55);
	windowTrans1->AddChild(window);//Change this code to open/close the window
	//window is an open window and 
	//closedWindow is a close window

	//Room 2 window
	CSgPtr <CSgTranslate > windowTrans2 = new CSgTranslate(12, 4, 0.55);
	windowTrans2->AddChild(closedWindow);

	//Room 3 window
	CSgPtr <CSgTranslate > windowTrans3 = new CSgTranslate(20.5, 4, 0.55);
	windowTrans3->AddChild(window);
	
	//Room 4 window
	CSgPtr <CSgTranslate > windowTrans4 = new CSgTranslate(29, 4, 0.55);
	windowTrans4->AddChild(window);

	//Room 5 window
	CSgPtr <CSgTranslate > windowTrans5 = new CSgTranslate(37.5, 4, 0.55);
	windowTrans5->AddChild(window);

	root->AddChild(windowTrans1);
	root->AddChild(windowTrans2);
	root->AddChild(windowTrans3);
	root->AddChild(windowTrans4);
	root->AddChild(windowTrans5);
}

//Adds all but the animated part of newtons cradle
void CWindowFactory::CreateNewtonCradle(CSgComposite *root)
{
	CSgPtr <CSgTranslate > newtonsCradle = new CSgTranslate(0, 0, 0);
	CreateNewton(newtonsCradle);
	
	m_newtonTexture->AddChild(newtonsCradle);
	root->AddChild(m_newtonTexture);
}

//Creates a square window frame
//dimension should contain length, height, and width
void CWindowFactory::CreateDormWindow(CSgComposite* parent, CGrVector dimensions, WinState state)
{
	CSgPtr <CSgMaterial> winFrameColor = new CSgMaterial();
	parent->AddChild(winFrameColor);

	CreateWindowFrame(winFrameColor, dimensions);
	double side = dimensions[0] / 12.;

	//Back inner frames
	CSgPtr <CSgTranslate > innerFrameBack = new CSgTranslate(side, side, -dimensions[2]/2);
	double innerDimen[4] = {(dimensions[0]-2*side)/2, dimensions[1]-2*side, dimensions[2]/2,1};
	CreateWindowFrame(innerFrameBack, innerDimen);
	parent->AddChild(innerFrameBack);
	//Uncomment this part to adds winter windows
	//CSgPtr <CSgTranslate > innerFrameBack2 = new CSgTranslate(dimensions[0]/2, side, -dimensions[2]/2);
	//CreateWindowFrame(innerFrameBack2, innerDimenBack);
	//parent->AddChild(innerFrameBack2);

	//Front Inner Frame
	CSgPtr <CSgTranslate > innerFrameFront = new CSgTranslate(dimensions[0]/state, side, 0);
	CreateWindowFrame(innerFrameFront, innerDimen);
	parent->AddChild(innerFrameFront);

}

//Creates a window frame with dimensions(height, length, width)
void CWindowFactory::CreateWindowFrame(CSgComposite* parent, CGrVector dimensions)
{
	double side = dimensions[0] / 12.;
	double xtransform = dimensions[0] - side;
	double ytransform = dimensions[1] - side;

	double n[6][4] = {{1., 0., 0., 1.},{-1., 0., 0., 1.},{0., 1., 0., 1.},
	{0., -1., 0., 1.},{0., 0., 1., 1.},{0., 0., -1., 1.}};

	double v[32][4] = {
	//bot left
	{0, 0, 0, 1}, {side, 0, 0, 1}, {side, side, 0, 1}, {0, side, 0, 1}, 
	{0, 0, -dimensions[2], 1}, {side, 0, -dimensions[2], 1}, {side, side, -dimensions[2], 1}, {0, side, -dimensions[2], 1}, 
	//bot right
	{xtransform, 0, 0, 1}, {dimensions[0], 0, 0, 1}, {dimensions[0], side, 0, 1}, {xtransform, side, 0, 1}, 
	{xtransform, 0, -dimensions[2], 1},	{dimensions[0], 0, -dimensions[2], 1}, {dimensions[0], side, -dimensions[2], 1}, {xtransform, side, -dimensions[2], 1}, 
	//top right
	{xtransform, ytransform, 0, 1}, {dimensions[0], xtransform, 0, 1}, {dimensions[0], dimensions[1], 0, 1}, {xtransform, dimensions[1], 0, 1}, 
	{xtransform, ytransform, -dimensions[2], 1},	{dimensions[0], ytransform, -dimensions[2], 1}, {dimensions[0], dimensions[1], -dimensions[2], 1}, {xtransform, dimensions[1], -dimensions[2], 1}, 
	//top left
	{0, ytransform, 0, 1}, {side, ytransform, 0, 1}, {side, dimensions[1], 0, 1}, {0, dimensions[1], 0, 1}, {0, ytransform, -dimensions[2], 1}, 
	{side, ytransform, -dimensions[2], 1}, {side, dimensions[1], -dimensions[2], 1}, {0, dimensions[1], -dimensions[2], 1}};

	CSgPtr <CSgMesh> windowMesh = new CSgMesh();

	for (int i=0; i<6; i++)
	{
		windowMesh->AddNormal(n[i]);
	}

	for(int i=0; i<32; i++)
		windowMesh->AddVertex(v[i]);

	//Front Quads
	windowMesh->AddFlatQuad(0, 1, 2, 3, 4);
	windowMesh->AddFlatQuad(1, 8, 11, 2, 4);
	windowMesh->AddFlatQuad(8, 9, 10, 11, 4);
	windowMesh->AddFlatQuad(11, 10, 17, 16, 4);
	windowMesh->AddFlatQuad(16, 17, 18, 19, 4);
	windowMesh->AddFlatQuad(16, 19, 26, 25, 4);
	windowMesh->AddFlatQuad(24, 25, 26, 27, 4);
	windowMesh->AddFlatQuad(25, 24, 3, 2, 4);

	//Left outside
	windowMesh->AddFlatQuad(0, 3, 7, 4, 1);
	windowMesh->AddFlatQuad(7, 3, 24, 28, 1);
	windowMesh->AddFlatQuad(28, 24, 27, 31, 1);

	//Bottom outside
	windowMesh->AddFlatQuad(1, 0, 4, 5, 3);
	windowMesh->AddFlatQuad(1, 5, 12, 8, 3);
	windowMesh->AddFlatQuad(8, 12, 13, 9, 3);

	//Right outside
	windowMesh->AddFlatQuad(9, 13, 14, 10, 0);
	windowMesh->AddFlatQuad(10, 14, 21, 17, 0);
	windowMesh->AddFlatQuad(17, 21, 22, 18, 0);

	//Top outside
	windowMesh->AddFlatQuad(19, 18, 22, 23, 2);
	windowMesh->AddFlatQuad(19, 23, 30, 26, 2);
	windowMesh->AddFlatQuad(27, 26, 30, 31, 2);

	//Back
	windowMesh->AddFlatQuad(30, 29, 28, 31, 5);
	windowMesh->AddFlatQuad(28, 29, 6, 7, 5);
	windowMesh->AddFlatQuad(7, 6, 5, 4, 5);
	windowMesh->AddFlatQuad(6, 15, 12, 5, 5);
	windowMesh->AddFlatQuad(15, 14, 13, 12, 5);
	windowMesh->AddFlatQuad(14, 15, 20, 21, 5);
	windowMesh->AddFlatQuad(23, 22, 21, 20, 5);
	windowMesh->AddFlatQuad(23, 20, 29, 30, 5);

	//bottom inside
	windowMesh->AddFlatQuad(2, 11, 15, 6, 2);
	//right inside
	windowMesh->AddFlatQuad(15, 11, 16, 20, 1);
	//top inside
	windowMesh->AddFlatQuad(20, 16, 25, 29, 3);
	//left inside
	windowMesh->AddFlatQuad(29, 25, 2, 6, 0);

	parent->AddChild(windowMesh);
}

//Create Newtons cradle
void CWindowFactory::CreateNewton(CSgComposite* parent)
{
	double height = .4;
	double radius = .1;

	CSgPtr <CSgComposite > newtonCradle = new CSgComposite();
	parent->AddChild(newtonCradle);

	CreateNewtonSide(newtonCradle, height, radius);

	CSgPtr <CSgTranslate > sideTrans = new CSgTranslate(0, 0, height);
	parent->AddChild(sideTrans);
	sideTrans->AddChild(newtonCradle);

}

void CWindowFactory::CreateNewtonNonMove(CSgComposite* parent)
{
	double height = .4;
	double radius = .1;

	CSgPtr <CSgTranslate > newtonBall = new CSgTranslate(radius+.074+(height/7), height+radius+.074, height/2);
	CreateNewtonBall(newtonBall, height*.6, radius/2);
	CSgPtr <CSgTranslate > newtonBall1 = new CSgTranslate(radius*1,0,0);
	parent->AddChild(newtonBall1);
	newtonBall1->AddChild(newtonBall);

	CSgPtr <CSgTranslate > newtonBall2 = new CSgTranslate(radius*2,0,0);
	parent->AddChild(newtonBall2);
	newtonBall2->AddChild(newtonBall);

	CSgPtr <CSgTranslate > newtonBall3 = new CSgTranslate(radius*3,0,0);
	parent->AddChild(newtonBall3);
	newtonBall3->AddChild(newtonBall);

}

void CWindowFactory::CreateNewtonRotate(CSgComposite* parent)
{
	double height = .4;
	double radius = .1;
	
	CSgPtr <CSgTranslate > newtonBall = new CSgTranslate(radius+.074+(height/7), height+radius+.074, height/2);
	parent->AddChild(newtonBall);
	CreateNewtonBall(newtonBall, height*.6, radius/2);

	//CSgPtr <CSgTranslate > newtonBall4 = new CSgTranslate(radius*4,0,0);
	//parent->AddChild(newtonBall4);
	//newtonBall4->AddChild(newtonBall);
}

//Creates one side of newtons cradle
//dimensions is total length, height, width
void CWindowFactory::CreateNewtonSide(CSgComposite* parent, double height, double radius)
{
	CSgPtr <CSgComposite > sideFirstHalf = new CSgComposite();
	parent->AddChild(sideFirstHalf);
	/*CreateNewtonPole(sideFirstHalf, height, radius, true);*/
	CSgPtr <CSgTranslate > curveTrans = new CSgTranslate(0, height, 0);
	CSgPtr <CSgRotate > curveRotate = new CSgRotate(180, 1, 1, 0);
	curveTrans->AddChild(curveRotate);
	sideFirstHalf->AddChild(curveTrans);
	CreateNewtonCurve(curveTrans, height, radius);

	CSgPtr <CSgTranslate > sideTrans = new CSgTranslate(2*height+.074, 0, 0);
	CSgPtr <CSgRotate > sideRotate = new CSgRotate(180, 0, 1, 0);
	sideTrans->AddChild(sideRotate);
	sideTrans->AddChild(sideFirstHalf);
	parent->AddChild(sideTrans);
}

//Creates the bent pipe that forms the frame
//radius of the inner circle (cross section)
void CWindowFactory::CreateNewtonCurve(CSgComposite* parent, double height, double radius)
{
	CSgPtr <CSgBentPipe > bendy = new CSgBentPipe();
	CSgPtr <CSgMesh > bendMesh = new CSgMesh();

    bendy->SetLength(height*2);
    bendy->SetDiameter(2*radius);
    bendy->SetStepsLength(40);
    bendy->SetStepsAround(20);

    // 
    // A smooth 90 degree bend
    //
    bendy->SetMesh(bendMesh);
    bendy->Create();

    // We will rotate in 10 slices
    int numSlices = 10;

    CGrTransform rot = CGrTransform::GetRotateZ(90.0 / numSlices);

    for(int i=0;  i<numSlices;  i++)
    {
        bendy->TransformAt(40 / 2 - numSlices / 2 + i, rot);
    }

	parent->AddChild(bendy);

}

//Creates the poles that hold the spheres
void CWindowFactory::CreateNewtonPole(CSgComposite* parent, double height, double radius, bool bottom)
{
	CSgPtr <CSgLatheObject> newtonPole = new CSgLatheObject();

	newtonPole->AddSegment(radius, 0,	// First point x,y (z is zero)
        1., 0.,								// First point normal x,y (z is zero)
        radius, height,				// Second point x,y
        1., 0.,							// Second point normal x,y
		0., 1.);					//Text coords

	if(bottom)
	{
		newtonPole->AddSegment(0, 0,           // First point x,y (z is zero)
			0., -1.,                // First point normal x,y (z is zero)
			radius, 0,                  // Second point x,y
			0., -1.);   // Second point normal x,y
	}
	//Add the pole to its parent
	parent->AddChild(newtonPole);
}

//Create the sphere and the poles holding it
void CWindowFactory::CreateNewtonBall(CSgComposite* parent, double height, double radius)
{
	CSgPtr <CSgMaterial> ballColor = new CSgMaterial();
	ballColor->SetDiffuseColor(0.1f, 0.1f, 0.1f, 1.0f);
	ballColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	ballColor->SetShininess(5.f);
	parent->AddChild(ballColor);

	CSgPtr <CSgComposite > firstPole = new CSgComposite();
	ballColor->AddChild(firstPole);
	CSgPtr <CSgRotate > poleAngle = new CSgRotate(35, 1, 0, 0);
	firstPole->AddChild(poleAngle);
	CreateNewtonPole(firstPole, height, .01, false);

	CSgPtr <CSgTranslate > poleTrans = new CSgTranslate(0, 0, 0);
	CSgPtr <CSgRotate > poleRotate = new CSgRotate(180, 0, 1, 0);
	poleTrans->AddChild(poleRotate);
	poleTrans->AddChild(firstPole);
	ballColor->AddChild(poleTrans);

	CSgPtr <CSgTranslate > sphereTrans = new CSgTranslate(0, 0, 0);
	CSgPtr <CSgSphere > sphere = new CSgSphere();
	sphere->setRadius(radius);
	ballColor->AddChild(sphereTrans);
	sphereTrans->AddChild(sphere);
}