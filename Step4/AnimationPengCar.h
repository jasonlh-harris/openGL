#pragma once
#include "animationtranslate.h"


class CAnimationPengCar :
	public CAnimationTranslate
{
public:
	CAnimationPengCar(void);
	~CAnimationPengCar(void);
	void Update();

private:
	double m_previousX;
	int m_time;
};

