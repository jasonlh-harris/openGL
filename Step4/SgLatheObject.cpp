#include "stdafx.h"
#include "SgLatheObject.h"


CSgLatheObject::CSgLatheObject(void)
{
	 PI = 3.1415926535;
}


CSgLatheObject::~CSgLatheObject(void)
{
}

void CSgLatheObject::Render()
{
	std::vector<SegInfo>::iterator it;
	for(it = SegmentList.begin(); it!=SegmentList.end(); ++it)
	{
		DrawSegment(*it);
	}
}

void CSgLatheObject::AddSegment(double x1, double y1, double nx1, double ny1,
								double x2, double y2, double nx2, double ny2,
								double t1, double t2)
{
	SegInfo tempSegment;
	tempSegment.x1 = x1;
	tempSegment.x2 = x2;
	tempSegment.nx1 = nx1;
	tempSegment.nx2 = nx2;
	tempSegment.y1 = y1;
	tempSegment.y2 = y2;
	tempSegment.ny1 = ny1;
	tempSegment.ny2 = ny2;
	tempSegment.t1 = t1;
	tempSegment.t2 = t2;
	SegmentList.push_back(tempSegment);
}


void CSgLatheObject::DrawSegment(SegInfo theSegment)
{
	double x1 = theSegment.x1;
	double x2 = theSegment.x2;
	double nx1 = theSegment.nx1;
	double nx2 = theSegment.nx2;
	double y1 = theSegment.y1;
	double y2 = theSegment.y2;
	double ny1 = theSegment.ny1;
	double ny2 = theSegment.ny2;
	double t1 = theSegment.t1;
	double t2 = theSegment.t2;

    // We'll do 32 segments
    const int N = 22;
    double rs = PI * 2 / N;    // 2 * PI / N
    double r1 = 0;          // The first angle
    double r2 = rs;         // The second angle

    double sin1 = sin(r1);
    double cos1 = cos(r1);
    double sin2, cos2;

    for(int i=0;  i<N;  i++, r1+=rs, r2+=rs, sin1=sin2, cos1=cos2)
    {
        // Compute the other angles
        sin2 = sin(r2);
        cos2 = cos(r2);

        // The four points and four normals we'll need
        double p1[3] = {x1 * cos1, y1, x1 * -sin1}; 
        double n1[3] = {nx1 * cos1, ny1, nx1 * -sin1}; 
        double p2[3] = {x1 * cos2, y1, x1 * -sin2}; 
        double n2[3] = {nx1 * cos2, ny1, nx1 * -sin2}; 
        double p3[3] = {x2 * cos2, y2, x2 * -sin2}; 
        double n3[3] = {nx2 * cos2, ny2, nx2 * -sin2}; 
        double p4[3] = {x2 * cos1, y2, x2 * -sin1}; 
        double n4[3] = {nx2 * cos1, ny2, nx2 * -sin1}; 

        glBegin(GL_QUADS);
            glNormal3dv(n1);
            glTexCoord2d(double(i) / N, t1);
            glVertex3dv(p1);
            glNormal3dv(n2);
            glTexCoord2d(double(i+1) / N, t1);
            glVertex3dv(p2);
            glNormal3dv(n3);
            glTexCoord2d(double(i+1) / N, t2);
            glVertex3dv(p3);
            glNormal3dv(n4);
            glTexCoord2d(double(i) / N, t2);
            glVertex3dv(p4);
        glEnd();
    }
}
