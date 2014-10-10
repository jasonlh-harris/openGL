#include "stdafx.h"
#include "SgClosetFactory.h"
#include "SgRotateAroundPoint.h"
#include "SgTranslate.h"
#include "SgRotateAroundPoint.h"
#include "SgTranslate.h"
#include "SgRotate.h"
#include "SgLatheObject.h"
#include "SgTexture.h"

using namespace std;
CSgClosetFactory::CSgClosetFactory(void)
{
	state = true;
	scale = 1.5;
}


CSgClosetFactory::~CSgClosetFactory(void)
{
}

void CSgClosetFactory::Create(CSgComposite* arg_Comp)
{
	
	CSgPtr<CSgRotateAroundPoint> closetHolder_and_Translation = new CSgRotateAroundPoint();
	CSgPtr<CSgTranslate> closetWall_Two_Offset_Translation = new CSgTranslate();
	CSgPtr<CSgTranslate> closetShelf_One_offset_Translation = new CSgTranslate();
	CSgPtr<CSgTranslate> closetShelf_Two_offset_Translation = new CSgTranslate();
	CSgPtr<CSgTranslate> closetCoatRack_offset_Translation = new CSgTranslate();
	CSgPtr<CSgRotateAroundPoint> closetCoatRack_rotation = new CSgRotateAroundPoint();
	CSgPtr<CSgTranslate> clostCeiling_Translation = new CSgTranslate();
	CSgPtr<CSgRotateAroundPoint> closetFrontDoorsOne_Translation = new CSgRotateAroundPoint();
	CSgPtr<CSgRotateAroundPoint> closetFrontDoorsTwo_Translation = new CSgRotateAroundPoint();
	CSgPtr<CSgTranslate> closetBottomDrawer_Translation = new CSgTranslate();
	CSgPtr<CSgTranslate> bottomPanel_Translation = new CSgTranslate();
	CSgPtr<CSgTexture> wardrobeTexture = new CSgTexture(L"textures/stainedwood.bmp");

	CSgPtr<CSgMesh> ClosetWallOne = new CSgMesh();
	CSgPtr<CSgMesh> ClosetWallTwo = new CSgMesh();
	CSgPtr<CSgMesh> ShelfOne = new CSgMesh();
	CSgPtr<CSgMesh> ShelfTwo = new CSgMesh();
	CSgPtr<CSgMesh> DoorOne = new CSgMesh();
	CSgPtr<CSgMesh> DoorTwo = new CSgMesh();
	CSgPtr<CSgMesh> closetDrawer = new CSgMesh();
	CSgPtr<CSgMesh> closetCeling = new CSgMesh();
	CSgPtr<CSgMesh> BottomPanel = new CSgMesh();
	CSgPtr<CSgLatheObject> CoatHanger = new CSgLatheObject();

	CreateWall(ClosetWallOne);
	CreateWall(ClosetWallTwo);
	CreateShelf(ShelfOne);
	CreateShelf(ShelfTwo);

	//Drawer
	CreateClostBottomDrawer(closetDrawer);
	if(state)
	{
		closetBottomDrawer_Translation->SetProperties(.5 / scale,0.2 / scale,2 / scale);
	}
	else
	{
		closetBottomDrawer_Translation->SetProperties(0.5/scale, 0.2/scale, 0.2/scale);
		
	}
	closetBottomDrawer_Translation->AddChild(closetDrawer);


	//BottomPanel
	bottomPanel_Translation->SetProperties(.2/ scale,0,0);
	CreateClosetBottomPanel(BottomPanel);
	bottomPanel_Translation->AddChild(BottomPanel);



	//closetCeling
	CreateClosetDoor(closetCeling, 3.3 / scale, 0.2 / scale, -3.5 / scale);
	clostCeiling_Translation->SetProperties(0.2 / scale,6.8 / scale,0);
	clostCeiling_Translation->AddChild(closetCeling);

	//closetDoor1
	CreateClosetDoor(DoorOne,1.85 / scale, 4.5 / scale, -0.2 / scale);
	closetFrontDoorsOne_Translation->SetTranslation(0 / scale,2.5 / scale,0.2 / scale);
	if(state)
	{
		closetFrontDoorsOne_Translation->SetNormal(0,1,0);
		closetFrontDoorsOne_Translation->SetAngle(180);
	}
	else
	{
		closetFrontDoorsOne_Translation->SetNormal(0,1,0);
		closetFrontDoorsOne_Translation->SetAngle(0);
	}

	closetFrontDoorsOne_Translation->AddChild(DoorOne);

	//closetDoor2
	CreateClosetDoor(DoorTwo,1.85 / scale, 4.5 / scale, -0.2 / scale);
	closetFrontDoorsTwo_Translation->SetTranslation(1.85 / scale,2.5 / scale,0.2 / scale);
	if(state)
	{
		closetFrontDoorsTwo_Translation->SetNormal(0,1,0);
		closetFrontDoorsTwo_Translation->SetAngle(180);
		closetFrontDoorsTwo_Translation->SetTranslation(1.85*3 / scale, 2.5 / scale, 0.2 / scale);
	}
	else
	{
		closetFrontDoorsTwo_Translation->SetNormal(0,1,0);
		closetFrontDoorsTwo_Translation->SetTranslation(1.85 / scale,2.5 / scale,0.2 / scale);
		closetFrontDoorsTwo_Translation->SetAngle(0);
	}
	closetFrontDoorsTwo_Translation->AddChild(DoorTwo);

	//Move wall two
	closetWall_Two_Offset_Translation->SetProperties(3.5 / scale,0,0);
	closetWall_Two_Offset_Translation->AddChild(ClosetWallTwo);

	//Move ShelfOne
	closetShelf_One_offset_Translation->SetProperties(0.2 / scale,3.5 / scale,0);
	closetShelf_One_offset_Translation->AddChild(ShelfOne);

	//Move ShelfTwo
	closetShelf_Two_offset_Translation->SetProperties(0.2 / scale,5 / scale,0);
	closetShelf_Two_offset_Translation->AddChild(ShelfTwo);

	//Move the CoatHanger & create it
	//closetCoatRack_offset_Translation->SetProperties(0,0,0);
	closetCoatRack_rotation->SetAngle(90);
	closetCoatRack_rotation->SetNormal(0,0,1);
	closetCoatRack_rotation->SetTranslation(3.3 / scale, 4.2 / (1.15* scale), -1.5 / scale);
	closetCoatRack_rotation->AddChild(CoatHanger);
	//closetCoatRack_offset_Translation->AddChild(CoatHanger);
	double CoatHangerDiameter = 0.1 / scale;
	double CoatHangerLength = 2.9 / scale;
	double CoatHangerPoints[2][4]={
		{CoatHangerDiameter,0,1,0},
		{CoatHangerDiameter,CoatHangerLength,1,0}
	};
	for(int j = 0; j < 1; j++)
	{
		CoatHanger->AddSegment(CoatHangerPoints[j][0], CoatHangerPoints[j][1],
								CoatHangerPoints[j][2], CoatHangerPoints[j][3],
								CoatHangerPoints[j+1][0], CoatHangerPoints[j+1][1],
								CoatHangerPoints[j+1][2], CoatHangerPoints[j+1][3]);
	}


	closetHolder_and_Translation->AddChild(closetBottomDrawer_Translation);
	closetHolder_and_Translation->AddChild(bottomPanel_Translation);
	closetHolder_and_Translation->AddChild(closetFrontDoorsTwo_Translation);
	closetHolder_and_Translation->AddChild(closetFrontDoorsOne_Translation);
	closetHolder_and_Translation->AddChild(clostCeiling_Translation);
	closetHolder_and_Translation->AddChild(closetCoatRack_rotation);
	closetHolder_and_Translation->AddChild(closetShelf_Two_offset_Translation);
	closetHolder_and_Translation->AddChild(closetShelf_One_offset_Translation);
	closetHolder_and_Translation->AddChild(ClosetWallOne);
	closetHolder_and_Translation->AddChild(closetWall_Two_Offset_Translation);
	
	closetHolder_and_Translation->SetTranslation(0,0,0);
	closetHolder_and_Translation->SetAngle(0);
	closetHolder_and_Translation->SetNormal(0,1,0);

	wardrobeTexture->AddChild(closetHolder_and_Translation);
	arg_Comp->AddChild(wardrobeTexture);

}

