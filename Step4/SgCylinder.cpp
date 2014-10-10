#include "stdafx.h"
#include "SgCylinder.h"
#include "graphics/GrVector.h"
#include "SgComposite.h"



const double PI = 3.1415926535897932384626433832795;



CSgCylinder::CSgCylinder(void)
{
}


CSgCylinder::~CSgCylinder(void)
{
}


void CSgCylinder::SetProperties(double height, double radius)
{
	m_Height = height;
	m_Radius = radius;
}

void CSgCylinder::Render(void)
{
	//top
	DrawSegment(m_Radius, m_Height,      // First point x,y (z is zero)
			0., 1.,                 // First point normal x,y (z is zero)
			0., m_Height,            // Second point x,y
			0., 1.);                // Second point normal x,y}

	//outside
		DrawSegment(m_Radius, 0,      // First point x,y (z is zero)
			1., 0.,                 // First point normal x,y (z is zero)
			m_Radius, m_Height,            // Second point x,y
			1., 0.);                // Second point normal x,y}

	//buttom
	DrawSegment(0, 0.,      // First point x,y (z is zero)
			0., -1.,                 // First point normal x,y (z is zero)
			m_Radius, 0.,            // Second point x,y
			0., -1.);                // Second point normal x,y

}


//void CSgCylinder::DrawSegmentTextured(double x1, double y1, double nx1, double ny1, 
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

void CSgCylinder::DrawSegment(double x1, double y1, double nx1, double ny1, 
                        double x2, double y2, double nx2, double ny2)
{
    // We'll do 32 segments
    const int N = 32;
    double rs = (2*PI) / N;    // 2 * PI / N
    double r1 = 0;          // The first angle
    double r2 = r1+rs;         // The second angle

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

