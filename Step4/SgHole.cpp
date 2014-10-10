#include "stdafx.h"
#include "SgHole.h"
#include "graphics/GrVector.h"
#include "SgComposite.h"

const double PI = 3.1415926535897932384626433832795;

CSgHole::CSgHole(double x, double y, double z, double d)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_diameter = d;
}


CSgHole::~CSgHole(void)
{
}

void CSgHole::Render()
{
	Hole(m_x, m_y, m_z, m_diameter);

}

void CSgHole::Hole(double p_x, double p_y, double p_z, double p_diameter)
{
    double radius = p_diameter / 2.;

    glPushMatrix();
    glTranslated(p_x, p_y, p_z);

    int N = 32;
    for(int r=0;  r<N/4;  r++)
    {
        double sr1 = radius * -sin(double(r) / double(N) * 2. * PI);
        double cr1 = radius * cos(double(r) / double(N) * 2. * PI);
        double sr2 = radius * -sin(double(r+1) / double(N) * 2. * PI);
        double cr2 = radius * cos(double(r+1) / double(N) * 2. * PI);

        glBegin(GL_TRIANGLES);
        glNormal3d(0, 1, 0);

        glVertex3d(radius, 0, -radius);
        glVertex3d(cr2, 0, sr2);
        glVertex3d(cr1, 0, sr1);

        glVertex3d(-radius, 0, -radius);
        glVertex3d(-cr1, 0, sr1);
        glVertex3d(-cr2, 0, sr2);

        glVertex3d(-radius, 0, radius);
        glVertex3d(-cr2, 0, -sr2);
        glVertex3d(-cr1, 0, -sr1);

        glVertex3d(radius, 0, radius);
        glVertex3d(cr1, 0, -sr1);
        glVertex3d(cr2, 0, -sr2);

        glEnd();

    }

    glPopMatrix();
}