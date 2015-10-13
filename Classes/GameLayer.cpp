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

	auto bg = Sprite::create("Background.jpg");
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg->setPosition(origin);
	bg->setScaleX(visible_size.width / bg->getContentSize().width);
	bg->setScaleY(visible_size.height / bg->getContentSize().height);

	this->addChild(bg, 1);

	ministry_of_technology = MinistryOfTechnology::create("tech.png");
	ministry_of_technology->setPosition(origin.x + visible_size.width/2, origin.y + visible_size.height/2);

	this->addChild(ministry_of_technology, 2);

    ministry_of_education = MinistryOfEducation::create("tech.png");
    ministry_of_education->setPosition(origin.x + visible_size.width/2 - 100, origin.y + visible_size.height/2 - 100);

    this->addChild(ministry_of_education, 2);

    ministry_of_culture = MinistryOfCulture::create("tech.png");
    ministry_of_culture->setPosition(origin.x + visible_size.width/2 + 100, origin.y + visible_size.height/2 + 100);

    this->addChild(ministry_of_culture, 2);

	run_week_button = ui::Button::create("run_week.png");
	run_week_button->setPosition(Vec2(origin.x + visible_size.width - run_week_button->getContentSize().width,
									  origin.y + run_week_button->getContentSize().height));
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

    add_button = ui::Button::create("add.png");
    add_button->setPosition(Vec2(origin.x + visible_size.width - add_button->getContentSize().width,
                                      origin.y + 100));
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


    substract_button = ui::Button::create("substract.png");
    substract_button->setPosition(Vec2(origin.x + visible_size.width - substract_button->getContentSize().width,
                                      origin.y + (80 - substract_button->getContentSize().height)));
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
}

void GameLayer::update_labels()
{
    _happinessLabel->setString(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_happiness()));
    _happinessPenaltyLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_happiness_penalty()));
    _awarenessLabel->setString(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_awareness()));
    _waterReservesLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_water_reserves()));
    _waterInflowLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_water_inflow()));
    _selectedWaterConsumptionLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_selected_water_consumption()));
    _actualWaterConsumptionLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_actual_water_consumption()));
    _desiredWaterConsumptionLabel->setString(StringUtils::format("%d", ResourceManager::getInstance().get_desired_water_consumption()));
    _cashLabel->setString(StringUtils::format("$ %d", ResourceManager::getInstance().get_cash_total()));
    _monthlyTaxesLabel->setString(StringUtils::format("$ %d",
            ResourceManager::getInstance().get_fee_per_family() * ResourceManager::getInstance().get_number_of_families()));
    _projectLabel->setString(StringUtils::format("%s: %d", ministry_of_technology->get_current_project()->get_name().c_str(),
        static_cast<int>(ministry_of_technology->is_project_running())));
}

