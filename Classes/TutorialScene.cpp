#include "TutorialScene.h"

Scene* TutorialScene::createScene()
{
  auto scene = Scene::create();

  auto layer = TutorialScene::create();

  scene->addChild(layer);

  return scene;
}

bool TutorialScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    amount_of_line = 40.0f;
    amount_of_line_reserves = 103.0f;

    visible_size = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    top_right.x = origin.x + visible_size.width;
    top_right.y = origin.y + visible_size.height;

     // add sky background
    sky = Sprite::create("images/sky.png");
    sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sky->setPosition(origin);

    this->addChild(sky, -1);

    // add background
    background_town = Sprite::create("images/back.png");
    background_town->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_town->setPosition(origin);

    this->addChild(background_town, 1);

    // add background
    background_tuto = Sprite::create("images/tutorialback.png");
    background_tuto->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_tuto->setPosition(origin);

    this->addChild(background_tuto, 10);

    // climate sprites
    sun_bg = Sprite::create("images/sun_anim/sun.png");
    sun_bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sun_bg->setPosition(origin);

    this->addChild(sun_bg, 2);

    sunny = Sprite::create("images/sunny.png");
    sunny->setPosition(Vec2(origin.x + visible_size.width * 0.94, origin.y + visible_size.height * 0.34));

    this->addChild(sunny, 3);

    water_reserves = Sprite::create("images/waterreserve.png");
    water_reserves->setPosition(Vec2(origin.x + visible_size.width * 0.055, origin.y + visible_size.height * 0.917));
    water_reserves->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(water_reserves, 3);

    water_meter = Sprite::create("images/meter4.png");
    water_meter->setPosition(Vec2(origin.x, origin.y + visible_size.height));
    water_meter->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    this->addChild(water_meter, 3);

    water_gallon = Sprite::create("images/gallon.png");
    water_gallon->setPosition(Vec2(origin.x + visible_size.width * 0.05, origin.y + visible_size.height * 0.03));
    water_gallon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(water_gallon, 2);

    background_consumption = Sprite::create("images/consumptionback.png");
    background_consumption->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_consumption->setPosition(origin);

    this->addChild(background_consumption, 1);

    background_resources = Sprite::create("images/resourcesmenu.png");
    background_resources->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    background_resources->setPosition(origin + Vec2(visible_size.width, 0));

    this->addChild(background_resources, 1);

    ministry_of_technology = MinistryOfTechnology::create("images/technology.png", "tech_projects.txt");
    ministry_of_technology->setPosition(origin.x + visible_size.width * 0.58, origin.y + visible_size.height * 0.66);

    this->addChild(ministry_of_technology, 1);

    ministry_of_education = MinistryOfEducation::create("images/education.png", "tech_projects.txt");
    ministry_of_education->setPosition(origin.x + visible_size.width * 0.76, origin.y + visible_size.height * 0.53);
    this->addChild(ministry_of_education, 1);

    ministry_of_culture = MinistryOfCulture::create("images/park.png", "tech_projects.txt");
    ministry_of_culture->setPosition(origin.x + visible_size.width * 0.64, origin.y + visible_size.height * 0.52);
    this->addChild(ministry_of_culture, 1);

    run_week_button = ui::Button::create("images/start.png");
    run_week_button->setPosition(Vec2(origin.x + visible_size.width * 0.735 - run_week_button->getContentSize().width / 2,
        origin.y + run_week_button->getContentSize().height / 2));
    run_week_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          // this->run_week();
          break;
        default:
          break;
      }
    });

    this->addChild(run_week_button, 2);

    add_button = ui::Button::create("images/more.png");
    add_button->setPosition(Vec2(origin.x + visible_size.width * 0.21, origin.y + visible_size.height * 0.18));

    this->addChild(add_button, 2);

    substract_button = ui::Button::create("images/less.png");
    substract_button->setPosition(Vec2(origin.x + visible_size.width * 0.21, origin.y + visible_size.height * 0.08));

    this->addChild(substract_button, 2);

    add_labels();

    add_dialogs();
    add_buttons();

    return true;
}