CSgObject* CSgClosetFactory::Create(void)
{
	CSgPtr<CSgComposite> comp = new CSgComposite();

	Create(comp);

	return comp;
}

void CSgClosetFactory::CreateShelf(CSgMesh* arg_Shelf)
{
	double ShelfWidth = 3.3f / scale;
	double ShelfHeight = 1.5f / scale;
	double ShelfDepth = -3.f / scale;
	double Height_ratio = 0.8f / scale;
	double XVal = 0.2 / scale;
	double closeShelfVerticies[20][4]=
	{
		{0,0,0,0}, //0
		{XVal,0,0,0}, //1
		{XVal,0,ShelfDepth,0}, //2
		{XVal,Height_ratio*ShelfHeight, ShelfDepth, 0}, //3
		{XVal, Height_ratio*ShelfHeight, 0, 0}, //4
		{ShelfWidth - XVal, Height_ratio*ShelfHeight, 0,0}, //5
		{ShelfWidth - XVal, Height_ratio*ShelfHeight, ShelfDepth, 0}, //6
		{ShelfWidth - XVal, 0,ShelfDepth, 0},//7
		{ShelfWidth - XVal,0,0,0}, //8
		{ShelfWidth, 0, 0, 0}, //9
		{ShelfWidth, 0, ShelfDepth, 0}, //10
		{ShelfWidth, ShelfHeight, ShelfDepth, 0}, //11
		{ShelfWidth, ShelfHeight, 0, 0}, //12
		{0, ShelfHeight, 0, 0}, //13
		{0, ShelfHeight, ShelfDepth, 0}, //14
		{0, 0, ShelfDepth, 0}, //15
		{0, Height_ratio * ShelfHeight, 0, 0}, //16
		{XVal, Height_ratio * ShelfHeight, 0, 0}, //17
		{ShelfWidth, Height_ratio * ShelfHeight, 0, 0}, //18
		{ShelfWidth, Height_ratio * ShelfHeight, ShelfDepth, 0}//19
	};
	double n[6][4]={
		{0,0,1,1},//0Front
		{1,0,0,1},//1Right Side
		{0,0,-1,1},//2Back
		{-1,0,0,1},//3Left
		{0,1,0,1},//4Top
		{0,-1,0,1}//5bottom
	};
	for(int i = 0; i < 20; i++)
		arg_Shelf->AddVertex(closeShelfVerticies[i]);
	for(int i = 0; i < 6; i++)
		arg_Shelf->AddNormal(n[i]);
	arg_Shelf->AddSelfTexturedQuad(0,1,4,16,0);//Front Section left leg
	arg_Shelf->AddSelfTexturedQuad(1,2,3,4,1); //Left leg, inside facing
	arg_Shelf->AddSelfTexturedQuad(3,6,5,4,5);// between two legs, bottom facing
	arg_Shelf->AddSelfTexturedQuad(7,8,5,6,3);//Inside portion, right leg
	arg_Shelf->AddSelfTexturedQuad(8,9,18,5,0);//Right Leg, front facing
	arg_Shelf->AddSelfTexturedQuad(9,10,11,12,1);//Right Leg, rightside facing
	arg_Shelf->AddSelfTexturedQuad(16,18,12,13,0);//Front Facing shelf portion
	arg_Shelf->AddSelfTexturedQuad(13,12,11,14,4);//Top Facing Shelf
	arg_Shelf->AddSelfTexturedQuad(15,0,13,14,3);//Left Leg, left facing
	arg_Shelf->AddSelfTexturedQuad(15,2,1,0,5);//Left Leg bottom facing
	arg_Shelf->AddSelfTexturedQuad(7,10,9,8,5);//Right Leg bottom facing
}

