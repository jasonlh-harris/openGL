#pragma once
#include "sgobject.h"
#include "SgPtr.h"
#include <list>
#include <vector>
class CSgComposite :
	public CSgObject
{
public:
	CSgComposite(void){}
	~CSgComposite(void){
		//for(std::list<CSgPtr<CSgObject> >::iterator c=m_children.begin();c != m_children.end(); c++)
			//delete (*c);
	}
	void Render(void);
	void AddChild(CSgObject *child) { m_children.push_back(child); }

private:
	std::list<CSgPtr<CSgObject> > m_children;
};
