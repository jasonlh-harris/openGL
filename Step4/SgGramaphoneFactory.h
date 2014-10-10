#pragma once
#include "sgfactory.h"
#include "SgLatheObject.h"
#include "SgRectangle.h"
#include "SgCD.h"

class CSgGramaphoneFactory :
	public CSgFactory
{
public:
	CSgGramaphoneFactory(void);
	~CSgGramaphoneFactory(void);
	void Create(CSgComposite*);
	void Create(CSgComposite&);
	void CreateCD(CSgComposite*);
	CSgObject* Create(void);
};