void GameLayer::add_labels()
{
    int xLoc = origin.x + visible_size.width/64;
    int fontSize = 18;
    int xGap = 15;

    _happinessSprite = Sprite::create("happiness.png");
    _happinessSprite->setPosition(Vec2(xLoc, origin.y + visible_size.height*15/16));
    _happinessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_happiness()), "fonts/Marker Felt.ttf", fontSize);
    _happinessLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*15/16));

    _awarenessSprite = Sprite::create("awareness.png");
    _awarenessSprite->setPosition(Vec2(xLoc, origin.y + visible_size.height*14/16));
    _awarenessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", ResourceManager::getInstance().get_awareness()), "fonts/Marker Felt.ttf", fontSize);
    _awarenessLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*14/16));

    _waterReservesSprite = Sprite::create("reserves.png");
    _waterReservesSprite->setPosition(Vec2(xLoc, origin.y + visible_size.height*13/16));
    _waterReservesLabel = Label::createWithTTF(StringUtils::format("%d",
            ResourceManager::getInstance().get_water_reserves()), "fonts/Marker Felt.ttf", fontSize);
    _waterReservesLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*13/16));

    _waterInflowLabel = Label::createWithTTF(StringUtils::format("%d", ResourceManager::getInstance().get_water_inflow()), "fonts/Marker Felt.ttf", fontSize);
    _waterInflowLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*12/16));

    _waterConsumptionSprite = Sprite::create("consumption.png");
    _waterConsumptionSprite->setPosition(Vec2(xLoc, origin.y + visible_size.height*11/16));
    _selectedWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d",
            ResourceManager::getInstance().get_selected_water_consumption()), "fonts/Marker Felt.ttf", fontSize);
    _selectedWaterConsumptionLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*11/16));

    _actualWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d",
            ResourceManager::getInstance().get_actual_water_consumption()), "fonts/Marker Felt.ttf", fontSize);
    _actualWaterConsumptionLabel->setPosition(Vec2(xLoc + 100, origin.y + visible_size.height*11/16));

    _desiredWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d",
            ResourceManager::getInstance().get_desired_water_consumption()), "fonts/Marker Felt.ttf", fontSize);
    _desiredWaterConsumptionLabel->setPosition(Vec2(xLoc + 200, origin.y + visible_size.height*11/16));

    _cashSprite = Sprite::create("cash.png");
    _cashSprite->setPosition(Vec2(xLoc, origin.y + visible_size.height*10/16));
    _cashLabel = Label::createWithTTF(StringUtils::format("$ %d", ResourceManager::getInstance().get_cash_total()), "fonts/Marker Felt.ttf", fontSize);
    _cashLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*10/16));

    _monthlyTaxesLabel = Label::createWithTTF(StringUtils::format("$ %d",
            ResourceManager::getInstance().get_fee_per_family() * ResourceManager::getInstance().get_number_of_families()), "fonts/Marker Felt.ttf", fontSize);
    _monthlyTaxesLabel->setPosition(Vec2(xLoc + xGap, origin.y + visible_size.height*9/16));

    _projectLabel = Label::createWithTTF(StringUtils::format("%s: %d", ministry_of_technology->get_current_project()->get_name().c_str(),
        static_cast<int>(ministry_of_technology->is_project_running())), "fonts/Marker Felt.ttf", fontSize);
    _projectLabel->setPosition(Vec2(origin.x + visible_size.width * 3 / 4,
                                    origin.y + _projectLabel->getContentSize().height));

    _happinessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _awarenessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterReservesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterInflowLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _selectedWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _actualWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _desiredWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _cashLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _monthlyTaxesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _projectLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    _happinessLabel->setTextColor(Color4B::BLACK);
    _awarenessLabel->setTextColor(Color4B::BLACK);
    _waterReservesLabel->setTextColor(Color4B::BLACK);
    _waterInflowLabel->setTextColor(Color4B::BLACK);
    _selectedWaterConsumptionLabel->setTextColor(Color4B::BLACK);
    _actualWaterConsumptionLabel->setTextColor(Color4B::BLACK);
    _desiredWaterConsumptionLabel->setTextColor(Color4B::BLACK);
    _cashLabel->setTextColor(Color4B::BLACK);
    _monthlyTaxesLabel->setTextColor(Color4B::BLACK);

    this->addChild(_happinessLabel, 1);
    this->addChild(_awarenessLabel, 1);
    this->addChild(_waterReservesLabel, 1);
    this->addChild(_waterInflowLabel, 1);
    this->addChild(_selectedWaterConsumptionLabel, 1);
    this->addChild(_actualWaterConsumptionLabel, 1);
    this->addChild(_desiredWaterConsumptionLabel, 1);
    this->addChild(_cashLabel, 1);
    this->addChild(_monthlyTaxesLabel, 1);
    this->addChild(_projectLabel, 1);

    this->addChild(_happinessSprite, 1);
    this->addChild(_awarenessSprite, 1);
    this->addChild(_waterReservesSprite, 1);
    this->addChild(_waterConsumptionSprite, 1);
    this->addChild(_cashSprite, 1);

    auto happinessPenaltySprite = Sprite::create("happiness.png");
    happinessPenaltySprite->setPosition(Vec2(origin.x + visible_size.width - 100, origin.y + 150));
    _happinessPenaltyLabel = Label::createWithTTF(StringUtils::format("%d", ResourceManager::getInstance().get_happiness_penalty()), "fonts/Marker Felt.ttf", fontSize);
    _happinessPenaltyLabel->setPosition(Vec2(origin.x + visible_size.width - 50, origin.y + 150));

    this->addChild(happinessPenaltySprite, 1);
    this->addChild(_happinessPenaltyLabel, 1);
}
