#pragma once
#include "sgfactory.h"
#include "SgPolygon.h"
#include "SgRectangle.h"
#include "SgMesh.h"
class CSgClosetFactory :
	public CSgFactory
{
public:
	CSgClosetFactory(void);
	~CSgClosetFactory(void);
	void SwitchState(void){state = !state;}
	void SetScale(double s){scale = s;}
	void Create(CSgComposite*);
	CSgObject* Create(void);
private:
	bool state;
	double scale;
	void CreateWall(CSgMesh*);
	void CreateShelf(CSgMesh*);
	void CreateClosetDoor(CSgMesh*, double, double, double);
	void CreateClosetBottomPanel(CSgMesh*);
	void CreateClostBottomDrawer(CSgMesh*);
};

