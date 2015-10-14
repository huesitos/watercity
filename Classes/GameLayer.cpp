#include "GameLayer.h"
#include "Breakdown.h"
#include "ProhibitedAct.h"


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

	this->addChild(bg, 1);

	technological_ministry = Ministry::create("tech.png");
	technological_ministry->setPosition(origin.x + visible_size.width/2, origin.y + visible_size.height/2);

	this->addChild(technological_ministry, 2);

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

	add_labels();

	return true;
}

void GameLayer::run_day()
{
	technological_ministry->develop_project();

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
	_happinessLabel->setString(StringUtils::format("Happiness: %.0f%%", ResourceManager::getInstance().get_happiness()));
    _awarenessLabel->setString(StringUtils::format("Awareness: %.0f%%", ResourceManager::getInstance().get_awareness()));
    _waterReservesLabel->setString(StringUtils::format("Water Reserves: %d", ResourceManager::getInstance().get_water_reserves()));
    _waterInflowLabel->setString(StringUtils::format("Water Inflow: %d", ResourceManager::getInstance().get_water_inflow()));
    _waterConsumptionLabel->setString(StringUtils::format("Water Consumption: %d", ResourceManager::getInstance().get_water_consumption()));
    _cashLabel->setString(StringUtils::format("Cash: $ %d", ResourceManager::getInstance().get_cash_total()));
    _monthlyTaxesLabel->setString(StringUtils::format("Monthly Taxes (p/min): $ %d", 
            ResourceManager::getInstance().get_fee_per_family() * ResourceManager::getInstance().get_number_of_families()));
    _projectLabel->setString(StringUtils::format("%s: %d", technological_ministry->get_current_project()->get_name().c_str(), 
    	static_cast<int>(technological_ministry->is_project_running())));
}

void GameLayer::add_labels()
{
	int xLoc = origin.x + visible_size.width/64;
    int fontSize = 20;

    _happinessLabel = Label::createWithTTF(StringUtils::format("Happiness: %.0f%%", ResourceManager::getInstance().get_happiness()), "fonts/Marker Felt.ttf", fontSize);
    _happinessLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*15/16));

    _awarenessLabel = Label::createWithTTF(StringUtils::format("Awareness: %.0f%%", ResourceManager::getInstance().get_awareness()), "fonts/Marker Felt.ttf", fontSize);
    _awarenessLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*14/16));

    _waterReservesLabel = Label::createWithTTF(StringUtils::format("Water Reserves: %d", 
            ResourceManager::getInstance().get_water_reserves()), "fonts/Marker Felt.ttf", fontSize);
    _waterReservesLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*13/16));

    _waterInflowLabel = Label::createWithTTF(StringUtils::format("Water Inflow: %d", ResourceManager::getInstance().get_water_inflow()), "fonts/Marker Felt.ttf", fontSize);
    _waterInflowLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*12/16));

    _waterConsumptionLabel = Label::createWithTTF(StringUtils::format("Water Consumption: %d", 
            ResourceManager::getInstance().get_water_consumption()), "fonts/Marker Felt.ttf", fontSize);
    _waterConsumptionLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*11/16));

    _cashLabel = Label::createWithTTF(StringUtils::format("Cash: $ %d", ResourceManager::getInstance().get_cash_total()), "fonts/Marker Felt.ttf", fontSize);
    _cashLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*10/16));

    _monthlyTaxesLabel = Label::createWithTTF(StringUtils::format("Monthly Taxes (p/min): $ %d", 
            ResourceManager::getInstance().get_fee_per_family() * ResourceManager::getInstance().get_number_of_families()), "fonts/Marker Felt.ttf", fontSize);
    _monthlyTaxesLabel->setPosition(Vec2(xLoc, origin.y + visible_size.height*9/16));

    _projectLabel = Label::createWithTTF(StringUtils::format("%s: %d", technological_ministry->get_current_project()->get_name().c_str(), 
    	static_cast<int>(technological_ministry->is_project_running())), "fonts/Marker Felt.ttf", fontSize);
    _projectLabel->setPosition(Vec2(origin.x + visible_size.width * 3 / 4, 
    								origin.y + _projectLabel->getContentSize().height));

    _happinessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _awarenessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterReservesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterInflowLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _cashLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _monthlyTaxesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _projectLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

    _happinessLabel->setTextColor(Color4B::BLACK);
    _awarenessLabel->setTextColor(Color4B::BLACK);
    _waterReservesLabel->setTextColor(Color4B::BLACK);
    _waterInflowLabel->setTextColor(Color4B::BLACK);
    _waterConsumptionLabel->setTextColor(Color4B::BLACK);
    _cashLabel->setTextColor(Color4B::BLACK);
    _monthlyTaxesLabel->setTextColor(Color4B::BLACK);

    this->addChild(_happinessLabel, 1);
    this->addChild(_awarenessLabel, 1);
    this->addChild(_waterReservesLabel, 1);
    this->addChild(_waterInflowLabel, 1);
    this->addChild(_waterConsumptionLabel, 1);
    this->addChild(_cashLabel, 1);
    this->addChild(_monthlyTaxesLabel, 1);
    this->addChild(_projectLabel, 1);
}
