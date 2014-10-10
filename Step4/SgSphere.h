#pragma once
#include "sgobject.h"
#include "graphics/GrVector.h"
//#include "SgTexture.h"
#include <vector>
class CSgSphere :
	public CSgObject
{
public:
	CSgSphere(void);
	virtual ~CSgSphere(void);

	void SphereFace(int p_recurse, double p_radius, double *a, double *b, double *c);
	virtual void Render(void);

	double getRadius(){return m_radius;}
	void setRadius(double rad){m_radius = rad;}

	int getRecurse(){return m_recurse;}
	void setRecurse(int recurse){m_recurse = recurse;}

private:
	double m_radius;
	int m_recurse;
};

