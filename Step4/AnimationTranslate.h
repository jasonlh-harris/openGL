#pragma once
#include "animation.h"
#include "graphics/GrVector.h"
#include "SgTranslate.h"


class CAnimationTranslate :
	public CAnimation
{
public:
	CAnimationTranslate(void);
	~CAnimationTranslate(void);

	void SetRate(CGrVector rate){m_rate = CGrVector(rate.X(), rate.Y(), rate.Z());}
	void SetNode(CSgTranslate *node){m_node = node;}

	virtual void Update(void);

protected:
	CGrVector m_rate;
	CSgTranslate *m_node;
};

