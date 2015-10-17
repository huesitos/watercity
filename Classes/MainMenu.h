#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
#include "GameLayer.h"
#include "TutorialScene.h"

class MainMenu : public cocos2d::Layer
{
public:
  Sprite* background;

	static cocos2d::Scene* createScene();

  void setup_listener();
  void disable_listener();

	virtual bool init();

	CREATE_FUNC(MainMenu);

	void start_game();

	void exit_game();

protected:
  bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

  cocos2d::EventListenerTouchOneByOne* listener;
};

#endif // __MAIN_MENU_H__
