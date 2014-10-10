#include "stdafx.h"
#include "SgGramaphoneFactory.h"
#include "SgTranslate.h"
#include "SgBendyTube.h"
#include "SgRectangle.h"
#include "SgTexture.h"
#include "SgAnimationRotate.h"
#include "SgMaterial.h"

CSgGramaphoneFactory::CSgGramaphoneFactory(void)
{
}


CSgGramaphoneFactory::~CSgGramaphoneFactory(void)
{
}

void CSgGramaphoneFactory::CreateCD(CSgComposite* arg_CD)
{
	CSgPtr<CSgCD> m_cd = new CSgCD();
	CSgPtr<CSgRotateAroundPoint> cd_translate = new CSgRotateAroundPoint();
	CSgPtr<CSgTexture> m_DiskTexture = new CSgTexture(L"textures/vinylRecord.bmp");
	cd_translate->SetTranslation(-.4, 0, .35);
	//
	//CD Translation
	//
	cd_translate->SetAngle(0);
	cd_translate->SetNormal(0,1,0);
	m_DiskTexture->AddChild(cd_translate);
	cd_translate->AddChild(m_cd);
	m_cd->setVals(.1, .7, .005);
	arg_CD->AddChild(m_DiskTexture);
}

void CSgGramaphoneFactory::Create(CSgComposite* arg_Comp)
{

	CSgPtr<CSgBendyTube> m_Phone = new CSgBendyTube();
	CSgPtr<CSgBendyTube> m_PhoneSupporter = new CSgBendyTube();
	CSgPtr<CSgLatheObject> m_PhoneSupportLock = new CSgLatheObject();
	CSgPtr<CSgLatheObject> m_PhoneSupportLockInside = new CSgLatheObject();

	CSgPtr <CSgMaterial> woodColor = new CSgMaterial();
	woodColor->SetDiffuseColor(0.398f, 0.199f, 0.f, 1.0f);
	woodColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	woodColor->SetShininess(5.f);

	CSgPtr <CSgMaterial> brassColor = new CSgMaterial();
	brassColor->SetDiffuseColor(0.286f, 0.263f, 0.136f, 1.0f);
	brassColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	brassColor->SetShininess(.5f);

	CSgPtr<CSgMesh> bendy_mesh = new CSgMesh();
	CSgPtr<CSgMesh> bendy_mesh2 = new CSgMesh();

	CSgPtr<CSgLatheObject> m_readingHead = new CSgLatheObject();
	CSgPtr<CSgRectangle> m_readingHeadTop = new CSgRectangle();
	CSgPtr<CSgRectangle> m_readingHeadTopFirstBar = new CSgRectangle();


	m_Phone->SetMesh(bendy_mesh);
	m_PhoneSupporter->SetMesh(bendy_mesh2);

	CSgPtr<CSgRectangle> m_bottomBox = new CSgRectangle();
	m_bottomBox->SetBackLeft(0,0,0,.8, .8, .2);

	
	CSgPtr<CSgTranslate> GramophoneTotalTranslate = new CSgTranslate();
	CSgPtr<CSgTranslate> box_additionalTranslation = new CSgTranslate();

	CSgPtr<CSgTranslate> readerHeadTranslation = new CSgTranslate();
	CSgPtr<CSgTranslate> readerHeadTopTranslation = new CSgTranslate();
	CSgPtr<CSgTranslate> readerHeadTopFirstBarTranslation = new CSgTranslate();
	CSgPtr<CSgTranslate> phoneTranslation = new CSgTranslate();
	CSgPtr<CSgTranslate> phoneSupportTranslation = new CSgTranslate();
	CSgPtr<CSgTranslate> PhoneSupportLockTranslation = new CSgTranslate();



	GramophoneTotalTranslate->SetProperties(0,0,0);

	readerHeadTranslation->SetProperties(-0.5,0,0.1);
	box_additionalTranslation->SetProperties(-0.8, -.2, 0.7);
	
	//
	//ReaderHeadFirstBar
	// This is the bar that connects from the readerheadTop to the second bar
	readerHeadTopFirstBarTranslation->AddChild(m_readingHeadTopFirstBar);
	m_readingHeadTopFirstBar->SetBackLeft(0,0,0,.5,.2,.05);
	readerHeadTopFirstBarTranslation->SetProperties(-0.65,.1,0.25);


	

	//
	//ReaderHeadCap
	//
	readerHeadTopTranslation->SetProperties(-0.65,.1,0.25);
	readerHeadTopTranslation->AddChild(m_readingHeadTop);
	m_readingHeadTop->SetBackLeft(0,0,0,.2,.2,0.05);


	//
	//Box AdditionalTranslation
	//
	box_additionalTranslation->AddChild(m_bottomBox);


	
	
	//
	// DrawGramophone Phone
	//
	/*

	const double Length = 100;
	const double Diameter = 1;
	const int StepsLength = 100;
	const int StepsAround = 10;

	*/
	m_Phone->SetLength(2);
	m_Phone->SetDiameter(.02);
	m_Phone->SetDiameterEnd(.5);
	m_Phone->SetStepsLength(100);
	m_Phone->SetStepsAround(10);
	m_Phone->Create();
	phoneTranslation->AddChild(m_Phone);
	int slicesToRotateIn = 20;
	CGrTransform rot = CGrTransform::GetRotateZ(160 / slicesToRotateIn);
	for(int i =0; i < slicesToRotateIn; i++)
	{
		m_Phone->TransformAt(100 / 3 - slicesToRotateIn / 2 + i, rot);
	}
	phoneTranslation->SetProperties(-.15,.125,0);
	
	//
	//DrawGramophone Phone Support bendyBar
	//
	m_PhoneSupporter->SetLength(1);
	m_PhoneSupporter->SetDiameter(.25);
	m_PhoneSupporter->SetDiameterEnd(.25);
	m_PhoneSupporter->SetStepsAround(10);
	m_PhoneSupporter->SetStepsLength(100);
	m_PhoneSupporter->Create();
	phoneSupportTranslation->AddChild(m_PhoneSupporter);
	slicesToRotateIn = 20;
	CGrTransform rot2 = CGrTransform::GetRotateZ(75 / slicesToRotateIn);
	for(int i = 0; i < slicesToRotateIn; i++)
	{
		m_PhoneSupporter->TransformAt(60 - slicesToRotateIn / 2 + i, rot2);
	}
	slicesToRotateIn = 6;
	CGrTransform rot3 = CGrTransform::GetRotateZ(30 / slicesToRotateIn);
	for(int i = 0; i < slicesToRotateIn; i++)
	{
		m_PhoneSupporter->TransformAt(70 - slicesToRotateIn / 2 + i, rot3);
	}
	phoneSupportTranslation->SetProperties(0,-.1,0);

	//
	//DrawGramophone Support Ring
	//
	PhoneSupportLockTranslation->SetProperties(.57,.25,0);
	PhoneSupportLockTranslation->AddChild(m_PhoneSupportLock);
	PhoneSupportLockTranslation->AddChild(m_PhoneSupportLockInside);
	double m_PhoneSupportLockPoints[2][4]={
		{.22,0,1,0},
		{.22,.05,1, 0}
	};
	for(int j = 0; j < 1; j++)
	{
		m_PhoneSupportLock->AddSegment(m_PhoneSupportLockPoints[j][0], m_PhoneSupportLockPoints[j][1],
								m_PhoneSupportLockPoints[j][2], m_PhoneSupportLockPoints[j][3],
								m_PhoneSupportLockPoints[j+1][0], m_PhoneSupportLockPoints[j+1][1],
								m_PhoneSupportLockPoints[j+1][2], m_PhoneSupportLockPoints[j+1][2]);
	}

	for(int j = 1; j >  1; j--)
	{
		m_PhoneSupportLockInside->AddSegment(m_PhoneSupportLockPoints[j][0], m_PhoneSupportLockPoints[j][1],
								m_PhoneSupportLockPoints[j][2], m_PhoneSupportLockPoints[j][3],
								m_PhoneSupportLockPoints[j-1][0], m_PhoneSupportLockPoints[j-1][1],
								m_PhoneSupportLockPoints[j-1][2], m_PhoneSupportLockPoints[j-1][2]);
	}


	//
	//ReadingHead Section
	//
	readerHeadTranslation->AddChild(m_readingHead);
	double m_readingHeadPoints[2][4] = {
		{0,0, 1, 0}, //Double x1, y1, nx1, ny1
		{.1,.1,1,0}
	};
		
	for(int j = 0; j < 1; j++)
	{
		m_readingHead->AddSegment(m_readingHeadPoints[j][0], m_readingHeadPoints[j][1],
								m_readingHeadPoints[j][2], m_readingHeadPoints[j][3],
								m_readingHeadPoints[j+1][0], m_readingHeadPoints[j+1][1],
								m_readingHeadPoints[j+1][2], m_readingHeadPoints[j+1][2]);
	}

	

	//
	//Add all of these objects to the Gramophone total Translation
	//
	GramophoneTotalTranslate->AddChild(readerHeadTranslation);
	woodColor->AddChild(box_additionalTranslation);
	GramophoneTotalTranslate->AddChild(woodColor);
	//GramophoneTotalTranslate->AddChild(phoneTranslation);
	brassColor->AddChild(readerHeadTopTranslation);
	brassColor->AddChild(phoneTranslation);
	brassColor->AddChild(phoneSupportTranslation);
	brassColor->AddChild(PhoneSupportLockTranslation);
	brassColor->AddChild(readerHeadTopFirstBarTranslation);
	GramophoneTotalTranslate->AddChild(brassColor);
	//GramophoneTotalTranslate->AddChild(readerHeadTopTranslation);
	//GramophoneTotalTranslate->AddChild(readerHeadTopFirstBarTranslation);
	//GramophoneTotalTranslate->AddChild(phoneSupportTranslation);
	//GramophoneTotalTranslate->AddChild(PhoneSupportLockTranslation);

	//
	//Add the total translation (and every object) to the passed composite
	//
	arg_Comp->AddChild(GramophoneTotalTranslate);

}

CSgObject* CSgGramaphoneFactory::Create(void)
{
	CSgPtr<CSgComposite> comp = new CSgComposite();

	Create(comp);

	return comp;
}