void TutorialScene::add_dialogs()
{
  t1 = Sprite::create("images/tutorial/t1.png");
  t2 = Sprite::create("images/tutorial/t2.png");
  t3 = Sprite::create("images/tutorial/t3.png");
  t4 = Sprite::create("images/tutorial/t4.png");
  t5 = Sprite::create("images/tutorial/t5.png");
  t6 = Sprite::create("images/tutorial/t6.png");
  t7 = Sprite::create("images/tutorial/t7.png");
  t8 = Sprite::create("images/tutorial/t8.png");
  t9 = Sprite::create("images/tutorial/t9.png");
  t10 = Sprite::create("images/tutorial/t10.png");
  t11 = Sprite::create("images/tutorial/t11.png");
  t12 = Sprite::create("images/tutorial/t12.png");
  t13 = Sprite::create("images/tutorial/t13.png");
  t14 = Sprite::create("images/tutorial/t14.png");
  t15 = Sprite::create("images/tutorial/t15.png");
  t16 = Sprite::create("images/tutorial/t16.png");

  t1->setVisible(true);
  t2->setVisible(false);
  t3->setVisible(false);
  t4->setVisible(false);
  t5->setVisible(false);
  t6->setVisible(false);
  t7->setVisible(false);
  t8->setVisible(false);
  t9->setVisible(false);
  t10->setVisible(false);
  t11->setVisible(false);
  t12->setVisible(false);
  t13->setVisible(false);
  t14->setVisible(false);
  t15->setVisible(false);
  t16->setVisible(false);

  t1->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t2->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t3->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t4->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t5->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t6->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t7->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t8->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t9->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t10->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t11->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t12->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t13->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t14->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t15->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));
  t16->setPosition(Vec2(origin.x + visible_size.width/2, origin.y + visible_size.height/2));

  this->addChild(t1, 11);
  this->addChild(t2, 11);
  this->addChild(t3, 11);
  this->addChild(t4, 11);
  this->addChild(t5, 11);
  this->addChild(t6, 11);
  this->addChild(t7, 11);
  this->addChild(t8, 11);
  this->addChild(t9, 11);
  this->addChild(t10, 11);
  this->addChild(t11, 11);
  this->addChild(t12, 11);
  this->addChild(t13, 11);
  this->addChild(t14, 11);
  this->addChild(t15, 11);
  this->addChild(t16, 11);
}

