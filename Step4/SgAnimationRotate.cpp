#include "stdafx.h"
#include "SgAnimationRotate.h"


CSgAnimationRotate::CSgAnimationRotate(void)
{
}


CSgAnimationRotate::~CSgAnimationRotate(void)
{
}

void CSgAnimationRotate::Update(void)
{

	double prevAngle = m_node->GetAngle();
	double newAngle = prevAngle + m_rate;
	m_node->SetAngle(newAngle);

}