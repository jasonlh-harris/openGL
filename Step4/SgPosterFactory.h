#pragma once
#include "SgFactory.h"
class CSgPosterFactory :
	public CSgFactory
{
public:
	CSgPosterFactory(void);
	~CSgPosterFactory(void);
	void Create(CSgComposite*);
	void Create(CSgComposite&);
	CSgObject* Create(void);
	void SetPicture(LPCTSTR c){name = c;}
	void SetWidthHeight(double w, double h){PosterWidth = w; PosterHeight = h;}
	void SetWidth(double w){PosterWidth = w;}
	void setHeight(double h){PosterHeight = h;}
	void setBordered(bool b){bordered = b;}
	void setBorderedTexture(LPCTSTR c){borderName = c;}
	void isBorderedTextured(bool b){borderTexture = b;}

private:
	LPCTSTR name;
	LPCTSTR borderName;
	double width;
	double PosterHeight;
	double PosterWidth;
	bool bordered, borderTexture;
};

