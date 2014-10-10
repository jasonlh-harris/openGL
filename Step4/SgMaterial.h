#pragma once
#include "sgcomposite.h"
#include "SgPtr.h"
#include "SgObject.h"
#include "graphics/GrTexture.h"
#include <vector>
#include <list>
#include "graphics/OpenGLWnd.h"
class CSgMaterial :
	public CSgComposite
{
public:
	CSgMaterial(void);
	//CSgMaterial(GLenum, Glenum, const GLfloat);
	~CSgMaterial(void);
	//If we want to add this back in uncomment and add the getter and setters
	//Not really needed
	//void SetDiffuse(bool d){}
	//void SetSpecular(bool s){}
	//void SetShinine(bool s){}
	//void SetAmbient(bool a){}
	//void SetMaterial(GLenum, GLenum, const GLfloat);
	//void AddChild(CSgObject *child) { m_children.push_back(child);}
	void Render(void);
	void SetSpecularColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void SetDiffuseColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void SetAmbientColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	void SetShininess(GLfloat shine){m_shininess[0] = shine;}


private:
	//Commented out because currently not used
	//bool m_diffuse;
	//bool m_specular;
	//bool m_shinine;
	//bool m_ambient;
	//std::list<CSgObject* > m_children;
	CGrTexture* m_texture;

	GLfloat m_specularColor[4];
	GLfloat m_diffuseColor[4];
	GLfloat m_ambientColor[4];
	GLfloat m_shininess[1];
};

