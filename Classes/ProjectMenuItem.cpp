#include "ProjectMenuItem.h"
#include "ResourceManager.h"

void ProjectMenuItem::setup(Project* project)
{
	this->project = project;

	filled = false;

	Size visible_size = Director::getInstance()->getVisibleSize();

	this->setScaleX((visible_size.width * 3 / 4) / (this->getContentSize().width));
	this->setScaleY((visible_size.height * 1 / 4) / (this->getContentSize().height));

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

	Size rect_size = this->getBoundingBox().size;

	project_image = Sprite::create("project.png");
	project_image->setScaleX((rect_size.width * 1 / 4) / (project_image->getContentSize().width));
	project_image->setScaleY((rect_size.height * 2 / 3) / (project_image->getContentSize().height));
	project_image->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	project_image->setPosition(Vec2(-(rect_size.width / 2), -(rect_size.height)));

	this->addChild(project_image, 1);

	fill_button = Sprite::create("checkmark.png");
	fill_button->setScaleX((rect_size.width * 1 / 4) / (fill_button->getContentSize().width));
	fill_button->setScaleY((rect_size.height * 1 / 2) / (fill_button->getContentSize().height));
	fill_button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	fill_button->setPosition(Vec2(rect_size.width / 2, 0));

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [this] (Touch* touch, Event* event) {
		if (!this->is_filled() && ResourceManager::getInstance().has_enough_unoccupied(this->project->get_persons_needed()))
		{
			this->set_filled(true);
			ResourceManager::getInstance().occupy_persons(this->project->get_persons_needed());

			this->update_labels();

			return true;
		}
	};

	fill_button->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, fill_button);

	this->addChild(fill_button, 1);

	empty_button = Sprite::create("crossmark.png");
	empty_button->setScaleX((rect_size.width * 1 / 4) / (empty_button->getContentSize().width));
	empty_button->setScaleY((rect_size.height * 1 / 2) / (empty_button->getContentSize().height));
	empty_button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	empty_button->setPosition(Vec2(rect_size.width / 2, -(rect_size.height / 2)));

	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [this] (Touch* touch, Event* event) {
		if (this->is_filled())
		{
			this->set_filled(false);
			ResourceManager::getInstance().unoccupy_persons(this->project->get_persons_needed());

			this->update_labels();

			return true;
		}
	};

	empty_button->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, empty_button);

	this->addChild(empty_button, 1);

	int font_size = 8;

	name_label = Label::createWithTTF(project->get_name(), "fonts/Marker Felt.ttf", font_size);
	name_label->setDimensions((rect_size.width * 1 / 4), (rect_size.height * 1 / 3));
	name_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	name_label->setPosition(Vec2(-(rect_size.width * 1 / 2), 0));
	name_label->setTextColor(Color4B::BLACK);

	this->addChild(name_label, 1);

	description_label = Label::createWithTTF(project->get_description(), "fonts/Marker Felt.ttf", font_size);
	description_label->setDimensions((rect_size.width * 1 / 2), (rect_size.height * 1 / 2));
	description_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	description_label->setPosition(Vec2(-(rect_size.width * 1 / 4), 0));
	description_label->setTextColor(Color4B::BLACK);

	this->addChild(description_label, 1);

	cash_label = Label::createWithTTF(StringUtils::format("$ %d", project->get_cash_cost()), "fonts/Marker Felt.ttf", font_size);
	cash_label->setDimensions((rect_size.width * 1 / 8), (rect_size.height * 1 / 2));
	cash_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cash_label->setPosition(Vec2(-(rect_size.width * 1 / 4), -(rect_size.height)));
	cash_label->setTextColor(Color4B::BLACK);

	this->addChild(cash_label, 1);

	water_label = Label::createWithTTF(StringUtils::format("Water: %d", project->get_water_cost()), "fonts/Marker Felt.ttf", font_size);
	water_label->setDimensions((rect_size.width * 1 / 8), (rect_size.height * 1 / 2));
	water_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	water_label->setPosition(Vec2(-(rect_size.width * 1 / 8), -(rect_size.height)));
	water_label->setTextColor(Color4B::BLACK);

	this->addChild(water_label, 1);

	persons_label = Label::createWithTTF(StringUtils::format("0 / %d persons", project->get_persons_needed()), "fonts/Marker Felt.ttf", font_size);
	persons_label->setDimensions((rect_size.width * 1 / 8), (rect_size.height * 1 / 2));
	persons_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	persons_label->setPosition(Vec2(0, -(rect_size.height)));
	persons_label->setTextColor(Color4B::BLACK);

	this->addChild(persons_label, 1);

	time_label = Label::createWithTTF(StringUtils::format("0 / %d days", project->get_completion_time()), "fonts/Marker Felt.ttf", font_size);
	time_label->setDimensions((rect_size.width * 1 / 8), (rect_size.height * 1 / 2));
	time_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	time_label->setPosition(Vec2((rect_size.width * 1 / 8), -(rect_size.height)));
	time_label->setTextColor(Color4B::BLACK);

	this->addChild(time_label, 1);
}

void ProjectMenuItem::update_labels()
{
	persons_label->setString(StringUtils::format("%d / %d persons", is_filled() ? project->get_persons_needed() : 0, project->get_persons_needed()));
	time_label->setString(StringUtils::format("%d / %d days", project->get_time_completed(), project->get_completion_time()));
}
