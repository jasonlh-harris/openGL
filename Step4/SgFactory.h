#pragma once
#include "SgObject.h"
#include "SgComposite.h"
#include "SgPtr.h"
#include "AnimationTime.h"

class CSgFactory
{
public:
	CSgFactory(void);
	virtual ~CSgFactory(void);
	virtual void Create(CSgComposite *root) = 0;
	//void Create(CSgComposite&);
	//CSgObject* Create(void);

	void SetTime(CAnimationTime *time) {m_time = time;}

protected:
	CAnimationTime *m_time;
};

