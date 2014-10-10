#include "stdafx.h"
#include "SgPartSegment.h"
#include "graphics/GrVector.h"
#include "SgComposite.h"



const double PI = 3.1415926535897932384626433832795;



CSgPartSegment::CSgPartSegment(void)
{
}


CSgPartSegment::~CSgPartSegment(void)
{
}


void CSgPartSegment::SetProperties(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2, int n)
{
	m_vx1 = x1;
	m_vy1 = y1;
	m_x1n = nx1;
	m_y1n = ny1;
	m_vx2 = x2;
	m_vy2 = y2;
	m_x2n = nx2;
	m_y2n = ny2;

	m_num = n;
}

void CSgPartSegment::Render(void)
{

	//outside
	glPushMatrix();
		DrawPartSegment(m_vx1, m_vy1, m_x1n, m_y1n, m_vx2, m_vy2, m_x2n, m_y2n, m_num);                // Second point normal x,y}
	glPopMatrix();
}


//void CSgPartSegment::DrawSegmentTextured(double x1, double y1, double nx1, double ny1, 
//                        double x2, double y2, double nx2, double ny2,
//                        double t1, double t2)
//{
//    // We'll do 32 segments
//    const int N = 32;
//    double rs = (2*PI) / N;    // 2 * PI / N
//    double r1 = 0;          // The first angle
//    double r2 = rs;         // The second angle
//
//    double sin1 = sin(r1);
//    double cos1 = cos(r1);
//    double sin2, cos2;
//
//    for(int i=0;  i<N;  i++, r1+=rs, r2+=rs, sin1=sin2, cos1=cos2)
//    {
//        // Compute the other angles
//        sin2 = sin(r2);
//        cos2 = cos(r2);
//
//        // The four points and four normals we'll need
//        double p1[3] = {x1 * cos1, y1, x1 * -sin1}; 
//        double n1[3] = {nx1 * cos1, ny1, nx1 * -sin1}; 
//        double p2[3] = {x1 * cos2, y1, x1 * -sin2}; 
//        double n2[3] = {nx1 * cos2, ny1, nx1 * -sin2}; 
//        double p3[3] = {x2 * cos2, y2, x2 * -sin2}; 
//        double n3[3] = {nx2 * cos2, ny2, nx2 * -sin2}; 
//        double p4[3] = {x2 * cos1, y2, x2 * -sin1}; 
//        double n4[3] = {nx2 * cos1, ny2, nx2 * -sin1}; 
//
//        glBegin(GL_QUADS);
//            glNormal3dv(n1);
//            glTexCoord2d(double(i) / N, t1);
//            glVertex3dv(p1);
//            glNormal3dv(n2);
//            glTexCoord2d(double(i+1) / N, t1);
//            glVertex3dv(p2);
//            glNormal3dv(n3);
//            glTexCoord2d(double(i+1) / N, t2);
//            glVertex3dv(p3);
//            glNormal3dv(n4);
//            glTexCoord2d(double(i) / N, t2);
//            glVertex3dv(p4);
//        glEnd();
//    }
//
//}

void CSgPartSegment::DrawPartSegment(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2, int n)
{
    // We'll do 32 segments
    const int N = 32;
    double rs = (2*PI) / N;    // 2 * PI / N
    double r1 = 0;          // The first angle
    double r2 = r1+rs;         // The second angle

    double sin1 = sin(r1);
    double cos1 = cos(r1);
    double sin2, cos2;



    for(int i=0;  i<N-n;  i++, r1+=rs, r2+=rs, sin1=sin2, cos1=cos2)
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
            glVertex3dv(p1);
            glNormal3dv(n2);
            glVertex3dv(p2);
            glNormal3dv(n3);
            glVertex3dv(p3);
            glNormal3dv(n4);
            glVertex3dv(p4);
        glEnd();
    }
}

