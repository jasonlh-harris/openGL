#pragma once
#include "sgobject.h"
class CSgPartSegment :
	public CSgObject
{
public:
	CSgPartSegment(void);
	~CSgPartSegment(void);

	void Render(void);
	void SetProperties(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2, int n);
	void DrawSegmentTextured(double x1, double y1, double nx1, double ny1, double x2, double y2, double nx2, double ny2,double t1, double t2);
	void DrawPartSegment(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2, int n);

private:
	//double m_Height;
	//double m_Radius;

	double m_vx1;
	double m_vy1;
	double m_x1n;
	double m_y1n;
	double m_vx2;
	double m_vy2;
	double m_x2n;
	double m_y2n;

	double m_num;
};



