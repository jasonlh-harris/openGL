#pragma once
//#include "sgobject.h"
#include "graphics/GrVector.h"
#include "SgComposite.h"

class CSgRotateAroundPoint :
	public CSgComposite
{
public:
	CSgRotateAroundPoint(void);
	~CSgRotateAroundPoint(void);
	//Commands to set the point rotated around
	void SetPoint(double *p);
	void SetPoint(double x, double y, double z) {m_point = CGrVector(x,y,z);};
	void SetPoint(const CGrVector v){m_point = v;}
	void SetAngle(double angle) {m_angle = angle;}
	void SetNormal(CGrVector normal) {m_normal = normal;}
	void SetNormal(double x, double y, double z) {m_normal = CGrVector(x,y,z);}
	void SetTranslation(const CGrVector &v){m_translation = v;};
	void SetTranslation(double x, double y, double z){SetTranslation(CGrVector(x,y,z));}
	void Render();
	//void AddChild(CSgObject* c);

	CGrVector GetPoint() {return m_point;}
	double GetAngle() {return m_angle;}
	CGrVector GetNormal() {return m_normal;}

private:
	double m_angle;
	CGrVector m_point;
	CGrVector m_translation;
	//CGrVector m_point;
	CGrVector m_normal;

};

