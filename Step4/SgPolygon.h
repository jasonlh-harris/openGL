#pragma once
#include "sgobject.h"
#include "graphics/GrVector.h"
//#include "SgTexture.h"
#include <vector>
class CSgPolygon :
	public CSgObject
{
public:
	CSgPolygon(void);
	CSgPolygon(double *x, double *y, double *z);
	~CSgPolygon(void);
	void AddVertex3d(double x, double y, double z);
	void AddVertex3dv(double* p);
	void AddVertices(double* a, double* b, double* c, double* d=NULL);
	void AddNormal(const CGrVector &n) {m_normals.push_back(n);}
    void AddTexCoord(const CGrVector &t) {m_tvertices.push_back(t);}
	//void SetTexture(CSgPtr<CSgTexture> texture) {m_texture=texture;}
	virtual void Render();
private:
	std::vector<CGrVector> m_vertices;
	std::vector<CGrVector> m_tvertices;
	std::vector<CGrVector> m_normals;

};
