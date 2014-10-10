#pragma once
#include "sgfactory.h"
#include "SgMesh.h"
class CSgCanFactory :
	public CSgFactory
{
public:
	CSgCanFactory(void);
	~CSgCanFactory(void);
	void Create(CSgComposite*);
	CSgObject* Create(void);
};
