#include "ProjectMenuItem.h"
#include "ResourceManager.h"

void ProjectMenuItem::setup(Project* project)
{
	this->project = project;

	filled = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [this] (Touch* touch, Event* event) {
		if (this->getBoundingBox().containsPoint(touch->getLocation()))
		{
			return true;
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Size visible_size = Director::getInstance()->getVisibleSize();

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

	Size rect_size = this->getBoundingBox().size;

	project_image = Sprite::create("project.png");
	project_image->setScaleX((rect_size.width * 1 / 4) / (project_image->getContentSize().width) / this->getScaleX());
	project_image->setScaleY((rect_size.height * 2 / 3) / (project_image->getContentSize().height) / this->getScaleY());
	project_image->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	this->addChild(project_image, 1);

	fill_button = ui::Button::create("checkmark.png");
	fill_button->setScaleX((rect_size.width * 1 / 4) / (fill_button->getContentSize().width) / this->getScaleX());
	fill_button->setScaleY((rect_size.height * 1 / 2) / (fill_button->getContentSize().height) / this->getScaleY());
	fill_button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	fill_button->setPosition(Vec2(rect_size.width, rect_size.height));

	fill_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
			case ui::Widget::TouchEventType::BEGAN:
				if (!this->is_filled() && ResourceManager::getInstance().has_enough_unoccupied(this->project->get_persons_needed()))
				{
					this->set_filled(true);
					ResourceManager::getInstance().occupy_persons(this->project->get_persons_needed());

					this->update_labels();

					return true;
				}
				break;
			default:
				break;
		}
	});

	this->addChild(fill_button, 1);

	empty_button = ui::Button::create("crossmark.png");
	empty_button->setScaleX((rect_size.width * 1 / 4) / (empty_button->getContentSize().width) / this->getScaleX());
	empty_button->setScaleY((rect_size.height * 1 / 2) / (empty_button->getContentSize().height) / this->getScaleY());
	empty_button->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	empty_button->setPosition(Vec2(rect_size.width, rect_size.height / 2));

	empty_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
			case ui::Widget::TouchEventType::BEGAN:
				if (this->is_filled())
				{
					this->set_filled(false);
					ResourceManager::getInstance().unoccupy_persons(this->project->get_persons_needed());

					this->update_labels();

					return true;
				}
				break;
			default:
				break;
		}
	});

	this->addChild(empty_button, 1);

	int font_size = 20;

	name_label = Label::createWithTTF(project->get_name(), "fonts/Marker Felt.ttf", font_size);
	name_label->setDimensions((rect_size.width * 3 / 4), (rect_size.height * 1 / 3));
	name_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	name_label->setPosition(Vec2(0, rect_size.height));
	name_label->setTextColor(Color4B::BLACK);
	name_label->setScale(1 / this->getScaleX(), 1 / this->getScaleY());

	this->addChild(name_label, 1);

	description_label = Label::createWithTTF(project->get_description(), "fonts/Marker Felt.ttf", font_size);
	description_label->setDimensions((rect_size.width * 1 / 2), (rect_size.height * 1 / 3));
	description_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	description_label->setPosition(Vec2(rect_size.width * 1 / 4, rect_size.height * 2 / 3));
	description_label->setTextColor(Color4B::BLACK);
	description_label->setScale(1 / this->getScaleX(), 1 / this->getScaleY());

	this->addChild(description_label, 1);

	cash_label = Label::createWithTTF(StringUtils::format("$ %d", project->get_cash_cost()), "fonts/Marker Felt.ttf", font_size);
	cash_label->setDimensions((rect_size.width * 1 / 2), (rect_size.height * 1 / 6));
	cash_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cash_label->setPosition(Vec2((rect_size.width * 1 / 4), 0));
	cash_label->setTextColor(Color4B::BLACK);
	cash_label->setScale(1 / this->getScaleX(), 1 / this->getScaleY());

	this->addChild(cash_label, 1);

	water_label = Label::createWithTTF(StringUtils::format("Water: %d", project->get_water_cost()), "fonts/Marker Felt.ttf", font_size);
	water_label->setDimensions((rect_size.width * 1 / 2), (rect_size.height * 1 / 6));
	water_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	water_label->setPosition(Vec2((rect_size.width * 1 / 4) + (rect_size.width * 1 / 8), 0));
	water_label->setTextColor(Color4B::BLACK);
	water_label->setScale(1 / this->getScaleX(), 1 / this->getScaleY());

	this->addChild(water_label, 1);

	persons_label = Label::createWithTTF(StringUtils::format("0 / %d persons", project->get_persons_needed()), "fonts/Marker Felt.ttf", font_size);
	persons_label->setDimensions((rect_size.width * 1 / 2), (rect_size.height * 1 / 6));
	persons_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	persons_label->setPosition(Vec2((rect_size.width * 1 / 4) + (rect_size.width * 2 / 8), 0));
	persons_label->setTextColor(Color4B::BLACK);
	persons_label->setScale(1 / this->getScaleX(), 1 / this->getScaleY());

	this->addChild(persons_label, 1);

	time_label = Label::createWithTTF(StringUtils::format("0 / %d days", project->get_completion_time()), "fonts/Marker Felt.ttf", font_size);
	time_label->setDimensions((rect_size.width * 1 / 2), (rect_size.height * 1 / 6));
	time_label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	time_label->setPosition(Vec2((rect_size.width * 1 / 4) + (rect_size.width * 3 / 8), 0));
	time_label->setTextColor(Color4B::BLACK);
	time_label->setScale(1 / this->getScaleX(), 1 / this->getScaleY());

	this->addChild(time_label, 1);
}

void ProjectMenuItem::update_labels()
{
	persons_label->setString(StringUtils::format("%d / %d persons", is_filled() ? project->get_persons_needed() : 0, project->get_persons_needed()));
	time_label->setString(StringUtils::format("%d / %d days", project->get_time_completed(), project->get_completion_time()));
}
