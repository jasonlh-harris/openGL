#include "stdafx.h"
#include "SgSphere.h"


CSgSphere::CSgSphere(void)
{
	m_radius = 1;
	m_recurse = 3;
}


CSgSphere::~CSgSphere(void)
{
}

inline void Normalize3(GLdouble *v)
{
   GLdouble len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] /= len;
   v[1] /= len;
   v[2] /= len;
}

void CSgSphere::SphereFace(int p_recurse, double p_radius, double *a, double *b, double *c)
{
{
    if(p_recurse > 1)
    {
       // Compute vectors halfway between the passed vectors 
       GLdouble d[3] = {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
       GLdouble e[3] = {b[0] + c[0], b[1] + c[1], b[2] + c[2]};
       GLdouble f[3] = {c[0] + a[0], c[1] + a[1], c[2] + a[2]};

       Normalize3(d);
       Normalize3(e);
       Normalize3(f);

       SphereFace(p_recurse-1, p_radius, a, d, f);
       SphereFace(p_recurse-1, p_radius, d, b, e);
       SphereFace(p_recurse-1, p_radius, f, e, c);
       SphereFace(p_recurse-1, p_radius, f, d, e);
    }
    else 
    {
       glBegin(GL_TRIANGLES);
          glNormal3dv(a);
          glVertex3d(a[0] * p_radius, a[1] * p_radius, a[2] * p_radius);
          glNormal3dv(b);
          glVertex3d(b[0] * p_radius, b[1] * p_radius, b[2] * p_radius);
          glNormal3dv(c);
          glVertex3d(c[0] * p_radius, c[1] * p_radius, c[2] * p_radius);
       glEnd();
    }
}
}

void CSgSphere::Render()
{
   GLdouble a[] = {1, 0, 0};
   GLdouble b[] = {0, 0, -1};
   GLdouble c[] = {-1, 0, 0};
   GLdouble d[] = {0, 0, 1};
   GLdouble e[] = {0, 1, 0};
   GLdouble f[] = {0, -1, 0};

   SphereFace(m_recurse, m_radius, d, a, e);
   SphereFace(m_recurse, m_radius, a, b, e);
   SphereFace(m_recurse, m_radius, b, c, e);
   SphereFace(m_recurse, m_radius, c, d, e);
   SphereFace(m_recurse, m_radius, a, d, f);
   SphereFace(m_recurse, m_radius, b, a, f);
   SphereFace(m_recurse, m_radius, c, b, f);
   SphereFace(m_recurse, m_radius, d, c, f);
}