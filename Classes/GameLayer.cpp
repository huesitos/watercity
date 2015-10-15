#include "GameLayer.h"
#include "Breakdown.h"
#include "ProhibitedAct.h"
#include "Rain.h"

Scene* GameLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GameLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visible_size = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	top_right.x = origin.x + visible_size.width;
    top_right.y = origin.y + visible_size.height;

    background_town = Sprite::create("back.png");
    background_town->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_town->setPosition(origin);

    this->addChild(background_town, 1);

    background_menu = Sprite::create("menuback.png");
	background_menu->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background_menu->setPosition(origin);

	this->addChild(background_menu, 1);

	ministry_of_technology = MinistryOfTechnology::create("ministerioboton.png", "tech_projects.txt");
	ministry_of_technology->setPosition(origin.x + visible_size.width * 0.53, origin.y + visible_size.height * 0.66);

	this->addChild(ministry_of_technology, 1);

    ministry_of_education = MinistryOfEducation::create("ministerioboton.png", "tech_projects.txt");
    ministry_of_education->setPosition(origin.x + visible_size.width * 0.64, origin.y + visible_size.height * 0.58);

    this->addChild(ministry_of_education, 1);

    ministry_of_culture = MinistryOfCulture::create("ministerioboton.png", "tech_projects.txt");
    ministry_of_culture->setPosition(origin.x + visible_size.width * 0.75, origin.y + visible_size.height * 0.50);

    this->addChild(ministry_of_culture, 1);

	run_week_button = ui::Button::create("start.png");
	run_week_button->setPosition(Vec2(origin.x + visible_size.width * 0.95 - run_week_button->getContentSize().width / 2,
									  origin.y + visible_size.height * 0.05 + run_week_button->getContentSize().height / 2));
	run_week_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
			case ui::Widget::TouchEventType::BEGAN:
				this->run_week();
				break;
			default:
				break;
		}
	});

    this->addChild(run_week_button, 2);

    add_button = ui::Button::create("plus.png");
    add_button->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.15));
    add_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                rm.increase_selected_consumption(100);
                this->update_labels();
                break;
            default:
                break;
        }
    });

    this->addChild(add_button, 2);

    substract_button = ui::Button::create("minus.png");
    substract_button->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.08));
    substract_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                rm.decrease_selected_consumption(100);
                this->update_labels();
                break;
            default:
                break;
        }
    });

    this->addChild(substract_button, 2);

    add_labels();

    return true;
}

void GameLayer::run_day()
{
    ministry_of_technology->develop_project();
    ministry_of_education->develop_project();
	ministry_of_culture->develop_project();
    Rain::rain();

    rm.update_day();
}

void GameLayer::run_week()
{
    for (int i = 0; i < 7; ++i)
        run_day();

    update_labels();
    if (rm.is_water_depleted())
    {
        game_over();
    }
}

void GameLayer::update_labels()
{
    _happinessLabel->setString(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_happiness()));
    _happinessPenaltyLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_happiness_penalty() * 7));
    _awarenessLabel->setString(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_awareness()));
    _waterReservesLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_water_reserves()));
    _selectedWaterConsumptionLabel->setString(StringUtils::format("%d gl", ResourceManager::getInstance().get_selected_water_consumption()));
    // _actualWaterConsumptionLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_actual_water_consumption()));
    // _desiredWaterConsumptionLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_desired_water_consumption()));
    _cashLabel->setString(StringUtils::format("$ %d", ResourceManager::getInstance().get_cash_total()));
    _populationLabel->setString(StringUtils::format("%d / %d",
        ResourceManager::getInstance().get_population_occupied(),
        ResourceManager::getInstance().get_population_total()));

    int current_num_lines = (rm.get_selected_water_consumption() - rm.get_desired_water_consumption()) / 100;
    int i = 0;

    auto wl = Sprite::create("consumptionup.png");
    actual_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.057, origin.y + visible_size.height * 0.080)
            + Vec2(0, wl->getContentSize().height * 0.70) * num_of_water_lines);

    for (; i < current_num_lines; ++i)
    {
        water_lines.at(i)->setVisible(true);
    }
    for (; i < num_of_water_lines; ++i)
    {
        water_lines.at(i)->setVisible(false);
    }
}

