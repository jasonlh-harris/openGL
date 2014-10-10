#pragma once
#include "sgobject.h"
class CSgHole :
	public CSgObject
{
public:
	CSgHole(double, double, double, double);
	~CSgHole(void);
	void Render();
	void Hole(double p_x, double p_y, double p_z, double p_diameter);


private:
	double m_diameter;
	double m_x;
	double m_y;
	double m_z;
};

