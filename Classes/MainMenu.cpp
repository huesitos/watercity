#include "MainMenu.h"


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

	background = Sprite::create("images/mainmenu.png");
	background->setPosition(Vec2(origin.x, origin.y + visibleSize.height));
	background->setAnchorPoint(Vec2(Vec2::ANCHOR_TOP_LEFT));

	this->addChild(background, 1);

	setup_listener();

	return true;
}

void MainMenu::start_game()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, TutorialScene::createScene()));
}

void MainMenu::exit_game()
{
	Director::getInstance()->end();
}

void MainMenu::setup_listener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MainMenu::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MainMenu::on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event)
{
	disable_listener();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->background->runAction(
		Sequence::create(
			MoveBy::create(3.0f, Vec2(0, background->getContentSize().height-visibleSize.height)),
			CallFunc::create(CC_CALLBACK_0(MainMenu::start_game, this)),
			nullptr
			)
		);

	return true;
}

void MainMenu::disable_listener()
{
	listener->setEnabled(false);
}