#include "stdafx.h"
#include "SgRectangle.h"


CSgRectangle::CSgRectangle(void)
{
	m_type = MESH;
}

CSgRectangle::CSgRectangle(double x, double y, double z, double l, double d, double h)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_length = l;
	m_depth = d;
	m_height = h;
	m_type = MESH;
}
CSgRectangle::~CSgRectangle(void)
{
}
void CSgRectangle::Render(void)
{
	switch(m_type)
	{
	case MESH:
		CreateMesh();
		m_mesh.Render();
		break;
	case POLYGON:
		break;

	}
}
void CSgRectangle::SetBackLeft(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}
void CSgRectangle::SetDepth(double d)
{
	m_depth = d;
}
void CSgRectangle::SetBackLeft(double x, double y, double z, double l, double d, double h)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_length = l;
	m_depth = d;
	m_height = h;
}
void CSgRectangle::SetRenderType(RenderType t)
{
	m_type = t;
}

void CSgRectangle::CreateMesh(void)
{
			double v[8][4] = {{m_x, m_y, m_z, 1}, {m_x+m_length, m_y, m_z, 1}, {m_x + m_length, m_y+m_height, m_z, 1}, {m_x, m_y+m_height, m_z, 1}, 
						{m_x, m_y, m_z - m_depth, 1}, {m_x+m_length, m_y, m_z - m_depth, 1}, {m_x+m_length, m_y + m_height, m_z - m_depth, 1}, {m_x, m_y + m_height, m_z - m_depth, 1}};
			double n[6][4] = {{0, 0, 1, 0}, {1, 0, 0, 0}, {0, 0, -1, 0}, 
						{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, -1, 0, 0}};

			for(int i=0;  i<8;  i++)
				m_mesh.AddVertex(v[i]);

			for(int i=0;  i<6;  i++)
				m_mesh.AddNormal(n[i]);

			m_mesh.AddSelfTexturedQuad(0, 1, 2, 3, 0);
			m_mesh.AddSelfTexturedQuad(1, 5, 6, 2, 1);
			m_mesh.AddSelfTexturedQuad(5, 4, 7, 6, 2);
			m_mesh.AddSelfTexturedQuad(4, 0, 3, 7, 3);
			m_mesh.AddSelfTexturedQuad(3, 2, 6, 7, 4);
			m_mesh.AddSelfTexturedQuad(0, 4, 5, 1, 5);
}