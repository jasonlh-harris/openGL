#pragma once
#include "animation.h"
#include "graphics\GrVector.h"
#include "SgTranslate.h"
#include "SgRotateAroundPoint.h"
#include "SgPtr.h"

class CSgAnimationRotate :
	public CAnimation
{
public:
	CSgAnimationRotate(void);
	~CSgAnimationRotate(void);
	
	void SetRate(double rate){m_rate = rate;}
	void SetNode(CSgRotateAroundPoint *node){m_node = node;}

	virtual void Update(void);
protected:
	double m_rate;
	CSgRotateAroundPoint *m_node;
	int m_time;
};

