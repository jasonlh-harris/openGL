#include "stdafx.h"
#include "SgMesh.h"
#include <fstream>      // For input streams from files
#include <string>       // For the string type
#include <sstream>      // For streams from strings

using namespace std;

CSgMesh::CSgMesh(void)
{
	m_texture = NULL;
	m_selfTVertices.push_back(CGrVector(0,0));
	m_selfTVertices.push_back(CGrVector(1,0));
	m_selfTVertices.push_back(CGrVector(1,1));
	m_selfTVertices.push_back(CGrVector(0,1));
}


CSgMesh::~CSgMesh(void)
{
}

//
// Name :         CMesh::LoadOBJ()
// Description :  Load a file in OBJ format.
//
void CSgMesh::LoadOBJ(const char *filename)
{
    ifstream str(filename);
    if(!str)
    {
        AfxMessageBox(L"File not found");
        return;
    }

    string line;
    while(getline(str, line))
    {
        istringstream lstr(line);

        string code;
        lstr >> code;
        if(code == "v") 
        {
            double x, y, z;
            lstr >> x >> y >> z;
            AddVertex(CGrVector(x, y, z, 1));
        }
        else if(code == "vn")
        {
			double x, y, z;
			lstr >> x >> y >> z;
			AddNormal(CGrVector(x, y, z, 0));
        }
        else if(code == "vt")
        {
			double s, t;
			lstr >> s >> t;
			AddTexCoord(CGrVector(s, t, 0, 1));
        }
        else if(code == "f")
        {
			for(int i=0;  i<3;  i++)
            {
                char slash;
                int v, t, n;
                lstr >> v >> slash >> t >> slash >> n;
                AddTriangleVertex(v-1, n-1, t-1);
            }
        }

    }

}

//
// Name :         CMesh::ComputeSmoothNormals()
// Description :  Compute a normal for each vertex that is the
//                average of the surface normals incident on the 
//                vertex.
//
void CSgMesh::ComputeSmoothNormals()
{
	m_normals.resize(m_vertices.size());
    for(unsigned int i=0;  i<m_vertices.size();  i++)
		m_normals[i] = CGrVector(0, 0, 0, 0);

	for(PTV v=m_triangles.begin();  v!=m_triangles.end();  )
    {
        // Collect up the vertices of a triangle...
        int a = v->v;
        v++;
        int b = v->v;
        v++;
        int c = v->v;
        v++;

        // Surface normal
        CGrVector normal = Cross(m_vertices[b] - m_vertices[a], 
                                 m_vertices[c] - m_vertices[a]);
        normal.Normalize3();

        // Add to the incident vertices normals
        m_normals[a] += normal;
        m_normals[b] += normal;
        m_normals[c] += normal;
	}
	    // Normalize the normals
    for(unsigned int i=0;  i<m_vertices.size();  i++)
        m_normals[i].Normalize3();
}

//
// Name :         CMesh::AddQuad()
// Description :  Add a quadrangle to the triangle mesh with no 
//                assumption of flatness.
//
void CSgMesh::AddQuad(int a, int b, int c, int d)
{
    // First triangle
    AddTriangleVertex(a, a, -1);
    AddTriangleVertex(b, b, -1);
    AddTriangleVertex(c, c, -1);

    // Second triangle
    AddTriangleVertex(a, a, -1);
    AddTriangleVertex(c, c, -1);
    AddTriangleVertex(d, d, -1);
}
//
// Name :         CMesh::AddFlatQuad()
// Description :  Add a quadrangle to the triangle mesh.
//
void CSgMesh::AddFlatQuad(int a, int b, int c, int d, int n)
{

    // First triangle
    AddTriangleVertex(a, n, -1);
    AddTriangleVertex(b, n, -1);
    AddTriangleVertex(c, n, -1);

    // Second triangle
    AddTriangleVertex(a, n, -1);
    AddTriangleVertex(c, n, -1);
    AddTriangleVertex(d, n, -1);
}

