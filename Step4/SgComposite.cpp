#include "stdafx.h"
#include "SgComposite.h"
#include "graphics/GrVector.h"

using namespace std;

void CSgComposite::Render(void)
{
	glPushMatrix();
	for(std::list<CSgPtr<CSgObject> >::iterator c=m_children.begin();c != m_children.end(); c++)
	{
		(*c)->Render();
	}
	glPopMatrix();
}