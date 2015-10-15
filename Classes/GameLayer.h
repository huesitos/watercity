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
	{
		rm.reset();
	}

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

	Sprite* 	background_town;
	Sprite* 	background_menu;

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
	Label* _cashLabel;
	Label* _populationLabel;

	Label* _selectedWaterConsumptionLabel;
	Label* _actualWaterConsumptionLabel;
	Label* _desiredWaterConsumptionLabel;

	ui::Button* run_week_button;
	ui::Button* add_button;
	ui::Button* substract_button;

	// Water consumption gallon

	Vector<Sprite*> 	water_lines;
	int 				num_of_water_lines;

	Sprite* 			topmost_line;
	Sprite* 			desired_consumption;
	Sprite* 			actual_consumption;
};

#endif // __GAME_LAYER_H__
