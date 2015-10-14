#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Ministry.h"
#include "ResourceManager.h"
#include "MainMenu.h"

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

	void game_over();


private:
	void 	run_week();
	void 	run_day();
	void 	add_labels();

	ResourceManager &rm;

	Ministry* 	ministry_of_technology;
	Ministry* 	ministry_of_education;
	Ministry* 	ministry_of_culture;

	Size visible_size;
	Vec2 origin;
	Vec2 top_right;

	Label* _happinessLabel;
	Label* _happinessPenaltyLabel;
	Label* _awarenessLabel;

	Label* _waterReservesLabel;
	Label* _waterInflowLabel;

	Label* _selectedWaterConsumptionLabel;
	Label* _actualWaterConsumptionLabel;
	Label* _desiredWaterConsumptionLabel;

	Label* _cashLabel;
	Label* _monthlyTaxesLabel;

	Label* _projectLabel;

	Sprite* _happinessSprite;
	Sprite* _awarenessSprite;

	Sprite* _waterReservesSprite;
	Sprite* _waterInflowSprite;
	Sprite* _waterConsumptionSprite;

	Sprite* _cashSprite;
	Sprite* _monthlyTaxesSprite;

	ui::Button* run_week_button;
	ui::Button* add_button;
	ui::Button* substract_button;
};

#endif // __GAME_LAYER_H__