void TutorialScene::add_labels()
{
    int fontSize = 18;

    _happinessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", rm.get_happiness()), "fonts/Marker Felt.ttf", fontSize);
    _happinessLabel->setPosition(Vec2(origin.x + visible_size.width * 0.81, origin.y + visible_size.height * 0.19));

    _awarenessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", rm.get_awareness()), "fonts/Marker Felt.ttf", fontSize);
    _awarenessLabel->setPosition(Vec2(origin.x + visible_size.width * 0.81, origin.y + visible_size.height * 0.12));

    _waterReservesLabel = Label::createWithTTF(StringUtils::format("%d",
            rm.get_water_reserves()), "fonts/Marker Felt.ttf", fontSize);
    _waterReservesLabel->setPosition(Vec2(origin.x+110, origin.y + visible_size.height - 36));

    _selectedWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d gl",
            rm.get_selected_water_consumption() * 7), "fonts/Marker Felt.ttf", fontSize);
    _selectedWaterConsumptionLabel->setPosition(Vec2(origin.x + visible_size.width * 0.095, origin.y + visible_size.height * 0.08));

    _cashLabel = Label::createWithTTF(StringUtils::format("$%d", rm.get_cash_total()), "fonts/Marker Felt.ttf", fontSize);
    _cashLabel->setPosition(Vec2(origin.x + visible_size.width * 0.93, origin.y + visible_size.height * 0.19));

    _feeLabel = Label::createWithTTF(StringUtils::format("$%d", rm.get_fee_per_family()*rm.get_number_of_families()*7), "fonts/Marker Felt.ttf", fontSize);
    _feeLabel->setPosition(Vec2(origin.x + visible_size.width * 0.948, origin.y + visible_size.height * 0.11));

    _populationLabel = Label::createWithTTF(StringUtils::format("%d / %d",
        rm.get_population_total()-rm.get_population_occupied(), rm.get_population_total()),
        "fonts/Marker Felt.ttf", fontSize);
    _populationLabel->setPosition(Vec2(origin.x + visible_size.width * 0.87, origin.y + visible_size.height * 0.055));

    _happinessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _awarenessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterReservesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _selectedWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _cashLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _populationLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

    _happinessLabel->setTextColor(Color4B::WHITE);
    _awarenessLabel->setTextColor(Color4B::WHITE);
    _waterReservesLabel->setTextColor(Color4B::WHITE);
    _selectedWaterConsumptionLabel->setTextColor(Color4B::WHITE);
    _cashLabel->setTextColor(Color4B::WHITE);
    _feeLabel->setTextColor(Color4B::WHITE);
    _populationLabel->setTextColor(Color4B::WHITE);

    this->addChild(_happinessLabel, 3);
    this->addChild(_awarenessLabel, 3);
    this->addChild(_waterReservesLabel, 3);
    this->addChild(_selectedWaterConsumptionLabel, 3);
    this->addChild(_cashLabel, 3);
    this->addChild(_feeLabel, 3);
    this->addChild(_populationLabel, 3);

    _happinessPenaltyLabel = Label::createWithTTF(StringUtils::format("%.0f", rm.get_happiness_penalty() * 7), "fonts/Marker Felt.ttf", fontSize);
    _happinessPenaltyLabel->setPosition(Vec2(origin.x + visible_size.width * 0.13, origin.y + visible_size.height * 0.02));

    this->addChild(_happinessPenaltyLabel, 3);


    // galon de agua
    num_of_water_lines_gallon = (rm.get_actual_water_consumption()-rm.get_desired_water_consumption())/amount_of_line;

    desired_consumption = Sprite::create("images/need.png");
    actual_consumption = Sprite::create("images/want.png");

    // el actual deberia tener el mismo height?
    auto wl = Sprite::create("images/galonaguamedio.png");

    desired_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.40));
    actual_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.70) * num_of_water_lines_gallon);

    this->addChild(desired_consumption, 3);
    this->addChild(actual_consumption, 2);

    for (int i = 0; i < num_of_water_lines_gallon; ++i)
    {
        auto wl = Sprite::create("images/galonaguamedio.png");
        wl->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.70) * i);
        wl->setVisible(false);

        this->addChild(wl, 1);
        water_lines.pushBack(wl);
    }

    int current_num_lines = (rm.get_selected_water_consumption() - rm.get_desired_water_consumption()) / amount_of_line;
    for (int i = 0; i < current_num_lines; ++i)
    {
        water_lines.at(i)->setVisible(true);
    }

    // galon de agua
    num_of_water_lines_meter = amount_of_line_reserves;

    wl = Sprite::create("images/meteragua1.png");
    wl->setPosition(Vec2(origin.x + visible_size.width * 0.03, origin.y + visible_size.height * 0.170));
    this->addChild(wl, 1);

    for (int i = 0; i < num_of_water_lines_meter; ++i)
    {
        wl = Sprite::create("images/meteragua2.png");
        wl->setPosition(Vec2(origin.x + visible_size.width * 0.03, origin.y + visible_size.height * 0.178)
            + Vec2(0, wl->getContentSize().height * 0.70) * i);
        wl->setVisible(false);

        this->addChild(wl, 1);
        water_lines_meter.pushBack(wl);
    }

    current_num_lines = amount_of_line_reserves;
    for (int i = 0; i < current_num_lines; ++i)
    {
        water_lines_meter.at(i)->setVisible(true);
    }
}

