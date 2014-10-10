#pragma once
#include "scenefactory.h"
#include "SgFactory.h"
#include "SgTexture.h"

class CPengFactory :
	public CSgFactory
{
public:
	CPengFactory(void);
	~CPengFactory(void);

	void Create(CSgComposite *root);


	void CreateDesk(CSgComposite *parent, double);
	void CreateCar(CSgComposite *parent);
	void CreatePoster(CSgComposite *parent);
	double *Normal3dv( const double *a,const double *b, const double *c);
	
private:
	CSgPtr<CSgTexture> carBodyText;

	CSgPtr<CSgTexture> rimText;
	CSgPtr<CSgTexture> tireMiddleText;
	CSgPtr<CSgTexture> fireText;
	CSgPtr<CSgTexture> deskFrontText;
	CSgPtr<CSgTexture> posterText;

};

