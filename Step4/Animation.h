#pragma once
class CAnimation
{
public:
	CAnimation(void);
	~CAnimation(void);

	void IncRef() {m_refs++;}
	void DecRef() {m_refs--; if(m_refs==0){ delete this;}}
	
	virtual void Update(void) = 0;
	
private:
	int m_refs;
};

