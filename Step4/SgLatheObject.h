#pragma once
#include "sgcomposite.h"
#include "graphics/GrVector.h"
#include <vector>
class CSgLatheObject :
	public CSgObject
{
public:
	CSgLatheObject(void);
	~CSgLatheObject(void);
	void AddSegment(double x1, double y1, double nx1, double ny1,
				double x2, double y2, double nx2, double ny2,
				double t1 = 0, double t2 =0);
	void Render();

private:
	struct SegInfo{
		double x1;
		double x2;
		double nx1;
		double nx2;
		double y1;
		double y2;
		double ny1;
		double ny2;
		double t1;
		double t2;

	};
	std::vector<SegInfo> SegmentList;

	double PI;

	void DrawSegment(SegInfo theSegment);


};

