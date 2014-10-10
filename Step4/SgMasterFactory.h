#pragma once
#include "sgfactory.h"
#include "SgComposite.h"
#include "PengFactory.h"
#include "YueFactory.h"
#include "WindowFactory.h"

#include "SgClosetFactory.h"
#include "SGDresserFactory.h"
#include "SgCanFactory.h"
#include "AnimationTime.h"
#include "SgGramaphoneFactory.h"
#include "SgPosterFactory.h"

class CSgMasterFactory:public CSgFactory
{
public:
	CSgMasterFactory(void);
	~CSgMasterFactory(void);
	CSgObject* Create(void);
	void Create(CSgComposite *parent);


private:

	//Peng's Dorm
	CPengFactory *peng_dorm;
	//CSgComposite *m_dorm;

	//Jason's stuff
	CSgClosetFactory* m_ClosetFactory;
	CSgGramaphoneFactory *m_GramaphoneFacotry;
	CSgPosterFactory* m_PosterFactory;

	//Ben's dresser
	CSGDresserFactory* m_DresserFactory;

	//Windows!
	CWindowFactory *m_windowFactory;

	//Yue's Dorm
	CYueFactory *yue_dorm;

	//Rooms
	CSgPtr<CSgComposite> m_dorm1;
	CSgPtr<CSgComposite> m_dorm2;
	CSgPtr<CSgComposite> m_dorm3;
	CSgPtr<CSgComposite> m_dorm4;
	CSgPtr<CSgComposite> m_dorm5;
	
	//DecorativeObject (Ben)
	CSgCanFactory* m_can;

	//Textures(General)

};

