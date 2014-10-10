#pragma once
#include "sgobject.h"
#include "graphics/GrVector.h"
#include "graphics/GrTexture.h"
#include "graphics\GrTransform.h"
#include <vector>

class CSgMesh :
	public CSgObject
{
public:
	CSgMesh(void);
	~CSgMesh(void);
	void AddVertex(const CGrVector &v) {m_vertices.push_back(v);}
	void AddVertex(double x, double y, double z) {AddVertex(CGrVector(x, y, z));}
    void AddNormal(const CGrVector &n) {m_normals.push_back(n);}
	void AddNormal(double x, double y, double z) {AddNormal(CGrVector(x, y, z, 0));}
	void AddSelfTexturedQuad(int a, int b, int c, int d, int n);
	void AddSelfTexturedTriangleVertex(int v, int n, int t);
    void AddTexCoord(const CGrVector &t) {m_tvertices.push_back(t);}
	void AddTexCoord(double x, double y) {AddTexCoord(CGrVector(x, y, 0));}
	void AddTriangleVertex(int v, int n, int t);
	void AddFlatQuad(int a, int b, int c, int d, int n);
	void AddQuad(int a, int b, int c, int d);
	void ComputeSmoothNormals();
	void LoadOBJ(const char *filename);
	void Render(void);
	void SetTexture(CGrTexture *texture) {m_texture = texture;}
    CGrTexture *GetTexture() {return m_texture;}
	int GetNumVertices() const {return (int)m_vertices.size();}
    CGrVector GetVertex(int i) {return m_vertices[i];}

    void TransformVertex(int i, const CGrTransform &transform) {m_vertices[i] = transform * m_vertices[i];}
    void TransformNormal(int i, const CGrTransform &transform) {m_normals[i] = transform * m_normals[i];}

private:
	std::vector<CGrVector> m_vertices;
    std::vector<CGrVector> m_normals;
    std::vector<CGrVector> m_tvertices;
	std::vector<CGrVector> m_selfTVertices;
	// A triangle vertex description
    struct TV
    {
        int     v;      // Vertex
        int     n;      // Normal
        int     t;      // Texture coordinate
    };
	struct STV
    {
        int     v;      // Vertex
        int     n;      // Normal
        int     t;      // Texture coordinate
    };
	typedef std::vector<TV> Triangles;
	typedef std::vector<STV> STriangles;
    typedef Triangles::iterator PTV;
	typedef STriangles::iterator SPTV;
    Triangles       m_triangles;
	STriangles m_striangles;
	CGrTexture   *m_texture;  // Texture to use for the fishy
};

