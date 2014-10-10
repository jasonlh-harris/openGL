#include "stdafx.h"
#include "SceneFactory.h"
#include "SgMesh.h"
#include "SgPtr.h"


CSceneFactory::CSceneFactory(void)
{
}


CSceneFactory::~CSceneFactory(void)
{
}

void CSceneFactory::Create(CSgComposite &m)
{
	CSgPtr<CSgMesh> room = new CSgMesh();
	//room->AddVertex(add vertex);
	m.AddChild(room);
}