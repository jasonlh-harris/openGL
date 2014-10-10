#include "stdafx.h"
#include "AnimationTranslate.h"


CAnimationTranslate::CAnimationTranslate(void)
{
}


CAnimationTranslate::~CAnimationTranslate(void)
{
}

void CAnimationTranslate::Update(void)
{
	m_node->SetProperties(
		m_node->GetX() + 1,
		m_node->GetY() + 1,
		m_node->GetZ() + 1);
}