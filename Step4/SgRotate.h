#pragma once
#include "sgobject.h"
#include "graphics/GrVector.h"
class CSgRotate :
	public CSgObject
{
public:
	CSgRotate(void);
	CSgRotate(const CGrVector &v);
	CSgRotate(float a, const CGrVector &v);
	//CSgRotate(const CGrVector &v, CSgObject *p_child);
	CSgRotate(float x, float y, float z);
	CSgRotate(float a, float x, float y, float z);
	void setAngle(double a){m_AngleDegrees = a;};
	//CSgRotate(float x, float y, float z, CSgObject *p_child);
	~CSgRotate(void);
	void Render();
private:
	double m_AngleDegrees, m_x, m_y, m_z;
};

