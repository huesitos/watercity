#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ProjectMenuItem.h"
#include "ResourceManager.h"
#include "MainMenu.h"
#include "Climate.h"

USING_NS_CC;


class GameLayer : public cocos2d::Layer
{
public:
	GameLayer()
		: rm(ResourceManager::getInstance()), climate(Climate::getInstance())
	{
		rm.reset();
	}

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	void update_labels();

	void turn_off_listeners();
	void turn_on_listeners();

	void game_over();
	void finished();

	ProjectMenuItem* get_menu_technology() { return menu_technology; }
	ProjectMenuItem* get_menu_education() { return menu_education; }
	ProjectMenuItem* get_menu_culture() { return menu_culture; }

private:
	void 	run_week();
	void 	run_day();
	void 	add_labels();

	ResourceManager &rm;
	Climate &climate;

	Sprite* 	background_town;
	Sprite* sunny;
  Sprite* cloudy;
  Sprite* rainy;

	Ministry* 	ministry_of_technology;
	Ministry* 	ministry_of_education;
	Ministry* 	ministry_of_culture;

	ProjectMenuItem* 	menu_technology;
	ProjectMenuItem* 	menu_education;
	ProjectMenuItem* 	menu_culture;

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

	Sprite* 			desired_consumption;
	Sprite* 			actual_consumption;

	bool 		did_riot_happen;
	bool 		will_reward;
	int 		cash_reward;
};

#endif // __GAME_LAYER_H__
