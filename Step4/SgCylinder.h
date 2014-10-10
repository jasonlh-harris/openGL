#pragma once
#include "sgobject.h"
class CSgCylinder :
	public CSgObject
{
public:
	CSgCylinder(void);
	~CSgCylinder(void);

	void Render(void);
	void SetProperties(double, double);
	void DrawSegmentTextured(double x1, double y1, double nx1, double ny1, double x2, double y2, double nx2, double ny2,double t1, double t2);
	void DrawSegment(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2);

private:
	double m_Height;
	double m_Radius;
};

