#include "stdafx.h"
#include "SgMaterial.h"
#include "graphics/GrVector.h"

using namespace std;
CSgMaterial::CSgMaterial(void)
{
	m_diffuseColor[0] = m_diffuseColor[1] = m_diffuseColor[2] = 0.8f;m_diffuseColor[3] = 1.0f;
	m_ambientColor[0] = m_ambientColor[1] = m_ambientColor[2] = 0.2f;m_ambientColor[3] = 0.2f;
	m_specularColor[0] = m_specularColor[1] = m_specularColor[2] = 0.0f; m_specularColor[3] = 1.0f;
	m_shininess[0] = 0;
}


CSgMaterial::~CSgMaterial(void)
{

}

void CSgMaterial::Render(void)
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuseColor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambientColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specularColor);
	glMaterialfv(GL_FRONT, GL_SHININESS, m_shininess);
	CSgComposite::Render();
}

void CSgMaterial::SetSpecularColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	m_specularColor[0] = red;
	m_specularColor[1] = green;
	m_specularColor[2] = blue;
	m_specularColor[3] = alpha;
}

void CSgMaterial::SetDiffuseColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	m_diffuseColor[0] = red;
	m_diffuseColor[1] = green;
	m_diffuseColor[2] = blue;
	m_diffuseColor[3] = alpha;
}

void CSgMaterial::SetAmbientColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	m_ambientColor[0] = red;
	m_ambientColor[1] = green;
	m_ambientColor[2] = blue;
	m_ambientColor[3] = alpha;
}