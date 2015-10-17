#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ProjectMenuItem.h"
#include "ResourceManager.h"
#include "MainMenu.h"
#include "Climate.h"
#include "Breakdown.h"
#include "ProhibitedAct.h"
#include "Project.h"
#include "GameLayer.h"

USING_NS_CC;


class TutorialScene : public cocos2d::Layer
{
public:
  TutorialScene()
    : rm(ResourceManager::getInstance()), climate(Climate::getInstance())
  {
    rm.reset();
  }

  static cocos2d::Scene* createScene();

  virtual bool init();

  CREATE_FUNC(TutorialScene);

  void update(float dt) {};
  void add_buttons();

private:
  void  add_labels();
  void  add_dialogs();

  ResourceManager &rm;
  Climate &climate;

  Sprite* t1;
  Sprite* t2;
  Sprite* t3;
  Sprite* t4;
  Sprite* t5;
  Sprite* t6;
  Sprite* t7;
  Sprite* t8;
  Sprite* t9;
  Sprite* t10;
  Sprite* t11;
  Sprite* t12;
  Sprite* t13;
  Sprite* t14;
  Sprite* t15;
  Sprite* t16;
  Sprite* t17;

  ui::Button* next1;
  ui::Button* next2;
  ui::Button* next3;
  ui::Button* next4;
  ui::Button* next5;
  ui::Button* next6;
  ui::Button* next7;
  ui::Button* next8;
  ui::Button* next9;
  ui::Button* next10;
  ui::Button* next11;
  ui::Button* next12;
  ui::Button* next13;
  ui::Button* next14;
  ui::Button* next15;
  ui::Button* next16;
  ui::Button* next17;

  ui::Button* skip;

  Sprite*   background_town;
  Sprite*   background_tuto;
  Sprite*   sky;
  Sprite*   sun_bg;

  Sprite* sunny;
  Sprite* cloudy;
  Sprite* rainy;

  Sprite* happy;
  Sprite* mad;

  Sprite* water_meter;
  Sprite* water_reserves;

  Sprite* water_gallon;

  Sprite* background_consumption;
  Sprite* background_resources;

  Ministry*   ministry_of_technology;
  Ministry*   ministry_of_education;
  Ministry*   ministry_of_culture;

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

  Label* _selectedWaterConsumptionLabel;
  Label* _actualWaterConsumptionLabel;
  Label* _desiredWaterConsumptionLabel;

  ui::Button* run_week_button;
  ui::Button* add_button;
  ui::Button* substract_button;

  // Water consumption gallon

  Vector<Sprite*>   water_lines;
  Vector<Sprite*>   water_lines_meter;
  int         num_of_water_lines_gallon;
  int         num_of_water_lines_meter;
  float         amount_of_line;
  float         amount_of_line_reserves;

  Sprite*       desired_consumption;
  Sprite*       actual_consumption;
};

#endif // __TUTORIAL_SCENE_H__
