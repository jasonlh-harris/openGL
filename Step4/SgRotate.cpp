#include "stdafx.h"
#include "SgRotate.h"


CSgRotate::CSgRotate(void)
{
}


CSgRotate::~CSgRotate(void)
{
}

CSgRotate::CSgRotate(const CGrVector &v)
{
	m_x = v.X();
	m_y = v.Y();
	m_z = v.Z();
}

CSgRotate::CSgRotate(float a, const CGrVector &v)
{
	m_AngleDegrees = a;
	m_x = v.X();
	m_y = v.Y();
	m_z = v.Z();
}

CSgRotate::CSgRotate(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

CSgRotate::CSgRotate(float a, float x, float y, float z)
{
	m_AngleDegrees = a;
	m_x = x;
	m_y = y;
	m_z = z;
}

void CSgRotate::Render(void)
{
	glRotated(m_AngleDegrees, m_x, m_y, m_z);
}