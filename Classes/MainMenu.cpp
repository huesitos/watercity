#include "MainMenu.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto start_image = MenuItemImage::create("play.png", "play.png", CC_CALLBACK_1(MainMenu::start_game, this));
	start_image->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 3 / 4));

	auto exit_image = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(MainMenu::exit_game, this));
	exit_image->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 1 / 4));

	auto menu = Menu::create(start_image, exit_image, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainMenu::start_game(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene()));
}

void MainMenu::exit_game(Ref *pSender)
{
	Director::getInstance()->end();
}
