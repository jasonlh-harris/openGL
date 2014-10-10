#include "stdafx.h"
#include "SgAnimationRotateWait.h"


CSgAnimationRotateWait::CSgAnimationRotateWait(void)
{
	m_reverse = false;
	m_upperLim = -1;
	m_lowerLim = -1;
	m_holdTime = 0;
	m_ignoreHoldUpper = false;
	m_ignoreHoldLower = false;
}


CSgAnimationRotateWait::~CSgAnimationRotateWait(void)
{
}

void CSgAnimationRotateWait::Update(void)
{
	if(m_holdTime == 0)
	{
		double prevAngle = m_node->GetAngle();
		double newAngle;
		if(!m_reverse)
			newAngle = prevAngle + m_rate;
		else
			newAngle = prevAngle - m_rate;
		m_node->SetAngle(newAngle);

		if(newAngle >= m_upperLim)
		{
			if(!m_ignoreHoldUpper)m_holdTime=10;
			SwitchReverse();
		}
		if(newAngle <= m_lowerLim)
		{
			if(!m_ignoreHoldLower)m_holdTime=10;
			SwitchReverse();
		}
	}
	else
		m_holdTime--;
}