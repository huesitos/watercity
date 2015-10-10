#include "Ministerio.h"

Ministerio::Ministerio()
{}

Ministerio::~Ministerio()
{}

bool Ministerio::init()
{
	Project proj;

	proj.set_name("Level 2 Pipes");
	proj.set_description("Upgrade the pipes in the neighborhood to reduce the rate of water consumption.");
	proj.set_completion_time(20.0f);
	proj.set_water_cost(600);
	proj.set_cash_cost(250);

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto button = Button::create("BlueBackground.png");
	button->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(button);

	auto buttonSize = button->getContentSize();

	auto label = Label::createWithTTF(proj.get_name(), "fonts/Marker Felt.ttf", 7);
	label->setDimensions(buttonSize.width/4, buttonSize.height/4);
	label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	label->setPosition(Vec2(0, buttonSize.height*3/4));
	button->addChild(label);

	label = Label::createWithTTF(proj.get_description(), "fonts/Marker Felt.ttf", 6);
	label->setDimensions(buttonSize.width*3/4, buttonSize.height*3/4);
	label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	label->setPosition(Vec2(buttonSize.width/4, buttonSize.height/4));
	button->addChild(label);

	return true;
}
