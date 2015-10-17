#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ProjectMenuItem.h"
#include "ResourceManager.h"
#include "MainMenu.h"
#include "Climate.h"
#include "Breakdown.h"
#include "ProhibitedAct.h"
#include "Project.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

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

	void update(float dt);

	ProjectMenuItem* get_menu_technology() { return menu_technology; }
	ProjectMenuItem* get_menu_education() { return menu_education; }
	ProjectMenuItem* get_menu_culture() { return menu_culture; }

private:
	void 	run_week();
	void 	run_day();
	void 	add_labels();

	void 	start_breakdown_minigame();
	void 	initial_countdown_breakdown_minigame();
	void 	run_breakdown_minigame();
	void 	end_breakdown_minigame();
	void 	on_correct_breakdown(ui::Button* breakdown_to_remove);
	void 	on_incorrect_breakdown();

	// Report methods (end of week)

	void 	report_breakdown_minigame();
	void 	report_riots();

	void 	start_prohibited_act_minigame();
	void 	run_prohibited_act_minigame();
	void 	end_prohibited_act_minigame();
	void 	on_correct_prohibited_act();
	void 	on_incorrect_prohibited_act();

	void 	report();

	ResourceManager &rm;
	Climate &climate;

	Sprite* 	background_town;
	Sprite* 	sky;
	Sprite* 	sun_bg;
	Sprite* 	rain_bg;
	Sprite* 	cloudy_bg;
	Sprite* 	rain_drops;

	Sprite* 	goal_bubble;

	// Clouds in the sky

	Sprite* 	cloud1;
	Sprite* 	cloud2;
	Sprite* 	cloud3;
	Sprite* 	cloud4;
	Sprite* 	cloud5;

	Vector<Sprite*> clouds;

	void 		run_clouds();
	void 		stop_clouds();

	Sprite* 	shadow;
	Sprite* 	shadow2;

	Sprite* sunny;
  	Sprite* cloudy;
  	Sprite* rainy;

  	Sprite* happy;
  	Sprite* mad;

  	Sprite* water_meter;
  	Sprite* water_reserves;

  	Sprite* water_gallon;

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
	Label* _feeLabel;
	Label* _populationLabel;

	Label* 	_goalLabel;

	Label* _selectedWaterConsumptionLabel;
	Label* _actualWaterConsumptionLabel;
	Label* _desiredWaterConsumptionLabel;

	ui::Button* goal_button;
	ui::Button* run_week_button;
	ui::Button* add_button;
	ui::Button* substract_button;

	Sprite* background_consumption;
	Sprite* background_resources;

	// Breakdowns minigame

	Vector<ui::Button*> breakdowns;
	Vector<Sprite*> 	breakdown_sprites;

	Label* 	breakdowns_clock;

	bool 	is_running_breakdowns_minigame;
	float 	breakdowns_countdown;

	bool 	did_win;

	bool 	first_breakdown_minigame;

	// Prohibited Acts minigame

	Vector<ui::Button*> prohibited_acts;
	Vector<Sprite*> 	prohibited_act_sprites;

	Label* 	prohibited_acts_clock;

	bool 	is_running_prohibited_acts_minigame;
	float 	prohibited_acts_countdown;

	// Water consumption gallon

	Vector<Sprite*> 	water_lines;
	Vector<Sprite*> 	water_lines_meter;
	int 				num_of_water_lines_gallon;
	int 				num_of_water_lines_meter;
	float 				amount_of_line;
	float 				amount_of_line_reserves;

	Sprite* 			desired_consumption;
	Sprite* 			actual_consumption;

	bool 		did_riot_happen;
	bool 		will_reward;

	// Sounds

	int 	water_sound_id = -1;
	int 	clock_tick_id = -1;

	// Weekly flow

	bool 	advance_to_minigame;
	bool 	advance_from_minigame;
};

#endif // __GAME_LAYER_H__
