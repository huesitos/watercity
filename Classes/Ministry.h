#ifndef __MINISTRY_H__
#define __MINISTRY_H__

#include "cocos2d.h"
#include "Project.h"


class Ministry : public cocos2d::Sprite
{
public:
	Ministry();
	virtual ~Ministry();

	static Ministry* create(const char* pszFileName);

private:
	
};

#endif // __MINISTRY_H__
