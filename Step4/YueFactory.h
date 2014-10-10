#pragma once
#include "scenefactory.h"
#include "SgFactory.h"
class CYueFactory :
	public CSgFactory
{
public:
	CYueFactory(void);
	~CYueFactory(void);
	void Create(CSgComposite *root);

	void CreateDorm(CSgComposite *parent);
  
  	void CreateBed(CSgComposite *parent);
	
	void BedFrame(CSgComposite *parent);

	void DrawSegment(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2);

	void UnmadeBed(CSgComposite *parent);

	void MadeBed(CSgComposite *parent);

	void Pillow(CSgComposite *parent);

	void CreateMadeBed(CSgComposite *parent);

	void CreateUnmadeBed(CSgComposite *parent);

	void CreateHoop(CSgComposite *parent);

	void HoopBase(CSgComposite *parent);

	void Rebound(CSgComposite *parent);

	void Rim(CSgComposite *parent);

	void Ball(CSgComposite *parent);
};

