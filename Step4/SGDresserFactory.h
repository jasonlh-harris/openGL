#pragma once
#include "sgfactory.h"
#include "SgMesh.h"
class CSGDresserFactory :
	public CSgFactory
{
public:
	CSGDresserFactory(void);
	~CSGDresserFactory(void);
	void Create(CSgComposite*);
	CSgObject* Create(void);
	void CreateDrawer(CSgComposite*, bool);
	void SetDifferent(bool setting){isDifferent = setting;}
private:
	double height;
	double width;
	double depth;
	double drawerWidth;
	double drawerHeight;
	double spacing;
	double spacingx;
	double drawerThickness;
	int drawerNum;
	int vertexNum;
	bool isDifferent;
};