void GameLayer::add_labels()
{
    int fontSize = 18;

    _happinessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_happiness()), "fonts/Marker Felt.ttf", fontSize);
    _happinessLabel->setPosition(Vec2(origin.x + visible_size.width * 0.70, origin.y + visible_size.height * 0.125));

    _awarenessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_awareness()), "fonts/Marker Felt.ttf", fontSize);
    _awarenessLabel->setPosition(Vec2(origin.x + visible_size.width * 0.60, origin.y + visible_size.height * 0.06));

    _waterReservesLabel = Label::createWithTTF(StringUtils::format("%d",
            ResourceManager::getInstance().get_water_reserves()), "fonts/Marker Felt.ttf", fontSize);
    _waterReservesLabel->setPosition(Vec2(origin.x + visible_size.width * 0.92, origin.y + visible_size.height * 0.315));

    // _actualWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d gl",
    //         ResourceManager::getInstance().get_actual_water_consumption()), "fonts/Marker Felt.ttf", 12);
    // _actualWaterConsumptionLabel->setPosition(Vec2(origin.x + visible_size.width*0.03, origin.y + visible_size.height*0.16));

    _selectedWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d gl",
            ResourceManager::getInstance().get_selected_water_consumption()), "fonts/Marker Felt.ttf", fontSize);
    _selectedWaterConsumptionLabel->setPosition(Vec2(origin.x + visible_size.width*0.035, origin.y + visible_size.height*0.06));

    // _desiredWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d gl",
    //         ResourceManager::getInstance().get_desired_water_consumption()), "fonts/Marker Felt.ttf", 12);
    // _desiredWaterConsumptionLabel->setPosition(Vec2(origin.x + visible_size.width*0.03, origin.y + visible_size.height*0.08));

    _cashLabel = Label::createWithTTF(StringUtils::format("$ %d", ResourceManager::getInstance().get_cash_total()), "fonts/Marker Felt.ttf", fontSize);
    _cashLabel->setPosition(Vec2(origin.x + visible_size.width * 0.86, origin.y + visible_size.height * 0.255));

    _populationLabel = Label::createWithTTF(StringUtils::format("%d / %d",
        ResourceManager::getInstance().get_population_occupied(), ResourceManager::getInstance().get_population_total()),
        "fonts/Marker Felt.ttf", fontSize);
    _populationLabel->setPosition(Vec2(origin.x + visible_size.width * 0.77, origin.y + visible_size.height * 0.19));

    _happinessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _awarenessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterReservesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _selectedWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    // _actualWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    // _desiredWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _cashLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _populationLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

    _happinessLabel->setTextColor(Color4B::WHITE);
    _awarenessLabel->setTextColor(Color4B::WHITE);
    _waterReservesLabel->setTextColor(Color4B::WHITE);
    _selectedWaterConsumptionLabel->setTextColor(Color4B::BLACK);
    // _actualWaterConsumptionLabel->setTextColor(Color4B::BLACK);
    // _desiredWaterConsumptionLabel->setTextColor(Color4B::WHITE);
    _cashLabel->setTextColor(Color4B::WHITE);
    _populationLabel->setTextColor(Color4B::WHITE);

    this->addChild(_happinessLabel, 3);
    this->addChild(_awarenessLabel, 3);
    this->addChild(_waterReservesLabel, 3);
    this->addChild(_selectedWaterConsumptionLabel, 3);
    // this->addChild(_actualWaterConsumptionLabel, 3);
    // this->addChild(_desiredWaterConsumptionLabel, 3);
    this->addChild(_cashLabel, 3);
    this->addChild(_populationLabel, 3);

    auto happinessPenaltySprite = Sprite::create("happy.png");
    happinessPenaltySprite->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.02));
    _happinessPenaltyLabel = Label::createWithTTF(StringUtils::format("%d", ResourceManager::getInstance().get_happiness_penalty()), "fonts/Marker Felt.ttf", fontSize);
    _happinessPenaltyLabel->setPosition(Vec2(origin.x + visible_size.width * 0.14, origin.y + visible_size.height * 0.02));

    this->addChild(happinessPenaltySprite, 3);
    this->addChild(_happinessPenaltyLabel, 3);

    num_of_water_lines = (rm.get_actual_water_consumption()-rm.get_desired_water_consumption())/100;

    desired_consumption = Sprite::create("need.png");
    actual_consumption = Sprite::create("want.png");

    // el actual deberia tener el mismo height?
    auto wl = Sprite::create("consumptionup.png");

    desired_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.057, origin.y + visible_size.height * 0.080)
            + Vec2(0, desired_consumption->getContentSize().height * 0.70));
    actual_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.057, origin.y + visible_size.height * 0.080)
            + Vec2(0, wl->getContentSize().height * 0.70) * num_of_water_lines);

    this->addChild(desired_consumption, 3);
    this->addChild(actual_consumption, 2);

    printf("%d\n", num_of_water_lines);

    for (int i = 0; i < num_of_water_lines; ++i)
    {
        auto wl = Sprite::create("consumptionup.png");
        wl->setPosition(Vec2(origin.x + visible_size.width * 0.057, origin.y + visible_size.height * 0.083)
            + Vec2(0, wl->getContentSize().height * 0.70) * i);
        wl->setVisible(false);

        this->addChild(wl, 1);
        water_lines.pushBack(wl);
    }

    int current_num_lines = (rm.get_selected_water_consumption() - rm.get_desired_water_consumption()) / 100;
    for (int i = 0; i < current_num_lines; ++i)
    {
        water_lines.at(i)->setVisible(true);
    }
}

void GameLayer::game_over()
{
    auto gameOver = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 50);
    gameOver->setPosition(visible_size.width/2, visible_size.height/2);

    this->addChild(gameOver, 10);

    auto main_menu = ui::Button::create("play.png");
    main_menu->setPosition(Vec2(origin.x + visible_size.width/2,
                                      origin.y + visible_size.height/2 + - main_menu->getContentSize().height));
    main_menu->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene()));
                break;
            default:
                break;
        }

        return true;
    });

    this->addChild(main_menu, 10);
}
