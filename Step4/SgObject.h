#pragma once

class CSgObject
{
public:
	CSgObject(void);
	virtual ~CSgObject(void);

	virtual void Render(void) = 0;

	void IncRef(void){m_ref++;}
	void DecRef(void){m_ref--;if(m_ref == 0){delete this;}}

private:
	int m_ref;
};

