#include "GameLayer.h"

USING_NS_CC;

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

	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Background.jpg");
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg->setPosition(origin);
	bg->setScaleX(visible_size.width / bg->getContentSize().width);
	bg->setScaleY(visible_size.height / bg->getContentSize().height);

	this->addChild(bg, 1);

	return true;
}
