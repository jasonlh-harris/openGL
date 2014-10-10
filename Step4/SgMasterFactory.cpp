#include "stdafx.h"
#include "SgMasterFactory.h"
#include "SgTranslate.h"
#include "SgRotateAroundPoint.h"
#include "Animation.h"
#include "AnimationPengCar.h"
#include "SgAnimationRotate.h"
#include "SgAnimationRotateWait.h"
#include "SgMaterial.h"
#include "SgRotate.h"

#include "AnimationBounce.h"

CSgMasterFactory::CSgMasterFactory(void)
{
	//break down the dorms into sparate rooms
	m_dorm1 = new CSgComposite();
	m_dorm2 = new CSgComposite();
	m_dorm3 = new CSgComposite();
	m_dorm4 = new CSgComposite();
	m_dorm5 = new CSgComposite();

	peng_dorm = new CPengFactory();
	m_DresserFactory = new CSGDresserFactory();
	yue_dorm = new CYueFactory();
	m_windowFactory = new CWindowFactory();
	m_ClosetFactory = new CSgClosetFactory();
	m_can = new CSgCanFactory();
	m_GramaphoneFacotry = new CSgGramaphoneFactory();
	m_PosterFactory = new CSgPosterFactory();
}


CSgMasterFactory::~CSgMasterFactory(void)
{
	delete peng_dorm;
	delete m_ClosetFactory;
	delete m_DresserFactory;
	delete m_windowFactory;
	delete yue_dorm;
	delete m_can;
	delete m_GramaphoneFacotry;
	delete m_PosterFactory;
}
CSgObject* CSgMasterFactory::Create(void)
{
	CSgPtr<CSgComposite> comp = new CSgComposite();

	Create(comp);

	return comp;
}
void CSgMasterFactory::Create(CSgComposite *parent)
{
		


	//Create the Structure
	yue_dorm -> CreateDorm(parent);
	m_windowFactory->CreateWin(parent);

	//
	//Backdrop
	//
	CSgPtr<CSgTranslate> backdropPlacement_Translation = new CSgTranslate(-10,-5,-20);
	m_PosterFactory->SetWidthHeight(60,30);
	m_PosterFactory->setBordered(false);
	m_PosterFactory->SetPicture(L"textures/Backdrop.bmp");
	m_PosterFactory->Create(backdropPlacement_Translation);
	parent->AddChild(backdropPlacement_Translation);
	
	//
	//Jason's Room
	//

	//m_dorm1->AddChild(gramophonePlacement_Translation);

	CSgPtr<CSgRotateAroundPoint> closetPlacement_Translation = new CSgRotateAroundPoint();
	closetPlacement_Translation->SetTranslation(2.9,1,9);
	closetPlacement_Translation->SetNormal(0,1,0);
	closetPlacement_Translation->SetAngle(90);
	m_ClosetFactory->Create(closetPlacement_Translation);
	m_dorm1->AddChild(closetPlacement_Translation);

	CSgPtr<CSgTranslate> posterPlacement_Translation = new CSgTranslate(1,4,.8);
	m_PosterFactory->SetWidthHeight(2,2);
	m_PosterFactory->setBordered(true);
	m_PosterFactory->setBorderedTexture(L"textures/RedWoodFloor.bmp");
	m_PosterFactory->isBorderedTextured(true);
	m_PosterFactory->SetPicture(L"textures/DayquilNyquil.bmp");
	m_PosterFactory->Create(posterPlacement_Translation);
	m_dorm1->AddChild(posterPlacement_Translation);

	CSgPtr<CSgTranslate> deskPlacement_Translation = new CSgTranslate(-17,0,0);
	peng_dorm->CreateDesk(deskPlacement_Translation, 0);
	m_dorm1->AddChild(deskPlacement_Translation);

	CSgPtr<CSgRotateAroundPoint> dresserPlacement_Translation_Orientation = new CSgRotateAroundPoint;
	dresserPlacement_Translation_Orientation->SetNormal(0,1,0);
	dresserPlacement_Translation_Orientation->SetAngle(90);
	dresserPlacement_Translation_Orientation->SetTranslation(1,1,5);
	m_DresserFactory->Create(dresserPlacement_Translation_Orientation);
	m_dorm1->AddChild(dresserPlacement_Translation_Orientation);


	CSgPtr<CSgRotateAroundPoint> bedPlacement_Translation_Orientation = new CSgRotateAroundPoint;
	bedPlacement_Translation_Orientation->SetNormal(0,1,0);
	bedPlacement_Translation_Orientation->SetAngle(00);
	bedPlacement_Translation_Orientation->SetTranslation(5.5,1,3.0);
	yue_dorm->CreateMadeBed(bedPlacement_Translation_Orientation);
	m_dorm1->AddChild(bedPlacement_Translation_Orientation);


	CSgPtr<CSgRotateAroundPoint> gramophonePlacement_Translation = new CSgRotateAroundPoint();
	gramophonePlacement_Translation->SetTranslation(2,6,8);
	gramophonePlacement_Translation->SetAngle(180);
	gramophonePlacement_Translation->SetNormal(0,1,0);
	CSgPtr<CSgTranslate> cdTranslate = new CSgTranslate(0,0,0);
	m_GramaphoneFacotry->CreateCD(cdTranslate);
	m_GramaphoneFacotry->Create(gramophonePlacement_Translation);
	CSgPtr<CSgRotateAroundPoint> diskOrientation = new CSgRotateAroundPoint();
	diskOrientation->SetAngle(0);
	diskOrientation->SetNormal(0,1,0);
	diskOrientation->SetTranslation(2.8,6,7.3);
	diskOrientation->SetPoint(-.4, 0, .35);
	diskOrientation->AddChild(cdTranslate);
	CSgPtr<CSgAnimationRotate> diskAnimation = new CSgAnimationRotate();
	diskAnimation->SetRate(33);
	diskAnimation->SetNode(diskOrientation);
	m_time->AddChannel(diskAnimation);
	m_dorm1->AddChild(diskOrientation);
	m_dorm1->AddChild(gramophonePlacement_Translation);

	//
	//Kevin's Room
	//
	m_ClosetFactory->SwitchState(); //Close the closet
	CSgPtr <CSgTranslate> trank1 = new CSgTranslate( 11.35, 1,9); //translation for closet
	CSgPtr <CSgRotate> rotk1 = new CSgRotate(90, 0, 1,0); //rotate the closet
	trank1->AddChild(rotk1);
	m_ClosetFactory->Create(trank1);
	m_dorm2->AddChild(trank1);

	//Make the poster
	CSgPtr<CSgTranslate> kevinPosterTrans = new CSgTranslate(9.5,4,.51);
	m_PosterFactory->SetWidthHeight(2,2);
	m_PosterFactory->setBordered(true);
	m_PosterFactory->SetPicture(L"textures/kevinPoster.bmp");
	m_PosterFactory->setBorderedTexture(L"textures/plastic.bmp");
	m_PosterFactory->isBorderedTextured(true);
	m_PosterFactory->Create(kevinPosterTrans);
	m_dorm2->AddChild(kevinPosterTrans);
	m_ClosetFactory->SwitchState();

	
	//Make all but the animated parts of newtons cradle
	CSgPtr <CSgTranslate > newtonTrans = new CSgTranslate(10,2.7,2);
	m_windowFactory->CreateNewtonCradle(newtonTrans);
	m_windowFactory->CreateNewtonNonMove(newtonTrans);
	CSgPtr <CSgTranslate > newtonAnimate = new CSgTranslate(10,2.7,2);
	m_windowFactory->CreateNewtonRotate(newtonAnimate);
	CSgPtr <CSgTranslate > newtonAnimate2 = new CSgTranslate(10.4,2.7,2);
	m_windowFactory->CreateNewtonRotate(newtonAnimate2);
	m_dorm2->AddChild(newtonTrans);

	//Make the left animated ball and wire
	double newtonHoldTime = 11;
	CSgPtr<CSgRotateAroundPoint> newtonRotate = new CSgRotateAroundPoint();
	newtonRotate->SetAngle(0);
	newtonRotate->SetNormal(0,0,1);
	newtonRotate->SetPoint( 10.174+(.2/7),3.474,2.2);
	newtonRotate->AddChild(newtonAnimate);
	CSgPtr<CSgAnimationRotateWait> newtonAnimation = new CSgAnimationRotateWait();//Setup animation parameters
	newtonAnimation->SetRate(newtonHoldTime);
	newtonAnimation->SetReverse(true);
	newtonAnimation->SetUpperLimit(0);
	newtonAnimation->SetLowerLimit(-55);
	newtonAnimation->SetNode(newtonRotate);
	newtonAnimation->SetIHoldUpper(true);
	m_time->AddChannel(newtonAnimation);

	//Make the right animated ball and wire
	CSgPtr<CSgRotateAroundPoint> newtonRotate2 = new CSgRotateAroundPoint();
	newtonRotate2->SetAngle(0);
	newtonRotate2->SetNormal(0,0,1);
	newtonRotate2->SetPoint( 10.574+(.2/7),3.474,2.2);
	newtonRotate2->AddChild(newtonAnimate2);
	CSgPtr<CSgAnimationRotateWait> newtonAnimation2 = new CSgAnimationRotateWait();//Setup animation parameters
	newtonAnimation2->SetRate(newtonHoldTime);
	newtonAnimation2->SetHoldTime(newtonHoldTime-1);
	newtonAnimation2->SetIHoldLower(true);
	newtonAnimation2->SetNode(newtonRotate2);
	newtonAnimation2->SetUpperLimit(55);
	newtonAnimation2->SetLowerLimit(0);
	m_time->AddChannel(newtonAnimation2);

	//Add the two animations to the dorm
	m_dorm2->AddChild(newtonRotate2);
	m_dorm2->AddChild(newtonRotate);

	//Create and translate the made bed
	CSgPtr <CSgTranslate> trank2 = new CSgTranslate( 14 , 1,.5);
	yue_dorm->CreateMadeBed(trank2);
	m_dorm2->AddChild(trank2);

	//create and translate the desk
	CSgPtr<CSgTranslate> kevinDeskTrans= new CSgTranslate(-8.6,0,0);
	peng_dorm->CreateDesk(kevinDeskTrans, 0);
	m_dorm1->AddChild(kevinDeskTrans);

	//create and translate the mini dresser
	CSgPtr<CSgRotateAroundPoint> trank3 = new CSgRotateAroundPoint;
	trank3->SetNormal(0,1,0);
	trank3->SetAngle(90);
	trank3->SetTranslation(9.5,1,5);
	m_DresserFactory->Create(trank3);
	m_dorm1->AddChild(trank3);

	//
	//Peng's Room
	//

	CSgPtr <CSgTranslate> tranp1 = new CSgTranslate( 2 * 10.5, 1.0,1.5 ); 	
	m_DresserFactory->Create(tranp1);
	m_dorm4->AddChild(tranp1);
	peng_dorm->CreateDesk(m_dorm3, 2);
	CSgPtr <CSgTranslate> start = new CSgTranslate(0,0,0);
	peng_dorm->CreateCar(start);
	peng_dorm->CreatePoster(m_dorm3);
	CSgPtr <CAnimationPengCar> CarAnimation = new CAnimationPengCar();
	CarAnimation->SetNode(start);
	m_time->AddChannel(CarAnimation);
	m_dorm3->AddChild(start);

	m_ClosetFactory->SwitchState();
	CSgPtr <CSgTranslate> drawerTrans = new CSgTranslate(22.5, 1, 2.5);
	m_ClosetFactory->Create(drawerTrans);
	CSgPtr <CSgMaterial> drawerColor = new CSgMaterial();
	drawerColor->SetDiffuseColor(1.f, 0.5f, 0.f, 1.f);
	drawerColor->SetSpecularColor(0.f, 0.f, 0.f, 1.f);
	drawerColor->AddChild(drawerTrans);

	CSgPtr <CSgRotateAroundPoint> bedRotate = new CSgRotateAroundPoint ();
	bedRotate->SetAngle(90);
	bedRotate->SetPoint(0,0,0);
	bedRotate->SetNormal(0,1,0);
	yue_dorm->CreateMadeBed(bedRotate);

	CSgPtr <CSgTranslate> bedTrans = new CSgTranslate(19.5, 1, 8);
	bedTrans->AddChild(bedRotate);
	m_dorm3->AddChild(drawerColor);
	m_dorm3->AddChild(bedTrans);

	

	//
	//Bens room
	//
	CSgPtr <CSgTranslate> tranb1 = new CSgTranslate( 3.45 * 8.5, 1.0,1.5 ); 
	CSgPtr <CSgTranslate> tranb2 = new CSgTranslate( 1.5 * 8.5 ,0.0 ,0 ); 
	CSgPtr <CSgTranslate> tranb3 = new CSgTranslate( 3.45 *8.5 + .5, 1.86,1 + .45); 
	CSgPtr <CSgTranslate> tranb4 = new CSgTranslate( 9.8* 3, 1,7); 
	CSgPtr <CSgTranslate> tranb5 = new CSgTranslate( 8.5* 3 + .5, 1.0,1); 
	CSgPtr<CSgTranslate> posterPlacement = new CSgTranslate(7.8 * 4,4,.8);

	//animation
	m_can->Create(tranb3);

	CSgPtr<CSgRotateAroundPoint> canOrientation = new CSgRotateAroundPoint();
	canOrientation->SetAngle(0);
	canOrientation->SetNormal(0,1,0);
	canOrientation->SetPoint( 3.45 *8.5 + .5, 1.86,1 + .45);
	canOrientation->AddChild(tranb3);
	CSgPtr<CSgAnimationRotate> canAnimation = new CSgAnimationRotate();
	canAnimation->SetRate(33);
	canAnimation->SetNode(canOrientation);
	m_time->AddChannel(canAnimation);
	

	m_PosterFactory->SetWidthHeight(2,2);
	m_PosterFactory->setBordered(true);
	m_PosterFactory->SetPicture(L"textures/CloseEnough.jpg");
	
	
	m_DresserFactory->SetDifferent(true);

	//Create Objects
	
	m_DresserFactory->Create(tranb1);
	peng_dorm->CreateDesk(tranb2, 0.8);
	
	m_ClosetFactory->Create(tranb4);
	yue_dorm->CreateMadeBed(tranb5);
	m_PosterFactory->Create(posterPlacement);
	
	
	m_dorm4->AddChild(tranb1);
	m_dorm4->AddChild(tranb2);
	m_dorm4->AddChild(canOrientation);
	m_dorm4->AddChild(tranb4);
	m_dorm4->AddChild(posterPlacement);
	m_dorm4->AddChild(tranb5);
	
	//
	//Yue's Room
	//

	CSgPtr <CSgTranslate> trany1 = new CSgTranslate( 2 * 8.5 - 0.2, 0., -1.); 
	CSgPtr <CSgTranslate> trany2 = new CSgTranslate( 4 * 8.5, 1., 5.); 
	CSgPtr <CSgTranslate> trany3 = new CSgTranslate( 4 * 8.5 + 5.5, 1.,0.5);
	peng_dorm->CreateDesk(trany1, 0.5);
	
	CSgPtr <CSgTranslate> dresTrany = new CSgTranslate( 4 * 8.5 + 0.5 , 3., 1.);
	m_DresserFactory->Create(dresTrany);

	CSgPtr <CSgRotateAroundPoint> bedRot = new CSgRotateAroundPoint();
	bedRot->SetTranslation( 4 * 8.5 + 8.5, 1., 9.0);
	bedRot->SetNormal(0, 1, 0);
	bedRot->SetAngle(180);
	yue_dorm->CreateUnmadeBed(bedRot);

	CSgPtr <CSgRotateAroundPoint> cloRot = new CSgRotateAroundPoint();
	cloRot->SetTranslation( 4 * 8.5 + 3., 1., 9.);
	cloRot->SetNormal(0, 1, 0);
	cloRot->SetAngle(90);
	m_ClosetFactory->SwitchState();
	m_ClosetFactory->Create(cloRot);

	CSgPtr <CSgRotateAroundPoint> hoopRot = new CSgRotateAroundPoint();
	hoopRot->SetTranslation( 4 * 8.5 + 2.2, 1., 4.);
	hoopRot->SetNormal(0, 1, 0);
	hoopRot->SetAngle(90);
	yue_dorm->CreateHoop(hoopRot);

	CSgPtr<CSgTranslate> posterTrany = new CSgTranslate(10. * 4,4,.8);
	m_PosterFactory->SetWidthHeight(2,2);
	m_PosterFactory->setBordered(true);
	m_PosterFactory->setBorderedTexture(L"textures/marble03.bmp");
	m_PosterFactory->SetPicture(L"textures/Hippo.bmp");
	m_PosterFactory->isBorderedTextured(true);
	m_PosterFactory->Create(posterTrany);

	CSgPtr <CSgTranslate> ballTrany = new CSgTranslate(4 * 8.5 + 3.8, 1.8 , 3.8);
	yue_dorm->Ball(ballTrany);

	CSgPtr <CAnimationBounce> ballAni = new CAnimationBounce();
	ballAni->SetNode(ballTrany);
	m_time->AddChannel(ballAni);

	m_dorm5->AddChild(trany1);
	m_dorm5->AddChild(cloRot);
	m_dorm5->AddChild(bedRot);
	m_dorm5->AddChild(hoopRot);
	m_dorm5->AddChild(posterTrany);
	m_dorm5->AddChild(dresTrany);
	m_dorm5->AddChild(ballTrany);

	//Add the rooms together
	
	parent->AddChild(m_dorm1);
	parent->AddChild(m_dorm2);
	parent->AddChild(m_dorm3);
	parent->AddChild(m_dorm4);
	parent->AddChild(m_dorm5);
}

