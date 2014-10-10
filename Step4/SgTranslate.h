#pragma once
//#include "sgobject.h"
#include "graphics/GrVector.h"
#include "SgComposite.h"

class CSgTranslate :
	public CSgComposite
{
public:
	CSgTranslate(void);
	~CSgTranslate(void);
	CSgTranslate(const CGrVector &v);
	//CSgTranslate(const CGrVector &v, CSgObject *p_child);
	CSgTranslate(double x, double y, double z);
	//CSgTranslate(float x, float y, float z, CSgObject *p_child);
	

	void Render(void);
	void SetProperties(double x, double y, double z){m_vector.X(x); m_vector.Y(y); m_vector.Z(z);}
	void SetX(double x){m_vector.X(x);}
	void SetY(double y){m_vector.Y(y);}
	void SetZ(double z){m_vector.Z(z);}
	double GetX(){return (double) m_vector.X();}
	double GetY(){return (double) m_vector.Y();}
	double GetZ(){return (double) m_vector.Z();}
	CGrVector GetTranslation(){return m_vector;}
	
private:
	CGrVector m_vector;


};

