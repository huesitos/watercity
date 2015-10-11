#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenu);

	void start_game(cocos2d::Ref *pSender);

	void exit_game(cocos2d::Ref *pSender);
};

#endif // __MAIN_MENU_H__
