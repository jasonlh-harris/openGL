#include "stdafx.h"
#include "SgRotateAroundPoint.h"


CSgRotateAroundPoint::CSgRotateAroundPoint(void)
{
	m_point = CGrVector(0, 0, 0);
	m_translation = CGrVector(0,0,0);
}


CSgRotateAroundPoint::~CSgRotateAroundPoint(void)
{
}

void CSgRotateAroundPoint::Render()
{
	glPushMatrix();
	glTranslated(m_translation.X(), m_translation.Y(), m_translation.Z());
	glTranslated(m_point.X(), m_point.Y(), m_point.Z());
	glRotated(m_angle, m_normal.X(), m_normal.Y(), m_normal.Z());
    glTranslated(-m_point.X(), -m_point.Y(), -m_point.Z());

	
	CSgComposite::Render();
	
	glPopMatrix();
}