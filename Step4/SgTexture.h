#pragma once
#include "sgcomposite.h"
#include "graphics\GrTexture.h"

class CSgTexture :
	public CSgComposite
{
public:
	CSgTexture(void);
	CSgTexture(LPCTSTR filename);
	~CSgTexture(void);
	void Render(void);

private:
	CString m_filename;
	CGrTexture m_texture;
};

