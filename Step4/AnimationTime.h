#pragma once
#include "Animation.h"
#include <vector>
#include "SgPtr.h"
#include "SgObject.h"

class CAnimationTime
{
public:
	CAnimationTime(void);
	~CAnimationTime(void);

	void Update(void);
	void AddChannel(CAnimation *channel){m_channels.push_back(channel);}
private:
	std::vector< CSgPtr<CAnimation> > m_channels;
};

