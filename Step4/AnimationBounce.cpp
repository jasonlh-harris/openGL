#include "stdafx.h"
#include "AnimationBounce.h"


CAnimationBounce::CAnimationBounce(void)
{
	m_time = 0;
	m_previousY = 0;
}


CAnimationBounce::~CAnimationBounce(void)
{
}

void CAnimationBounce::Update(){
	m_time++;
	m_time=m_time%60;
	m_previousY = m_node->GetY();
	//m_PreZ = m_node->GetZ();

	if(m_time<30)
	{
		m_node->SetY(m_previousY+0.2);
	}
	else if(m_time<60)
	{
		m_node->SetY(m_previousY-0.2);
	}

}