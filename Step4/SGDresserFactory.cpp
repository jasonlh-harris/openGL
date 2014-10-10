#include "stdafx.h"
#include "SGDresserFactory.h"
#include "SgTranslate.h"
#include "SgMaterial.h"

CSGDresserFactory::CSGDresserFactory(void)
{
	//Actual dresser messurements in meters
	height = .86 ;
	width = .8;
	depth = .45 ;
	drawerWidth = .67;
	drawerHeight = .21;
	drawerNum = 3;
	
	spacing = (height - (drawerHeight * drawerNum)) / (drawerNum + 1);
	spacingx = (width - drawerWidth) *.5;
	isDifferent = false;
	drawerThickness = 0.01905;
	
	//how many verticies one column of points have
	vertexNum = 8;
}


CSGDresserFactory::~CSGDresserFactory(void)
{
}
CSgObject* CSGDresserFactory::Create(void)
{
	CSgPtr<CSgComposite> comp = new CSgComposite();

	Create(comp);

	return comp;
}
void CSGDresserFactory::Create(CSgComposite *parent)
{
	CSgPtr <CSgMaterial> woodColor = new CSgMaterial();
	woodColor->SetDiffuseColor(0.89f, 0.67f, 0.45f, 1.0f);
	woodColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	woodColor->SetShininess(5.f);
	CSgPtr <CSgMesh > dresser = new CSgMesh();
	
	//messurements of dresser in meters

	
	//number of front verticies
	int frontside = 0;
	for(int i = 0; i < 4; i++)
	{
		double x = 0;
		switch (i){
		case 3:
			x = width; 
			break;
		case 2:
			x = drawerWidth + spacingx;
			break;
		case 1:
			x = spacingx;
			break;
		default:
			break;
		}
		dresser->AddVertex(CGrVector(x,0,0,1));
		dresser->AddVertex(CGrVector(x,spacing,0,1));
		dresser->AddVertex(CGrVector(x,spacing + drawerHeight,0,1));
		dresser->AddVertex(CGrVector(x,2*spacing + drawerHeight,0,1));
		dresser->AddVertex(CGrVector(x,2*spacing + 2*drawerHeight,0,1));
		dresser->AddVertex(CGrVector(x,3*spacing + 2*drawerHeight,0,1));
		dresser->AddVertex(CGrVector(x,3*spacing + 3*drawerHeight,0,1));
		dresser->AddVertex(CGrVector(x,height,0,1));
		frontside += 8;
	}
	dresser->AddNormal(CGrVector(0.,0.,1.,0.));
	//leftfront
	for(int j = 0; j < vertexNum -1;j++)
	{
		dresser->AddTriangleVertex(j,0,-1);
		dresser->AddTriangleVertex(j + vertexNum,0,-1);
		dresser->AddTriangleVertex(j + 1,0,-1);

		
		dresser->AddTriangleVertex(j + vertexNum,0,-1);
		dresser->AddTriangleVertex(j + vertexNum +1,0,-1);
		dresser->AddTriangleVertex(j + 1,0,-1);
	}
	//rightfront
	for(int j = 2* vertexNum; j < 3*vertexNum -1 ;j++)
	{
		dresser->AddTriangleVertex(j,0,-1);
		dresser->AddTriangleVertex(j + vertexNum,0,-1);
		dresser->AddTriangleVertex(j + 1,0,-1);

		
		dresser->AddTriangleVertex(j + vertexNum,0,-1);
		dresser->AddTriangleVertex(j + vertexNum +1,0,-1);
		dresser->AddTriangleVertex(j + 1,0,-1);
	}
	//crossbeams
	for(int j = 0;j <=6; j +=2)
	{
		dresser->AddTriangleVertex(j + vertexNum +1,0,-1);
		dresser->AddTriangleVertex(j + vertexNum,0,-1);
		dresser->AddTriangleVertex(j + vertexNum * 2,0,-1);

		dresser->AddTriangleVertex(j + vertexNum +1,0,-1);
		dresser->AddTriangleVertex(j + vertexNum * 2,0,-1);
		dresser->AddTriangleVertex(j + vertexNum *2 +1,0,-1);
	}

	//other corners

	dresser->AddVertex(CGrVector(0,0,-depth,1));
	dresser->AddVertex(CGrVector(0,height,-depth,1));

	dresser->AddVertex(CGrVector(width,0,-depth,1));
	dresser->AddVertex(CGrVector(width,height,-depth,1));

	//leftside
	dresser->AddNormal(CGrVector(-1.,0.,0.,0.));


	dresser->AddTriangleVertex(0,1,-1);
	dresser->AddTriangleVertex(vertexNum-1,1,-1);
	dresser->AddTriangleVertex(frontside,1,-1);

	dresser->AddTriangleVertex(vertexNum - 1,1,-1);
	dresser->AddTriangleVertex(frontside + 1,1,-1);
	dresser->AddTriangleVertex(frontside,1,-1);

	//rightside
	dresser->AddNormal(CGrVector(1.,0.,0.,0.));

	dresser->AddTriangleVertex(3*vertexNum,2,-1);
	dresser->AddTriangleVertex(frontside + 2,2,-1);
	dresser->AddTriangleVertex(4*vertexNum-1,2,-1);

	dresser->AddTriangleVertex(4*vertexNum - 1,2,-1);
	dresser->AddTriangleVertex(frontside + 2,2,-1);
	dresser->AddTriangleVertex(frontside + 3,2,-1);
	//top
	dresser->AddNormal(CGrVector(0.,1.,0.,0.));

	dresser->AddTriangleVertex(frontside + 1,3,-1);
	dresser->AddTriangleVertex(vertexNum-1,3,-1);
	dresser->AddTriangleVertex(frontside + 3,3,-1);

	dresser->AddTriangleVertex(vertexNum - 1,3,-1);
	dresser->AddTriangleVertex(4*vertexNum-1,3,-1);
	dresser->AddTriangleVertex(frontside + 3,3,-1);

	//back
	dresser->AddNormal(CGrVector(0.,0.,-1.,0.));

	dresser->AddTriangleVertex(frontside,4,-1);
	dresser->AddTriangleVertex(frontside + 1,4,-1);
	dresser->AddTriangleVertex(frontside + 3,4,-1);

	dresser->AddTriangleVertex(frontside +3,4,-1);
	dresser->AddTriangleVertex(frontside +2,4,-1);
	dresser->AddTriangleVertex(frontside,4,-1);
	

	//add in the drawers
	if(!isDifferent)
	{
		CSgPtr <CSgTranslate> tran0 = new CSgTranslate( spacingx, spacing, drawerThickness); 
		CSgPtr <CSgTranslate> tran1 = new CSgTranslate( spacingx, 2*spacing + drawerHeight, drawerThickness ); 
		CSgPtr <CSgTranslate> tran2 = new CSgTranslate( spacingx, 3*spacing + 2*drawerHeight, drawerThickness);

		CreateDrawer(tran0, isDifferent);
		CreateDrawer(tran1, isDifferent);
		CreateDrawer(tran2, isDifferent);

		CSgPtr <CSgComposite> dressergrp = new CSgComposite(); 
		dressergrp->AddChild(dresser);
		dressergrp->AddChild(tran0);
		dressergrp->AddChild(tran1);
		dressergrp->AddChild(tran2);
		woodColor->AddChild(dressergrp);
		parent->AddChild(woodColor);
	}
	else
	{
		CSgPtr <CSgTranslate> tran0 = new CSgTranslate( spacingx, spacing, drawerThickness + depth/2.0); 
		CSgPtr <CSgTranslate> tran1 = new CSgTranslate( spacingx, 2*spacing + drawerHeight, drawerThickness + depth/2.0); 
		CSgPtr <CSgTranslate> tran2 = new CSgTranslate( spacingx, 3*spacing + 2*drawerHeight, drawerThickness + depth/2.0); 
		CreateDrawer(tran0, isDifferent);
		CreateDrawer(tran1, isDifferent);
		CreateDrawer(tran2, isDifferent);

		CSgPtr <CSgComposite> dressergrp = new CSgComposite(); 
		dressergrp->AddChild(dresser);
		dressergrp->AddChild(tran0);
		dressergrp->AddChild(tran1);
		dressergrp->AddChild(tran2);
		woodColor->AddChild(dressergrp);
		parent->AddChild(woodColor);
	}

	
	
	
}
void CSGDresserFactory::CreateDrawer(CSgComposite *parent, bool different)
{
	CSgPtr <CSgMesh > drawer = new CSgMesh();
	for(double z = 0; z >= -drawerThickness; z-= drawerThickness)
	{
		drawer->AddVertex(CGrVector(0,0,z,1));
		drawer->AddVertex(CGrVector(0,drawerHeight,z,1));
		drawer->AddVertex(CGrVector(drawerWidth,0,z,1));
		drawer->AddVertex(CGrVector(drawerWidth,drawerHeight,z,1));
	}
	//add the other verticies if the setting is unique 8 - 19
	if(isDifferent)
	{
			//back far points
			drawer->AddVertex(CGrVector(0,0,-depth,1));
			drawer->AddVertex(CGrVector(0,drawerHeight,-depth,1));
			drawer->AddVertex(CGrVector(drawerWidth,0,-depth,1));
			drawer->AddVertex(CGrVector(drawerWidth,drawerHeight,-depth,1));
			//back inner points
			drawer->AddVertex(CGrVector(drawerThickness,drawerThickness,-depth,1));
			drawer->AddVertex(CGrVector(drawerThickness,drawerHeight,-depth,1));
			drawer->AddVertex(CGrVector(drawerWidth - drawerThickness,drawerThickness,-depth,1));
			drawer->AddVertex(CGrVector(drawerWidth - drawerThickness,drawerHeight,-depth,1));
			//backside of front panel
			drawer->AddVertex(CGrVector(drawerThickness,drawerThickness,-drawerThickness,1));
			drawer->AddVertex(CGrVector(drawerThickness,drawerHeight,-drawerThickness,1));
			drawer->AddVertex(CGrVector(drawerWidth - drawerThickness,drawerThickness,-drawerThickness,1));
			drawer->AddVertex(CGrVector(drawerWidth - drawerThickness,drawerHeight,-drawerThickness,1));




	}
	//front
	drawer->AddNormal(CGrVector(0.,0.,1.,0.));

	drawer->AddTriangleVertex(3,0,-1);
	drawer->AddTriangleVertex(1,0,-1);
	drawer->AddTriangleVertex(0,0,-1);

	drawer->AddTriangleVertex(2,0,-1);
	drawer->AddTriangleVertex(3,0,-1);
	drawer->AddTriangleVertex(0,0,-1);

	//left side
	drawer->AddNormal(CGrVector(-1.,0.,0.,0.));

	drawer->AddTriangleVertex(5,1,-1);
	drawer->AddTriangleVertex(4,1,-1);
	drawer->AddTriangleVertex(0,1,-1);

	drawer->AddTriangleVertex(0,1,-1);
	drawer->AddTriangleVertex(1,1,-1);
	drawer->AddTriangleVertex(5,1,-1);
	//right side
	drawer->AddNormal(CGrVector(1.,0.,0.,0.));

	drawer->AddTriangleVertex(6,2,-1);
	drawer->AddTriangleVertex(7,2,-1);
	drawer->AddTriangleVertex(2,2,-1);

	drawer->AddTriangleVertex(3,2,-1);
	drawer->AddTriangleVertex(2,2,-1);
	drawer->AddTriangleVertex(7,2,-1);
	
	
	//top
	drawer->AddNormal(CGrVector(0.,1.,0.,0.));

	drawer->AddTriangleVertex(1,3,-1);
	drawer->AddTriangleVertex(3,3,-1);
	drawer->AddTriangleVertex(7,3,-1);

	drawer->AddTriangleVertex(7,3,-1);
	drawer->AddTriangleVertex(5,3,-1);
	drawer->AddTriangleVertex(1,3,-1);
	//bottom
	drawer->AddNormal(CGrVector(0.,-1.,0.,0.));

	drawer->AddTriangleVertex(0,4,-1);
	drawer->AddTriangleVertex(4,4,-1);
	drawer->AddTriangleVertex(6,4,-1);

	drawer->AddTriangleVertex(6,4,-1);
	drawer->AddTriangleVertex(2,4,-1);
	drawer->AddTriangleVertex(0,4,-1);

	//unique dresser component. Builds the rest of the drawer so it can be pulled out.
	if(isDifferent)
	{
		//backside of front panel
		drawer->AddNormal(CGrVector(0.,0.,-1.,0.));

		drawer->AddTriangleVertex(17,5,-1);
		drawer->AddTriangleVertex(19,5,-1);
		drawer->AddTriangleVertex(18,5,-1);

		drawer->AddTriangleVertex(18,5,-1);
		drawer->AddTriangleVertex(16,5,-1);
		drawer->AddTriangleVertex(17,5,-1);

		//back panel
		

		drawer->AddTriangleVertex(13,0,-1);
		drawer->AddTriangleVertex(14,0,-1);
		drawer->AddTriangleVertex(15,0,-1);

		drawer->AddTriangleVertex(13,0,-1);
		drawer->AddTriangleVertex(12,0,-1);
		drawer->AddTriangleVertex(14,0,-1);
		//left side extension
		drawer->AddTriangleVertex(4,1,-1);
		drawer->AddTriangleVertex(5,1,-1);
		drawer->AddTriangleVertex(9,1,-1);

		drawer->AddTriangleVertex(9,1,-1);
		drawer->AddTriangleVertex(8,1,-1);
		drawer->AddTriangleVertex(4,1,-1);
		//left of right piece
		drawer->AddTriangleVertex(19,1,-1);
		drawer->AddTriangleVertex(14,1,-1);
		drawer->AddTriangleVertex(18,1,-1);

		drawer->AddTriangleVertex(19,1,-1);
		drawer->AddTriangleVertex(15,1,-1);
		drawer->AddTriangleVertex(14,1,-1);
		//right side extension
		drawer->AddTriangleVertex(11,2,-1);
		drawer->AddTriangleVertex(7,2,-1);
		drawer->AddTriangleVertex(10,2,-1);

		drawer->AddTriangleVertex(6,2,-1);
		drawer->AddTriangleVertex(10,2,-1);
		drawer->AddTriangleVertex(7,2,-1);
		//right of left piece
		drawer->AddTriangleVertex(12,2,-1);
		drawer->AddTriangleVertex(13,2,-1);
		drawer->AddTriangleVertex(16,2,-1);

		drawer->AddTriangleVertex(16,2,-1);
		drawer->AddTriangleVertex(13,2,-1);
		drawer->AddTriangleVertex(17,2,-1);

		//top of bottom additional
		drawer->AddTriangleVertex(16,3,-1);
		drawer->AddTriangleVertex(18,3,-1);
		drawer->AddTriangleVertex(12,3,-1);

		drawer->AddTriangleVertex(14,3,-1);
		drawer->AddTriangleVertex(12,3,-1);
		drawer->AddTriangleVertex(18,3,-1);
		//top of left side
		drawer->AddTriangleVertex(5,3,-1);
		drawer->AddTriangleVertex(13,3,-1);
		drawer->AddTriangleVertex(9,3,-1);
		

		drawer->AddTriangleVertex(17,3,-1);
		drawer->AddTriangleVertex(13,3,-1);
		drawer->AddTriangleVertex(5,3,-1);
		//top of right side
		drawer->AddTriangleVertex(11,3,-1);
		drawer->AddTriangleVertex(15,3,-1);
		drawer->AddTriangleVertex(7,3,-1);

		drawer->AddTriangleVertex(19,3,-1);
		drawer->AddTriangleVertex(7,3,-1);
		drawer->AddTriangleVertex(15,3,-1);
		//bottom additional
		drawer->AddTriangleVertex(4,4,-1);
		drawer->AddTriangleVertex(8,4,-1);
		drawer->AddTriangleVertex(6,4,-1);

		drawer->AddTriangleVertex(6,4,-1);
		drawer->AddTriangleVertex(8,4,-1);
		drawer->AddTriangleVertex(10,4,-1);
	
	}

	parent->AddChild(drawer);
}