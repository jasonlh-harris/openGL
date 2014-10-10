#include "stdafx.h"
#include "SgTranslate.h"


CSgTranslate::CSgTranslate(void)
{
	m_vector = CGrVector();
}

CSgTranslate::CSgTranslate(double x, double y, double z)
{
	m_vector = CGrVector(x, y, z);
}

CSgTranslate::~CSgTranslate(void)
{
}


CSgTranslate::CSgTranslate(const CGrVector &v)
{
	glTranslated(v.X(),v.Y(),v.Z());
}

void CSgTranslate::Render(void)
{
	glPushMatrix();
	glTranslated(m_vector.X(), m_vector.Y(), m_vector.Z());

	CSgComposite::Render();
	
	glPopMatrix();
}

