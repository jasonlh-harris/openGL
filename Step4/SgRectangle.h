#pragma once
#include "SgMesh.h"
#include "SgPolygon.h"

class CSgRectangle:
		public CSgObject
{
public:
	CSgRectangle(void);
	~CSgRectangle(void);
	enum RenderType{MESH, POLYGON};
	CSgRectangle(double x, double y, double z, double l, double d, double h);
	void Render(void);
	void SetBackLeft(double x, double y, double z);
	void SetDepth(double d);
	void SetLength(double l);
	void setHeight(double h);
	void SetBackLeft(double x, double y, double z, double l, double d, double h);
	void SetRenderType(RenderType t);

private:
	RenderType m_type;
	double m_depth, m_length, m_height, m_x, m_y, m_z;
	CSgMesh m_mesh;
	void CreateMesh();
};

