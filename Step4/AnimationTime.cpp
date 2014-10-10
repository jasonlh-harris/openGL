#include "stdafx.h"
#include "AnimationTime.h"


CAnimationTime::CAnimationTime(void)
{
}


CAnimationTime::~CAnimationTime(void)
{

}

void CAnimationTime::Update(void)
{
	for(std::vector< CSgPtr<CAnimation> >::iterator c = m_channels.begin(); c != m_channels.end(); c++)
	{
		(*c)->Update();
	}
}