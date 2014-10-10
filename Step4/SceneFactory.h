#pragma once
#include "SgComposite.h"
class CSceneFactory
{
public:
	CSceneFactory(void);
	~CSceneFactory(void);

	void Create(CSgComposite &m);
};

