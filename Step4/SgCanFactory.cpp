#include "stdafx.h"
#include "SgCanFactory.h"
#include <cmath>
#include "SgTexture.h"
CSgCanFactory::CSgCanFactory(void)
{
}


CSgCanFactory::~CSgCanFactory(void)
{
}
CSgObject* CSgCanFactory::Create(void)
{
	CSgPtr<CSgComposite> comp = new CSgComposite();

	Create(comp);

	return comp;
}
void CSgCanFactory::Create(CSgComposite *parent)
{
	CSgPtr <CSgTexture > canTexture = new CSgTexture(L"textures/CanTextureFINISHED.jpg");
	
	CSgPtr <CSgMesh > can = new CSgMesh();

	int n = 20;
	const double pi = 3.14159265;
	double angle = 0;
	//mesured dimentions of a can in meters
	double radius = 0.028575;
	double height = 0.1397;
	//the center of the can
	can->AddVertex(CGrVector(0,height,0,1));
	can->AddNormal(CGrVector(0., 1., 0.,1.));
	can->AddNormal(CGrVector(0., -1., 0.,1.));

	//texture coordinates in pixels, starts at top-left corner
	double textureSize = 1600.0;
	double textureRadius = 250/textureSize;
	double lableBot = 1100.0;
	double lableleft = 320.0;
	double lablewidth = 880.0;
	double lableheight = 600.0;
	//middle of the top lid
	can->AddTexCoord(.5,1-textureRadius);
	for(int i = 0; i<=n; i++)
	{
		angle = (2 * pi / n) * i;
		can->AddVertex(CGrVector(radius * cos(angle),height,radius * -sin(angle),1));
		can->AddVertex(CGrVector(radius * cos(angle),0,radius * -sin(angle),1));
		can->AddNormal(CGrVector(cos(angle), 0, -sin(angle),1.));
	}
	int sideIndex = 0;
	int botIndex = 0;
	for(int i = 0; i<=n; i++, sideIndex++, botIndex++)
	{
		angle = (2 * pi / n) * i;
		//Texture coordinates-Top
		can->AddTexCoord(.5 + textureRadius * (cos(angle)),(1-textureRadius) + textureRadius * (sin(angle)));

	}
	for(int i = 0; i<n; i++)
	{
		//Texture coordinates-Side
		
		can->AddTexCoord((lableleft / textureSize) + i * (lablewidth / textureSize) /n,(1-lableBot/textureSize));
		can->AddTexCoord((lableleft / textureSize) + i * (lablewidth / textureSize) /n, lableBot/textureSize);
		botIndex+=2;

	}
	for(int i = 0; i<=n; i++)
	{
		angle = (2 * pi / n) * i;
		
		//Texture coordinates-bot
		can->AddTexCoord(.5 + textureRadius * (cos(angle)),(textureRadius) + textureRadius * (sin(angle)));
	}
	//middle of the top lid
	can->AddTexCoord(.5,textureRadius);
	can->AddVertex(CGrVector(0,0,0,1));

	
	for(int i = 0;i<n;i++)
	{
		//top
		can->AddTriangleVertex(0,0,0);
		can->AddTriangleVertex(i*2+1,0, i + 1);
		can->AddTriangleVertex(i*2+3,0,i + 2);

		//bottom
		can->AddTriangleVertex(i*2+2,1,botIndex + i + 1);
		can->AddTriangleVertex(2*n+3,1,botIndex + n + 2);
		can->AddTriangleVertex(i*2+4,1,botIndex+i+2);

		//sides
		can->AddTriangleVertex(2 * i + 1, i + 1,sideIndex + 2*i);
		can->AddTriangleVertex(2 * i + 2, i + 1,sideIndex + 2*i + 1);
		can->AddTriangleVertex(2 * i + 3, i + 2,sideIndex + 2*i + 2);

		can->AddTriangleVertex(2 * i + 3,  i + 2,sideIndex + 2*i+2);
		can->AddTriangleVertex(2 * i + 2, i + 1,sideIndex + 2*i +1);
		can->AddTriangleVertex(2* i + 4, i + 2,sideIndex + 2 *i + 3);
	}
	canTexture->AddChild(can);
	parent->AddChild(canTexture);


}