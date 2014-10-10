#pragma once
#include "scenefactory.h"
#include "SgFactory.h"
#include "graphics\GrVector.h"
#include "SgTexture.h"
#include "SgMesh.h"

class CWindowFactory :
	public CSgFactory
{
public:
	CWindowFactory(void);
	~CWindowFactory(void);
	void Create(CSgComposite *root);

	void CreateWin(CSgComposite *root);
	void CreateNewtonCradle(CSgComposite *root);

	enum WinState{open = 3, closed = 2};

	void CreateDormWindow(CSgComposite* parent, CGrVector dimensions, WinState state);
	void CreateWindowFrame(CSgComposite* parent, CGrVector dimensions);
	void CreateNewton(CSgComposite* parent);
	void CreateNewtonSide(CSgComposite* parent, double height, double radius);
	void CreateNewtonCurve(CSgComposite* parent, double height, double radius);
	void CreateNewtonPole(CSgComposite* parent, double height, double radius, bool bottom);
	void CreateNewtonBall(CSgComposite* parent, double height, double radius);
	void CreateNewtonRotate(CSgComposite* parent);
	void CreateNewtonNonMove(CSgComposite* parent);

private:
	CSgPtr<CSgTexture> m_newtonTexture;
};