void CSgMesh::AddSelfTexturedQuad(int a, int b, int c, int d, int n)
{/*
	double MaxX = m_vertices[a].X();
	double MinX = m_vertices[a].X();
	double MaxY = m_vertices[a].Y();
	double MinY = m_vertices[a].Y();
	CGrVector newVecList[4] = {m_vertices[a],
								m_vertices[b],
								m_vertices[c],
								m_vertices[d]};
	int intList[4] = {a,b,c,d};
	for(int i = 0; i < 4; i++)
	{
		if(newVecList[i].X() > MaxX)
			MaxX = newVecList[i].X();
		if(newVecList[i].X() < MinX)
			MinX = newVecList[i].X();
		if(newVecList[i].Y() > MaxY)
			MaxY=newVecList[i].Y();
		if(newVecList[i].Y() < MinY)
			MinY = newVecList[i].Y();
	}
	double width = MaxX - MinX;
	double height = MaxY - MinY;

	bool swap = true;
	int j = 0;
	while(swap)
	{
		swap = false;
		j++;
		for(int i = 0; i < 4 - j; i++)
		{
			if(m_vertices[i].X() > m_vertices[i+1].X())
			{
				CGrVector temp = m_vertices[i];
				m_vertices[i]= m_vertices[i+1];
				m_vertices[i+1] = temp;
				int tempInt = intList[i];
				intList[i]=intList[i+1];
				intList[i+1] = tempInt;
			}
		}
	}
	if(m_vertices[0].Y() > m_vertices[1].Y())
	{
		CGrVector temp = m_vertices[0];
		m_vertices[0]= m_vertices[1];
		m_vertices[1] = temp;
				int tempInt = intList[0];
				intList[0]=intList[1];
				intList[1] = tempInt;
	}
	if(m_vertices[2].Y() > m_vertices[3].Y())
	{
		CGrVector temp = m_vertices[2];
		m_vertices[2]= m_vertices[3];
		m_vertices[3] = temp;
				int tempInt = intList[2];
				intList[2]=intList[3];
				intList[3] = tempInt;
	}
	
	m_selfTVertices.push_back(CGrVector((newVecList[0].X() - MinX) / width,(newVecList[0].Y() - MinY) / height)); //bottom left 0 (-4
	m_selfTVertices.push_back(CGrVector((newVecList[1].X() - MinX) / width,(newVecList[1].Y() - MinY) / height));  // upper left verticy texture map 1 -3
	m_selfTVertices.push_back(CGrVector((newVecList[2].X() - MinX) / width,(newVecList[2].Y() - MinY) / height)); //bottom right 2 -2 
	m_selfTVertices.push_back(CGrVector((newVecList[3].X() - MinX) / width,(newVecList[3].Y() - MinY) / height)); // upper right 3 -1

	int tVertsLength = m_selfTVertices.size();

	AddSelfTexturedTriangleVertex(intList[0], n, tVertsLength - 4); 
	AddSelfTexturedTriangleVertex(intList[2], n, tVertsLength - 2); 
	AddSelfTexturedTriangleVertex(intList[3], n, tVertsLength - 1); 

	AddSelfTexturedTriangleVertex(intList[0], n, tVertsLength - 4);
	AddSelfTexturedTriangleVertex(intList[3], n, tVertsLength - 1);
	AddSelfTexturedTriangleVertex(intList[2], n, tVertsLength - 3);


	*/
	// First triangle
    AddSelfTexturedTriangleVertex(a, n, 0); //0
    AddSelfTexturedTriangleVertex(b, n, 1); //1
    AddSelfTexturedTriangleVertex(c, n, 2); //2

    // Second triangle
    AddSelfTexturedTriangleVertex(a, n, 0); //0
    AddSelfTexturedTriangleVertex(c, n, 2); //2
    AddSelfTexturedTriangleVertex(d, n, 3); //3
}

void CSgMesh::AddSelfTexturedTriangleVertex(int v, int n, int t)
{
	STV tv;
    tv.v = v;
    tv.n = n;
    tv.t = t;
    m_striangles.push_back(tv);
}
void CSgMesh::Render(void)
{
	glBegin(GL_TRIANGLES);
    for(PTV v=m_triangles.begin();  v!=m_triangles.end();  v++)
    {
		if(v->t!=-1)
			glTexCoord2dv(m_tvertices[v->t]);
        glNormal3dv(m_normals[v->n]);
        glVertex3dv(m_vertices[v->v]);
    }
	for(SPTV v=m_striangles.begin();  v!=m_striangles.end();  v++)
    {
		if(v->t!=-1)
			glTexCoord2dv(m_selfTVertices[v->t]);
        glNormal3dv(m_normals[v->n]);
        glVertex3dv(m_vertices[v->v]);
    }
    glEnd();
	/*
	if(m_texture != NULL)
    {
        glEnable(GL_TEXTURE_2D);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D, m_texture->TexName()); 
    }
	glBegin(GL_TRIANGLES);
    for(PTV v=m_triangles.begin();  v!=m_triangles.end();  v++)
    {
		if(m_texture != NULL)
			glTexCoord2dv(m_tvertices[v->t]);
        glNormal3dv(m_normals[v->n]);
        glVertex3dv(m_vertices[v->v]);
    }

    glEnd();
	glDisable(GL_TEXTURE_2D);*/
}

void CSgMesh::AddTriangleVertex(int v, int n, int t)
{
    TV tv;
    tv.v = v;
    tv.n = n;
    tv.t = t;
    m_triangles.push_back(tv);
}