void CSgClosetFactory::CreateClosetDoor(CSgMesh* arg_Door, double Thickness, double Height, double Depth)
{
		double closetDoorVerticies[8][4]={
		{0,0,0,0}, //0 Front Left
		{Thickness,0,0,0}, //1 Front Right
		{Thickness,Height,0,0}, //2 Upper Right
		{0,Height,0,0}, // 3 Upper Left
		{Thickness,0,Depth,0}, //4 Back Right
		{Thickness,Height,Depth,0}, //5 Back Upper Right
		{0,0,Depth,0}, //6 Back Left
		{0,Height,Depth,0} // 7 Back Upper Left
	};
	double n[6][4]={
		{0,0,1,1},//0Front
		{1,0,0,1},//1Right Side
		{0,0,-1,1},//2Back
		{-1,0,0,1},//3Left
		{0,1,0,1},//4Top
		{0,-1,0,1}//5bottom
	};
	for(int i = 0; i < 8; i++)
		arg_Door->AddVertex(closetDoorVerticies[i]);
	for(int i = 0; i < 6; i++)
		arg_Door->AddNormal(n[i]);
	arg_Door->AddSelfTexturedQuad(0,1,2,3,0);
	arg_Door->AddSelfTexturedQuad(1,4,5,3,1);
	arg_Door->AddSelfTexturedQuad(6, 7, 5, 4, 2);
	arg_Door->AddSelfTexturedQuad(6,0,3,7,3);
	arg_Door->AddSelfTexturedQuad(3,2,5,7,4);
	arg_Door->AddSelfTexturedQuad(6,4,1,0,5);
}