void TutorialScene::add_buttons()
{
    skip = ui::Button::create("images/saltar.png");
    skip->setPosition(Vec2(origin.x + visible_size.width * 0.35, origin.y + visible_size.height * 0.39));

    skip->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene()));
          break;
        default:
          break;
      }
    });
    this->addChild(skip, 11);

    next1 = ui::Button::create("images/siguiente.png");
    next2 = ui::Button::create("images/siguiente.png");
    next3 = ui::Button::create("images/siguiente.png");
    next4 = ui::Button::create("images/siguiente.png");
    next5 = ui::Button::create("images/siguiente.png");
    next6 = ui::Button::create("images/siguiente.png");
    next7 = ui::Button::create("images/siguiente.png");
    next8 = ui::Button::create("images/siguiente.png");
    next9 = ui::Button::create("images/siguiente.png");
    next10 = ui::Button::create("images/siguiente.png");
    next11 = ui::Button::create("images/siguiente.png");
    next12 = ui::Button::create("images/siguiente.png");
    next13 = ui::Button::create("images/siguiente.png");
    next14 = ui::Button::create("images/siguiente.png");
    next15 = ui::Button::create("images/siguiente.png");
    next16 = ui::Button::create("images/siguiente.png");

    next1->setPosition(Vec2(origin.x + visible_size.width * 0.56, origin.y + visible_size.height * 0.39));
    next2->setPosition(Vec2(origin.x + visible_size.width * 0.56, origin.y + visible_size.height * 0.39));
    next3->setPosition(Vec2(origin.x + visible_size.width * 0.54, origin.y + visible_size.height * 0.36));
    next4->setPosition(Vec2(origin.x + visible_size.width * 0.56, origin.y + visible_size.height * 0.40));
    next5->setPosition(Vec2(origin.x + visible_size.width * 0.56, origin.y + visible_size.height * 0.40));
    next6->setPosition(Vec2(origin.x + visible_size.width * 0.44, origin.y + visible_size.height * 0.105));
    next7->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.32));
    next8->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.32));
    next9->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.32));
    next10->setPosition(Vec2(origin.x + visible_size.width * 0.46, origin.y + visible_size.height * 0.25));
    next11->setPosition(Vec2(origin.x + visible_size.width * 0.44, origin.y + visible_size.height * 0.582));
    next12->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.5052));
    next13->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.44));
    next14->setPosition(Vec2(origin.x + visible_size.width * 0.55, origin.y + visible_size.height * 0.42));
    next15->setPosition(Vec2(origin.x + visible_size.width * 0.65, origin.y + visible_size.height * 0.195));
    next16->setPosition(Vec2(origin.x + visible_size.width * 0.62, origin.y + visible_size.height * 0.485));

    next1->setVisible(true);
    next2->setVisible(false);
    next3->setVisible(false);
    next4->setVisible(false);
    next5->setVisible(false);
    next6->setVisible(false);
    next7->setVisible(false);
    next8->setVisible(false);
    next9->setVisible(false);
    next10->setVisible(false);
    next11->setVisible(false);
    next12->setVisible(false);
    next13->setVisible(false);
    next14->setVisible(false);
    next15->setVisible(false);
    next16->setVisible(false);

    next1->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next1->setVisible(false);
          this->t1->setVisible(false);

          this->next2->setVisible(true);
          this->t2->setVisible(true);
          break;
        default:
          break;
      }
    });

    next2->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next2->setVisible(false);
          this->t2->setVisible(false);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.27, origin.y + visible_size.height * 0.36));

          this->next3->setVisible(true);
          this->t3->setVisible(true);
          break;
        default:
          break;
      }
    });

    next3->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next3->setVisible(false);
          this->t3->setVisible(false);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.27, origin.y + visible_size.height * 0.40));

          this->next4->setVisible(true);
          this->t4->setVisible(true);
          break;
        default:
          break;
      }
    });

    next4->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next4->setVisible(false);
          this->t4->setVisible(false);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.40));

          this->next5->setVisible(true);
          this->t5->setVisible(true);
          break;
        default:
          break;
      }
    });

    next5->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next5->setVisible(false);
          this->t5->setVisible(false);

          this->water_meter->setZOrder(11);
          this->water_reserves->setZOrder(11);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.295, origin.y + visible_size.height * 0.105));

          this->next6->setVisible(true);
          this->t6->setVisible(true);
          break;
        default:
          break;
      }
    });

    next6->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->water_meter->setZOrder(3);
          this->water_reserves->setZOrder(3);

          this->next6->setVisible(false);
          this->t6->setVisible(false);

          this->background_consumption->setZOrder(11);
          for (int i = 0; i < this->water_lines.size(); ++i)
          {
              this->water_lines.at(i)->setZOrder(11);
          }
          this->water_gallon->setZOrder(11);
          this->actual_consumption->setZOrder(11);
          this->desired_consumption->setZOrder(11);
          this->_selectedWaterConsumptionLabel->setZOrder(11);

          this->add_button->setZOrder(11);
          this->substract_button->setZOrder(11);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.26, origin.y + visible_size.height * 0.32));

          this->next7->setVisible(true);
          this->t7->setVisible(true);
          break;
        default:
          break;
      }
    });

    next7->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next7->setVisible(false);
          this->t7->setVisible(false);

          this->background_consumption->setZOrder(11);
          for (int i = 0; i < this->water_lines.size(); ++i)
          {
              this->water_lines.at(i)->setZOrder(11);
          }
          this->water_gallon->setZOrder(11);
          this->actual_consumption->setZOrder(11);
          this->desired_consumption->setZOrder(11);
          this->_selectedWaterConsumptionLabel->setZOrder(11);

          this->add_button->setZOrder(11);
          this->substract_button->setZOrder(11);

          this->next8->setVisible(true);
          this->t8->setVisible(true);
          break;
        default:
          break;
      }
    });

    next8->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next8->setVisible(false);
          this->t8->setVisible(false);

          this->next9->setVisible(true);
          this->t9->setVisible(true);
          break;
        default:
          break;
      }
    });

    next9->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next9->setVisible(false);
          this->t9->setVisible(false);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.26, origin.y + visible_size.height * 0.25));

          this->next10->setVisible(true);
          this->t10->setVisible(true);
          break;
        default:
          break;
      }
    });

    next10->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next10->setVisible(false);
          this->t10->setVisible(false);

          this->background_consumption->setZOrder(3);
          for (int i = 0; i < this->water_lines.size(); ++i)
          {
              this->water_lines.at(i)->setZOrder(3);
          }
          this->water_gallon->setZOrder(3);
          this->actual_consumption->setZOrder(3);
          this->desired_consumption->setZOrder(3);
          this->_selectedWaterConsumptionLabel->setZOrder(3);

          this->add_button->setZOrder(3);
          this->substract_button->setZOrder(3);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.26, origin.y + visible_size.height * 0.582));

          this->next11->setVisible(true);
          this->t11->setVisible(true);
          break;
        default:
          break;
      }
    });

    next11->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next11->setVisible(false);
          this->t11->setVisible(false);

          this->ministry_of_education->setZOrder(11);
          this->ministry_of_technology->setZOrder(11);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.28, origin.y + visible_size.height * 0.5052));

          this->next12->setVisible(true);
          this->t12->setVisible(true);
          break;
        default:
          break;
      }
    });

    next12->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next12->setVisible(false);
          this->t12->setVisible(false);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.29, origin.y + visible_size.height * 0.44));

          this->next13->setVisible(true);
          this->t13->setVisible(true);
          break;
        default:
          break;
      }
    });

    next13->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next13->setVisible(false);
          this->t13->setVisible(false);

          this->ministry_of_education->setZOrder(3);
          this->ministry_of_technology->setZOrder(3);

          this->ministry_of_culture->setZOrder(11);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.42, origin.y + visible_size.height * 0.42));

          this->next14->setVisible(true);
          this->t14->setVisible(true);
          break;
        default:
          break;
      }
    });

    next14->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next14->setVisible(false);
          this->t14->setVisible(false);

          this->ministry_of_culture->setZOrder(3);

          this->background_resources->setZOrder(11);
          this->run_week_button->setZOrder(11);
          this->sunny->setZOrder(11);

          this->_happinessLabel->setZOrder(11);
          this->_happinessPenaltyLabel->setZOrder(11);
          this->_awarenessLabel->setZOrder(11);
          this->_waterReservesLabel->setZOrder(11);
          this->_cashLabel->setZOrder(11);
          this->_feeLabel->setZOrder(11);
          this->_populationLabel->setZOrder(11);

          skip->setPosition(Vec2(origin.x + visible_size.width * 0.47, origin.y + visible_size.height * 0.195));

          this->next15->setVisible(true);
          this->t15->setVisible(true);
          break;
        default:
          break;
      }
    });

    next15->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next15->setVisible(false);
          this->t15->setVisible(false);

          this->background_resources->setZOrder(3);
          this->run_week_button->setZOrder(3);
          this->sunny->setZOrder(3);

          this->_happinessLabel->setZOrder(3);
          this->_happinessPenaltyLabel->setZOrder(3);
          this->_awarenessLabel->setZOrder(3);
          this->_waterReservesLabel->setZOrder(3);
          this->_cashLabel->setZOrder(3);
          this->_feeLabel->setZOrder(3);
          this->_populationLabel->setZOrder(3);

          skip->setVisible(false);
          this->next16->setVisible(true);
          this->t16->setVisible(true);
          break;
        default:
          break;
      }
    });

    next16->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
          this->next16->setVisible(false);
          this->t16->setVisible(false);
          Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene()));
          break;
        default:
          break;
      }
    });

    this->addChild(next1, 11);
    this->addChild(next2, 11);
    this->addChild(next3, 11);
    this->addChild(next4, 11);
    this->addChild(next5, 11);
    this->addChild(next6, 11);
    this->addChild(next7, 11);
    this->addChild(next8, 11);
    this->addChild(next9, 11);
    this->addChild(next10, 11);
    this->addChild(next11, 11);
    this->addChild(next12, 11);
    this->addChild(next13, 11);
    this->addChild(next14, 11);
    this->addChild(next15, 11);
    this->addChild(next16, 11);
}