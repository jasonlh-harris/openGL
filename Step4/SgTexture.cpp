#include "stdafx.h"
#include "SgTexture.h"


CSgTexture::CSgTexture(void)
{
}

CSgTexture::CSgTexture(LPCTSTR filename)
{
	m_filename=filename;
	m_texture.LoadFile(m_filename);
}

CSgTexture::~CSgTexture(void)
{
}

void CSgTexture::Render(void){

	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_texture.TexName());

	CSgComposite::Render();

	glDisable(GL_TEXTURE_2D);
}