void CSgClosetFactory::CreateWall(CSgMesh* arg_Wall)
{
	double WallThickness = 0.2 / scale;
	double Height = 7 / scale;
	double Depth = -3.5 / scale;
	double closetWallVerticies[8][4]={
		{0,0,0,0}, //0 Front Left
		{WallThickness,0,0,0}, //1 Front Right
		{WallThickness,Height,0,0}, //2 Upper Right
		{0,Height,0,0}, // 3 Upper Left
		{WallThickness,0,Depth,0}, //4 Back Right
		{WallThickness,Height,Depth,0}, //5 Back Upper Right
		{0,0,Depth,0}, //6 Back Left
		{0,Height,Depth,0} // 7 Back Upper Left
	};
	double closetWallNormals[6][4]={
		{0,0,1,1},//0Front
		{1,0,0,1},//1Right Side
		{0,0,-1,1},//2Back
		{-1,0,0,1},//3Left
		{0,1,0,1},//4Top
		{0,-1,0,1}//5bottom
	};
	for(int i = 0; i < 8; i++)
		arg_Wall->AddVertex(closetWallVerticies[i]);
	for(int i = 0; i < 6; i++)
		arg_Wall->AddNormal(closetWallNormals[i]);
	arg_Wall->AddSelfTexturedQuad(0,1,2,3,0);
	arg_Wall->AddSelfTexturedQuad(1,4,5,3,1);
	arg_Wall->AddSelfTexturedQuad(6, 7, 5, 4, 2);
	arg_Wall->AddSelfTexturedQuad(6,0,3,7,3);
	arg_Wall->AddSelfTexturedQuad(3,2,5,7,4);
	arg_Wall->AddSelfTexturedQuad(6,4,1,0,5);
}

