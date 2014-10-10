#include "stdafx.h"
#include "SgBendyTube.h"

CSgBendyTube::CSgBendyTube(void)
{
    m_mesh = new CSgMesh();

    // Some arbitrary defaults
    m_length = 100;       // Total length
    m_diameter = 1;     // Cylinder diameter
	m_diamEnd = 10;

    m_steps1 = 50;       // Number of steps along the length
    m_steps2 = 5;       // Number of steps around the diameter
}


CSgBendyTube::~CSgBendyTube(void)
{
}

void CSgBendyTube::Render()
{
	m_mesh->Render();
}

void CSgBendyTube::Create()
{
    // 
    // Create all of the vertices for the cylinder
    //

    // Add a vertex and normal for the left end cap
    m_mesh->AddVertex(0, 0, 0);
    m_mesh->AddNormal(-1, 0, 0);

    // First, we step over the length
    for(int i=0;  i<=m_steps1;  i++)
    {
        // What is the X location for this slice?
        double x = m_length * double(i) / double(m_steps1);

        // Loop over the diameter here
        for(int j=0;  j<m_steps2;  j++)
        {
            // Angle around the radius
            double angle = double(j) / double(m_steps2) * 6.283185307179586476925286766559;

            // y and z for the normal
            double yn = cos(angle);
            double zn = sin(angle);

            // Add the vertex
            m_mesh->AddVertex(x, yn * (m_diameter + ((m_diamEnd - m_diameter) * i / m_steps1)) / 2, zn * (m_diameter + ((m_diamEnd - m_diameter) * i / m_steps1))/ 2);

            // Add the normal
            // Important: Must have a W value of zero since this is a vector
            // My AddNormal function does that...
            m_mesh->AddNormal(0, yn, zn);
        }
    }

    // Vertex and normal for the right end cap
    m_mesh->AddVertex(m_length, 0, 0);
    m_mesh->AddNormal(1, 0, 0);

    // Create the triangles for the body of the cylinder
    for(int i=0;  i<m_steps1;  i++)
    {
        // Starting vertex for this and the next slice
        int sThis = 1 + i * m_steps2;  // This slice
        int sNext = sThis + m_steps2;     // Next slice

        // Around the cylinder
        for(int j=0;  j<m_steps2;  j++)
        {
            // We need the four vertices for a quadrilateral
            int a0 = sThis + j;
            int b0 = sNext + j;
            int a1 = (j == m_steps2-1) ? sThis : a0 + 1;    // Handle wrapping back...
            int b1 = (j == m_steps2-1) ? sNext : b0 + 1;

            m_mesh->AddTriangleVertex(a0, a0, -1);
            m_mesh->AddTriangleVertex(a1, a1, -1);
            m_mesh->AddTriangleVertex(b0, b0, -1);

            m_mesh->AddTriangleVertex(a1, a1, -1);
            m_mesh->AddTriangleVertex(b1, b1, -1);
            m_mesh->AddTriangleVertex(b0, b0, -1);
        }

    }

    // Center on left end is
    int centerLeft = 0;

    // Left end starts at:
    int lStart = 1;

    // Right end starts at:
    int rStart = 1 + m_steps1 * m_steps2;

    // Center on right end is
    int centerRight = rStart + m_steps2;

    // And the two end caps
    for(int j=0;  j<m_steps2;  j++)
    {
        // Left end triangle
        int a0 = lStart + j;
        int a1 = (j == m_steps2 - 1) ? lStart : a0 + 1;
        m_mesh->AddTriangleVertex(centerLeft, centerLeft, -1);
        m_mesh->AddTriangleVertex(a1, centerLeft, -1);
        m_mesh->AddTriangleVertex(a0, centerLeft, -1);
        
        // Right end triangle
        int b0 = rStart + j;
        int b1 = (j == m_steps2 - 1) ? rStart : b0 + 1;
        m_mesh->AddTriangleVertex(centerRight, centerRight, -1);
        m_mesh->AddTriangleVertex(b0, centerRight, -1);
        m_mesh->AddTriangleVertex(b1, centerRight, -1);
    }

}


//! Bend the straw at a selected slice by a given transformation
void CSgBendyTube::TransformAt(int slice, const CGrTransform &rot)
{
    // Find the point at the center of the slice
    int start = 1 + slice * m_steps2;
    CGrVector center(0, 0, 0, 0);

    for(int j=0;  j<m_steps2;  j++)
    {
        center += m_mesh->GetVertex(start + j);
    }

    center /= m_steps2;

    // Rotate all vertices to the end around this point
    CGrTransform transform = CGrTransform::GetTranslate(center) * 
        rot *
        CGrTransform::GetTranslate(-center);

    for(int i=start;  i<m_mesh->GetNumVertices();  i++)
    {
        m_mesh->TransformVertex(i, transform);
        m_mesh->TransformNormal(i, transform);
    }


}


