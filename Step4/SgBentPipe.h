#pragma once
#include "sgobject.h"
#include "SgMesh.h"
#include "SgPtr.h"
#include "graphics\GrTransform.h"

class CSgBentPipe :
	public CSgObject
{
public:
	CSgBentPipe(void);
	~CSgBentPipe(void);
	
    //void SetMesh(CSgMesh *mesh) {m_mesh = mesh;}
	void SetMesh(CSgMesh* mesh){m_mesh = mesh;}
    void SetLength(double l) {m_length = l;}
	void SetDiameterEnd(double d){m_diamEnd = d;}
    void SetDiameter(double d) {m_diameter = d;}
    void SetStepsLength(int d) {m_steps1 = d;}
    void SetStepsAround(int d) {m_steps2 = d;}

    void TransformAt(int slice, const CGrTransform &rot);

    void Create();

	void Render();
private:
    CSgPtr<CSgMesh>   m_mesh;

    double  m_length;       // Total length
    double  m_diameter;     // Cylinder diameter
	double	m_diamEnd;

    int     m_steps1;       // Number of steps along the length
    int     m_steps2;       // Number of steps around the diameter
};