void CSgClosetFactory::CreateClosetBottomPanel(CSgMesh* arg_Panel)
{
	double panelWidth = 3.3 / scale;
	double panelDepth = 3.5 / scale;
	double panelHeight = 2.5 / scale;
	double OpeningOffset = .5 / scale;
	double BottomPanelMeshVerticies[14][4]={
		{0,0,0,0}, // 0 Front bottom Left
		{panelWidth, 0,0,0}, // 1 Front bottom right
		{panelWidth, panelHeight, 0,0}, // 2 front top Right
		{0, panelHeight, 0,0}, //3 Front top Left
		{OpeningOffset, OpeningOffset, 0, 0},//4 bottom left opening point
		{panelWidth - OpeningOffset, OpeningOffset, 0, 0}, // 5 bottom right opening offset
		{panelWidth - OpeningOffset, panelHeight - OpeningOffset, 0 ,0}, // 6 top right opening offset
		{OpeningOffset, panelHeight - OpeningOffset, 0, 0}, // 7 top left opening offset
		{panelWidth, OpeningOffset, 0, 0}, // 8, verticy to make the opening Offset easier, bottom right front
		{0, OpeningOffset, 0, 0}, // 9 Verticy to make the openingOffset easier, bottom left
		{0, panelHeight - OpeningOffset, 0, 0}, //10 Verticy to make the opening Offset easier, top left
		{panelWidth, panelHeight - OpeningOffset,0,0}, // 11, verticy to make the openingOffsetEaser, top right
		{panelWidth, panelHeight, -panelDepth, 0}, //12 Upper back right
		{0, panelHeight, -panelDepth, 0}//13 upper back left
	};
	double n[6][4]={
		{0,0,1,1},//0Front
		{1,0,0,1},//1Right Side
		{0,0,-1,1},//2Back
		{-1,0,0,1},//3Left
		{0,1,0,1},//4Top
		{0,-1,0,1}//5bottom
	};
	for( int i = 0; i < 14; i++)
	{
		arg_Panel->AddVertex(BottomPanelMeshVerticies[i]);
	}
	for(int i = 0; i < 6; i++)
	{
		arg_Panel->AddNormal(n[i]);
	}
	arg_Panel->AddSelfTexturedQuad(0,1,8,9,0);
	arg_Panel->AddSelfTexturedQuad(5,8,11,6,0);
	arg_Panel->AddSelfTexturedQuad(10,11,2,3,0);
	arg_Panel->AddSelfTexturedQuad(9,4,7,10,0);
	arg_Panel->AddSelfTexturedQuad(3,2,12,13,4);

}

