#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Ministry.h"
#include "ResourceManager.h"

USING_NS_CC;


class GameLayer : public cocos2d::Layer
{
public:
	GameLayer()
		: rm(ResourceManager::getInstance())
	{}

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	void update_labels();

private:
	void 	run_week();

	void 	run_day();

	ResourceManager &rm;

	Ministry* 	technological_ministry;

	Size visible_size;
	Vec2 origin;
	Vec2 top_right;

	Label* _happinessLabel;
	Label* _awarenessLabel;

	Label* _waterReservesLabel;
	Label* _waterInflowLabel;
	Label* _waterConsumptionLabel;

	Label* _cashLabel;
	Label* _monthlyTaxesLabel;

	Label* _projectLabel;

	void add_labels();

	ui::Button* run_week_button;
};

#endif // __GAME_LAYER_H__
