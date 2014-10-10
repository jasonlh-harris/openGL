#pragma once
#include "sgobject.h"
#include "SgPtr.h"
#include "SgTexture.h"
#include "SgMesh.h"
class CSgCD :
	public CSgObject
{
public:
	CSgCD(void);
	~CSgCD(void);

	void Render();
	void setVals(const double innerDiam,const double outerDiam,const double thickness);

private:
	CSgPtr<CSgMesh> m_mesh;
	void MakeMe();
	double _innerDiam;
	double _outerDiam;
	double _Thickness;
	double PI;
};