void CSgClosetFactory::CreateClostBottomDrawer(CSgMesh* arg_Drawer)
{
	double frontWidth = 2.8 / scale;
	double frontHeight = 2. / scale;
	double frontDepth = -0.2 / scale;

	double SectionDepth = 0;
	double SectionHeight = 0;
	
	double DrawerDepth = -3.5 / scale;

	double DrawerInset = 0.3 / scale;
	double DrawerHeight = frontHeight - DrawerInset;
	double DrawerWidth = 0;
	
	double DrawerWallThickness = 0.1 / scale;


	double DrawerMeshverticies[28][4]={
		{0,0,0,0}, //0 Front Left
		{frontWidth,0,0,0}, //1 Front Right
		{frontWidth,frontHeight,0,0}, //2 Upper Right
		{0,frontHeight,0,0}, // 3 Upper Left
		{frontWidth,0,frontDepth,0}, //4 front Back Right
		{frontWidth,frontHeight,frontDepth,0}, //5 front Back Upper Right
		{frontWidth - DrawerInset,DrawerInset,frontDepth,0}, //6 Drawer front bottom right, as seen from front
		{frontWidth - DrawerInset,DrawerInset,frontDepth + DrawerDepth,0}, // 7 Drawer back bottom right, as seen from front
		{frontWidth - DrawerInset,frontHeight - DrawerInset, frontDepth + DrawerDepth,0}, //8 Drawer, drawer portion, upper back right (as seen from front)
		{frontWidth - DrawerInset,frontHeight - DrawerInset,frontDepth,0}, //9 Drawer front upper right, as seen from front
		{DrawerInset,DrawerInset,frontDepth + DrawerDepth,0}, //10 Drawer back bottom right, as seen from back of drawer
		{DrawerInset,frontHeight - DrawerInset,frontDepth + DrawerDepth,0}, //11 Drawer back upper right as seen from back of drawer
		{DrawerInset,DrawerInset,frontDepth,0}, //12 Drawer front part, back bottom left as seen from drawer side with front toward right
		{0,frontHeight,frontDepth,0}, //13 Drawer front part, back upper left, as een from side of drawer with front toward right
		{frontWidth - DrawerInset - DrawerWallThickness,frontHeight - DrawerInset,frontDepth,0}, //14
		{frontWidth - DrawerInset - DrawerWallThickness,frontHeight - DrawerInset,frontDepth + DrawerDepth + DrawerWallThickness,0}, //15
		{0,0,frontDepth,0}, //16
		{frontWidth - DrawerInset,frontHeight - DrawerInset,frontDepth + DrawerDepth + DrawerWallThickness,0}, //17
		{frontWidth - DrawerInset - DrawerWallThickness,DrawerInset,frontDepth + DrawerDepth + DrawerWallThickness,0}, //18
		{frontWidth - DrawerInset - DrawerWallThickness,DrawerInset,frontDepth,0}, //19
		{DrawerInset + DrawerWallThickness,DrawerInset,frontDepth,0}, //20
		{DrawerInset + DrawerWallThickness,DrawerInset,frontDepth + DrawerDepth + DrawerWallThickness,0}, //21
		{DrawerInset,DrawerInset,frontDepth + DrawerDepth,0}, //22
		{DrawerInset + DrawerWallThickness,DrawerHeight,frontDepth + DrawerDepth,0}, //23
		{DrawerInset + DrawerWallThickness,DrawerHeight,frontDepth + DrawerDepth + DrawerWallThickness,0}, //24
		{DrawerInset,DrawerHeight,frontDepth + DrawerDepth +DrawerWallThickness,0}, //25
		{DrawerInset + DrawerWallThickness, DrawerHeight, frontDepth, 0}, //26
		{DrawerInset, DrawerHeight, frontDepth, 0} //27
	};
	double n[6][4]={
		{0,0,1,1},//0Front
		{1,0,0,1},//1Right Side
		{0,0,-1,1},//2Back
		{-1,0,0,1},//3Left
		{0,1,0,1},//4Top
		{0,-1,0,1}//5bottom
	};

	for(int i = 0; i < 28; i++)
	{
		arg_Drawer->AddVertex(DrawerMeshverticies[i]);
	}
	for(int i = 0; i < 6; i++)
	{
		arg_Drawer->AddNormal(n[i]);
	}
	arg_Drawer->AddSelfTexturedQuad(0,1,2,3,0); //front
	arg_Drawer->AddSelfTexturedQuad(1,4,5,2,1); //front right thickness
	arg_Drawer->AddSelfTexturedQuad(6,7,8,9,1); // Drawer, drawer part, right outer facing side
	arg_Drawer->AddSelfTexturedQuad(7,10,11,8,2); //Drawer, Drawer back, backwards facing side
	arg_Drawer->AddSelfTexturedQuad(16,0,3,13,3); //Drawer front part, left thickness
	arg_Drawer->AddSelfTexturedQuad(3,2,5,13,4); //Drawe front part, top thickness
	arg_Drawer->AddSelfTexturedQuad(16,4,1,0,5); //DrawerFront part, bottom thickness
	arg_Drawer->AddSelfTexturedQuad(14,9,17,15,4); //Drawer right wall top part
	arg_Drawer->AddSelfTexturedQuad(18,19,14,15,3); //Drawer Right wall inside part
	arg_Drawer->AddSelfTexturedQuad(20,19,18,21,4); //Drawer, inside bottom, top face
	arg_Drawer->AddSelfTexturedQuad(21,18,15,24,0); //Drawer, inside back front face
	arg_Drawer->AddSelfTexturedQuad(25,17,8,11,4); //Drawer back, thickness top face
	arg_Drawer->AddSelfTexturedQuad(7,10,11,8, 2); //Drawer back, back face
	arg_Drawer->AddSelfTexturedQuad(10,12,27,11,3); //Drawer left side, outside face
	arg_Drawer->AddSelfTexturedQuad(27,26,24,25,4); //DrawerLeft side, top face
	arg_Drawer->AddSelfTexturedQuad(20,21,24,26,1); //Drawerleft side, inside fae
	arg_Drawer->AddSelfTexturedQuad(19,20,26,14,2); //Drawer front, inside facing
	arg_Drawer->AddSelfTexturedQuad(4,16,13,5,2);
	arg_Drawer->AddSelfTexturedQuad(10,22,15,11,3);

}