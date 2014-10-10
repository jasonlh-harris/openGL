#include "stdafx.h"
#include "SgCD.h"


CSgCD::CSgCD(void)
{
	PI = 3.1415926535;
	m_mesh = new CSgMesh();
}


CSgCD::~CSgCD(void)
{
}


void CSgCD::Render()
{
	m_mesh->Render();
}

void CSgCD::setVals(double innerDiam, double outerDiam, double thickness)
{
	_innerDiam = innerDiam;
	_outerDiam = outerDiam;
	_Thickness = thickness;
	MakeMe();
}

void CSgCD::MakeMe()
{
    int N = 32;
    int v = 0;

    int sTopOuter = v;

    // Add top vertices
    for(int i=0;  i<=N;  i++, v++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddVertex(cos(angle) * _outerDiam / 2, _Thickness, 
                         -sin(angle) * _outerDiam / 2);
    }

    int sTopInner = v;

    for(int i=0;  i<=N;  i++, v++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddVertex(cos(angle) * _innerDiam / 2, _Thickness, 
                         -sin(angle) * _innerDiam / 2);
    }

    int sBotOuter = v;

    // Add top vertices
    for(int i=0;  i<=N;  i++, v++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddVertex(cos(angle) * _outerDiam / 2, 0, 
                         -sin(angle) * _outerDiam / 2);
    }

    int sBotInner = v;

    for(int i=0;  i<=N;  i++, v++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddVertex(cos(angle) * _innerDiam / 2, 0, 
                         -sin(angle) * _innerDiam / 2);
    }


    m_mesh->AddNormal(0, 1, 0);
    m_mesh->AddNormal(0, -1, 0);
    int sNormals = 2;
    for(int i=0;  i<=N;  i++, v++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddNormal(cos(angle), 0, -sin(angle));
        m_mesh->AddNormal(-cos(angle), 0, sin(angle));
    }

    // Create texture coordinates for the top
    v = 0;
    
    for(int i=0;  i<=N;  i++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddTexCoord(0.5 + 0.5 * cos(angle), 
                           0.5 + 0.5 * sin(angle));
        v++;

        double ratio = _innerDiam / _outerDiam;
        m_mesh->AddTexCoord(0.5 + 0.5 * cos(angle) * ratio, 
                           0.5 + 0.5 * sin(angle) * ratio);
        v++;

    }

    // Create texture coordinates for the bottom
    int bottomT = v;
    for(int i=0;  i<=N;  i++)
    {
        double angle = 2 * PI * i / N;
        m_mesh->AddTexCoord(0.5 + 0.5 * cos(angle), 
                           0.25 + 0.25 * sin(angle));
        v++;

        double ratio = _innerDiam / _outerDiam;
        m_mesh->AddTexCoord(0.5 + 0.5 * cos(angle) * ratio, 
                           0.25 + 0.25 * sin(angle) * ratio);
        v++;

    }

    // Add triangles
    for(int i=0;  i<N; i++)
    {
        // Top triangles
        m_mesh->AddTriangleVertex(sTopOuter + i, 0, i * 2);
        m_mesh->AddTriangleVertex(sTopOuter + i + 1, 0, i * 2 + 2);
        m_mesh->AddTriangleVertex(sTopInner + i, 0, i * 2 + 1);

        m_mesh->AddTriangleVertex(sTopOuter + i + 1, 0, i * 2 + 2);
        m_mesh->AddTriangleVertex(sTopInner + i + 1, 0, i * 2 + 3);
        m_mesh->AddTriangleVertex(sTopInner + i, 0, i * 2 + 1);

        // Bottom triangles
        m_mesh->AddTriangleVertex(sBotInner + i, 1, i * 2 + 1 + bottomT);
        m_mesh->AddTriangleVertex(sBotOuter + i + 1, 1, i * 2 + 2 + bottomT);
        m_mesh->AddTriangleVertex(sBotOuter + i, 1, i * 2 + bottomT);
        
        m_mesh->AddTriangleVertex(sBotInner + i, 1, i * 2 + 1 + bottomT);
        m_mesh->AddTriangleVertex(sBotInner + i + 1, 1, i * 2 + 3 + bottomT);
        m_mesh->AddTriangleVertex(sBotOuter + i + 1, 1, i * 2 + 2 + bottomT);

        // Outer edge
        m_mesh->AddTriangleVertex(sTopOuter + i, sNormals + i * 2, -1);
        m_mesh->AddTriangleVertex(sBotOuter + i, sNormals + i * 2, -1);
        m_mesh->AddTriangleVertex(sTopOuter + i + 1, sNormals + i * 2 + 2, -1);

        m_mesh->AddTriangleVertex(sBotOuter + i, sNormals + i * 2, -1);
        m_mesh->AddTriangleVertex(sBotOuter + i  + 1, sNormals + i * 2 + 2, -1);
        m_mesh->AddTriangleVertex(sTopOuter + i + 1, sNormals + i * 2 + 2, -1);

    }
	
}