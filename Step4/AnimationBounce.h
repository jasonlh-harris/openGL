#pragma once
#include "animationtranslate.h"
class CAnimationBounce :
	public CAnimationTranslate
{
public:
	CAnimationBounce(void);
	~CAnimationBounce(void);
	void Update();

private:
	double m_previousY;
	int m_time;
};

