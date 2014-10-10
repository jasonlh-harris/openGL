#include "stdafx.h"
#include "AnimationPengCar.h"

const double PI = 3.1415926535897932384626433832795;

CAnimationPengCar::CAnimationPengCar(void)
{
	m_time = 0;
	m_previousX = 0;
}


CAnimationPengCar::~CAnimationPengCar(void)
{
}

void CAnimationPengCar::Update(){
	m_time++;
	m_time=m_time%60;
	m_previousX = m_node->GetX();
	//m_PreZ = m_node->GetZ();

	if(m_time<30)
	{
		m_node->SetX(m_previousX+0.06);
	}
	else if(m_time<60)
	{
		m_node->SetX(m_previousX-0.06);
	}

}