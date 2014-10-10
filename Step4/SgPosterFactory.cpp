#include "stdafx.h"
#include "SgPosterFactory.h"
#include "SgMesh.h"
#include "SgTexture.h"
#include "SgMaterial.h"

CSgPosterFactory::CSgPosterFactory(void)
{
	PosterHeight = 2;
	PosterWidth = 2;
	bordered = true;
	borderTexture = false;
}


CSgPosterFactory::~CSgPosterFactory(void)
{
}

CSgObject* CSgPosterFactory::Create(void)
{
	CSgPtr<CSgComposite> comp = new CSgComposite();

	Create(comp);

	return comp;
}

void CSgPosterFactory::Create(CSgComposite* arg_Poster)
{
	CSgPtr <CSgMesh> borderMesh = new CSgMesh();
	CSgPtr <CSgMaterial> posterColor = new CSgMaterial();

	posterColor->SetDiffuseColor(1.f, 1.f, 1.f, 1.0f);
	posterColor->SetSpecularColor(0.f, 0.f, 0.f, 1.0f);
	posterColor->SetShininess(5.f);

	CSgPtr<CSgTexture> theTexture = new CSgTexture(name);
	CSgPtr<CSgMesh> thePoster = new CSgMesh();

	CGrVector theFacing = CGrVector(0, 0, 1, 1);
	thePoster->AddNormal(theFacing);
	

	CGrVector theBottomLeft = CGrVector(0,0,0,0);
	//CGrVector theBottomLeftTexture = CGrVector(0,0);
	//thePoster->AddTexCoord(0,0);
	thePoster->AddVertex(theBottomLeft);

	CGrVector theBottomRight = CGrVector(PosterWidth, 0, 0, 0);
	//CGrVector theBottomRightTexture = CGrVector(1,0);
	//thePoster->AddTexCoord(1,0);
	thePoster->AddVertex(theBottomRight);

	CGrVector theTopRight = CGrVector(PosterWidth, PosterHeight, 0, 0);
	//CGrVector theTopRightTexture = CGrVector(1,1);
	//thePoster->AddTexCoord(1,1);
	thePoster->AddVertex(theTopRight);

	CGrVector theTopLeft = CGrVector(0, PosterHeight, 0, 0);
	//CGrVector theTopLeftTexture = CGrVector(0, 1);
	//thePoster->AddTexCoord(0,1);
	thePoster->AddVertex(theTopLeft);

	/*
	thePoster->AddTriangleVertex(0,0,0);
	thePoster->AddTriangleVertex(2,0,2);
	thePoster->AddTriangleVertex(3,0,3);
	thePoster->AddTriangleVertex(0,0,0);
	thePoster->AddTriangleVertex(1,0,1);
	thePoster->AddTriangleVertex(2,0,2);
	*/
	thePoster->AddSelfTexturedQuad(0,1,2,3,0);
	theTexture->AddChild(thePoster);
	posterColor->AddChild(theTexture);
	arg_Poster->AddChild(posterColor);

	if(bordered)
	{
		double borderThickness = 0.2;

		double borderPoints[16][4] = {
			{0,0,0,0},//0
			{PosterWidth,0,0,0}, //1
			{PosterWidth, PosterHeight, 0,0},//2
			{0, PosterWidth,0,0},//3
			{-borderThickness, -borderThickness,0,0},//4
			{PosterWidth+borderThickness, -borderThickness, 0, 0},//5
			{PosterWidth + borderThickness, PosterHeight + borderThickness, 0,0},//6
			{-borderThickness, PosterHeight + borderThickness,0,0},//7
			{0,0,borderThickness,0},//8
			{PosterWidth,0,borderThickness,0}, //9
			{PosterWidth, PosterHeight, borderThickness,0},//10
			{0, PosterWidth,borderThickness,0},//11
			{-borderThickness, -borderThickness,borderThickness,0},//12
			{PosterWidth+borderThickness, -borderThickness, borderThickness, 0},//13
			{PosterWidth + borderThickness, PosterHeight + borderThickness, borderThickness,0},//14
			{-borderThickness, PosterHeight + borderThickness,borderThickness,0}//16
		};
	double n[6][4]={
		{0,0,1,1},//0Front
		{1,0,0,1},//1Right Side
		{0,0,-1,1},//2Back
		{-1,0,0,1},//3Left
		{0,1,0,1},//4Top
		{0,-1,0,1}//5bottom
	};
		for(int i = 0; i < 6; i++)
		{
			borderMesh->AddNormal(n[i]);
		}
		for(int i = 0; i < 16; i++)
		{
			borderMesh->AddVertex(borderPoints[i]);
		}

		if(borderTexture)
		{
			CSgPtr<CSgTexture> theBorderTexture = new CSgTexture(borderName);
			borderMesh->AddSelfTexturedQuad(12,13,9,8,0);
			borderMesh->AddSelfTexturedQuad(9,13,14,10,0);
			borderMesh->AddSelfTexturedQuad(11,10,14,15,0);
			borderMesh->AddSelfTexturedQuad(12,8,11,15,0);
			borderMesh->AddSelfTexturedQuad(8,9,1,0,4);
			borderMesh->AddSelfTexturedQuad(1,9,10,2,1);
			borderMesh->AddSelfTexturedQuad(3,2,10,11,5);
			borderMesh->AddSelfTexturedQuad(0,3,11,8,1);
			borderMesh->AddSelfTexturedQuad(4,5,13,12,5);
			borderMesh->AddSelfTexturedQuad(5,6,14,13,1);
			borderMesh->AddSelfTexturedQuad(15,14,6,7,4);
			borderMesh->AddSelfTexturedQuad(7,4,12,15,3);
			theBorderTexture->AddChild(borderMesh);
			arg_Poster->AddChild(theBorderTexture);
			borderTexture = false;
		}
		else
		{
			borderMesh->AddSelfTexturedQuad(12,13,9,8,0);
			borderMesh->AddSelfTexturedQuad(9,13,14,10,0);
			borderMesh->AddSelfTexturedQuad(11,10,14,15,0);
			borderMesh->AddSelfTexturedQuad(12,8,11,15,0);
			borderMesh->AddSelfTexturedQuad(8,9,1,0,4);
			borderMesh->AddSelfTexturedQuad(1,9,10,2,1);
			borderMesh->AddSelfTexturedQuad(3,2,10,11,5);
			borderMesh->AddSelfTexturedQuad(0,3,11,8,1);
			borderMesh->AddSelfTexturedQuad(4,5,13,12,5);
			borderMesh->AddSelfTexturedQuad(5,6,14,13,1);
			borderMesh->AddSelfTexturedQuad(15,14,6,7,4);
			borderMesh->AddSelfTexturedQuad(7,4,12,15,3);
			arg_Poster->AddChild(borderMesh);
		}
	}

	



}