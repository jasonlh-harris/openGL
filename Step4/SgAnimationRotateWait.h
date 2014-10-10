#pragma once
#include "animation.h"
#include "graphics\GrVector.h"
#include "SgTranslate.h"
#include "SgRotateAroundPoint.h"
#include "SgPtr.h"
#include "sganimationrotate.h"
class CSgAnimationRotateWait :
	public CSgAnimationRotate
{
public:
	CSgAnimationRotateWait(void);
	~CSgAnimationRotateWait(void);

	void SetRate(double rate){m_rate = rate;}
	void SetNode(CSgRotateAroundPoint *node){m_node = node;}
	void SetHoldTime(double time){m_holdTime = time;}

	void SwitchReverse(){if(m_reverse)m_reverse=false;else m_reverse=true;}
	void SetReverse(bool reverse){m_reverse = reverse;}

	void SetIHoldUpper(bool lower){m_ignoreHoldLower = lower;}
	void SetIHoldLower(bool upper){m_ignoreHoldUpper = upper;}
	
	void SetUpperLimit(double upper){m_upperLim = upper;}
	void SetLowerLimit(double lower){m_lowerLim = lower;}

	virtual void Update(void);
protected:
	double m_rate;
	CSgRotateAroundPoint *m_node;
	int m_time;
	double m_holdTime;
	bool m_reverse;
	double m_upperLim;
	double m_lowerLim;
	bool m_ignoreHoldUpper;
	bool m_ignoreHoldLower;
};