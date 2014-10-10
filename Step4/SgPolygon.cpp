#include "StdAfx.h"
#include "SgPolygon.h"

CSgPolygon::CSgPolygon(void)
{
	//m_texture=NULL;
}

CSgPolygon::~CSgPolygon(void)
{
}
CSgPolygon::CSgPolygon(double *x, double *y, double *z){
	AddVertices(x,y,z,0);
}
void CSgPolygon::AddVertex3d(double x, double y, double z)
{
	m_vertices.push_back(CGrVector(x,y,z));
}

void CSgPolygon::AddVertex3dv(double* p)
{
	m_vertices.push_back(CGrVector(p[0], p[1], p[2]));
}

void CSgPolygon::AddVertices(double* a, double* b, double* c, double* d)
{
	m_vertices.push_back(CGrVector(a[0], a[1], a[2]));
	m_vertices.push_back(CGrVector(b[0], b[1], b[2]));
	m_vertices.push_back(CGrVector(c[0], c[1], c[2]));
	if(d)
		m_vertices.push_back(CGrVector(d[0], d[1], d[2]));
}

void CSgPolygon::Render()
{
	std::vector<CGrVector>::iterator n=m_normals.begin();
	std::vector<CGrVector>::iterator t=m_tvertices.begin();
	//if(m_texture)
	//{
	//	glEnable(GL_TEXTURE_2D);
	//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//	m_texture->Render();
	//}
	glBegin(GL_POLYGON);
	for(std::vector<CGrVector>::iterator i = m_vertices.begin(); i!=m_vertices.end(); i++){
		        // If we have an available normal, use it:
        if(n != m_normals.end())
        {
            glNormal3dv(*n);
            n++;
        }

        // If we have an available texture coordinate, use it:
        if(t != m_tvertices.end())
        {
            glTexCoord2dv(*t);
            t++;
        }

		i->glVertex();
	}
	glEnd();
}
