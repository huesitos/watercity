#include "ProjectMenuItem.h"
#include "ResourceManager.h"
#include "GameLayer.h"

void ProjectMenuItem::setup(Ministry* ministry)
{
	this->ministry = ministry;

	filled = false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [this] (Touch* touch, Event* event) {
		if (this->isVisible() && this->getBoundingBox().containsPoint(touch->getLocation()))
		{
			return true;
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Size rect_size = this->getBoundingBox().size;

	update_projects();

	// Fund/defund project
	// Assign persons and check if can be funded
	fund_project = ui::Button::create("images/fund.png");
	fund_project->setPosition(Vec2(rect_size.width * 0.70, rect_size.height * 0.20));

 	fund_project->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type){
 			auto projs = this->ministry->get_projects_to_display();
			Project* proj = nullptr;
			if (static_cast<int>(projs.size()) > 0)
				proj = projs[0];

      switch (type)
      {
        case ui::Widget::TouchEventType::BEGAN:
                break;
        case ui::Widget::TouchEventType::ENDED:
                if (proj && !proj->is_set_to_start() && !proj->is_running() && proj->can_be_funded())
								{
									proj->assign_persons_needed();
									this->ministry->start_project();
								}
                break;
        default:
                break;
      }

	    this->update_labels();
			((GameLayer*) this->getParent())->update_labels();
			return true;
	});

	this->addChild(fund_project, 1);
}

void ProjectMenuItem::update_labels()
{
	auto projs = ministry->get_projects_set_to_start();
	int num_projs = static_cast<int>(projs.size());

	int persons_on_projects = 0;
	for (int i = 0; i < num_projs; ++i)
	{
		persons_on_projects += projs[i]->get_persons_assigned();
	}

	if (num_projs == 0)
	{
		projs = ministry->get_projects_running();
		num_projs = static_cast<int>(projs.size());
		for (int i = 0; i < num_projs; ++i)
		{
			persons_on_projects += projs[i]->get_persons_assigned();
		}
	}

	projs = ministry->get_projects_to_display();
	num_projs = static_cast<int>(projs.size());

	for (int i = 0; i < num_projs; ++i)
	{
		persons_labels.at(i)->setString(StringUtils::format("%d", projs[i]->get_persons_assigned()));
		time_labels.at(i)->setString(StringUtils::format("%d / %d", projs[i]->get_time_completed(), projs[i]->get_completion_time()));
	}
}

void ProjectMenuItem::update_projects()
{
	int num_removals = static_cast<int>(name_labels.size()) * 7;

	name_labels.clear();
	description_labels.clear();
	cash_labels.clear();
	water_labels.clear();
	persons_labels.clear();
	time_labels.clear();
	change_labels.clear();

	for (int i = 0; i < num_removals; ++i)
		this->removeChildByTag(-999);

	Size rect_size = this->getContentSize();

	auto projs = ministry->get_projects_to_display();
	const int num_projs = static_cast<int>(projs.size());

	for (int i = 0; i < num_projs; ++i)
	{
		int font_size = 20;

		auto name_label = Label::createWithTTF(projs[i]->get_name(), "fonts/Marker Felt.ttf", 35);
		name_label->setDimensions(rect_size.width * 0.45, rect_size.height * 0.30);
		name_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		name_label->setPosition(Vec2(rect_size.width * 0.38, rect_size.height * 0.70));
		name_label->setTextColor(Color4B::WHITE);
		name_labels.pushBack(name_label);
		this->addChild(name_label, 1, -999);

		auto description_label = Label::createWithTTF(projs[i]->get_description(), "fonts/Marker Felt.ttf", 25);
		description_label->setDimensions(rect_size.width * 0.45, rect_size.height * 0.45);
		description_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		description_label->setPosition(Vec2(rect_size.width * 0.38, rect_size.height * 0.50));
		description_label->setTextColor(Color4B::WHITE);
		description_labels.pushBack(description_label);
		this->addChild(description_label, 1, -999);

		auto cash_label = Label::createWithTTF(StringUtils::format("%d", projs[i]->get_cash_cost()), "fonts/Marker Felt.ttf", font_size);
		/*cash_label->setDimensions(rect_size.width * 0.10, rect_size.height * 0.15);*/
		cash_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		cash_label->setPosition(Vec2(rect_size.width * 0.27, rect_size.height * 0.55));
		cash_label->setTextColor(Color4B::WHITE);
		cash_labels.pushBack(cash_label);
		this->addChild(cash_label, 1, -999);

		auto water_label = Label::createWithTTF(StringUtils::format("%d", projs[i]->get_water_cost()), "fonts/Marker Felt.ttf", font_size);
		/*water_label->setDimensions(rect_size.width * 0.10, rect_size.height * 0.15);*/
		water_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		water_label->setPosition(Vec2(rect_size.width * 0.31, rect_size.height * 0.63));
		water_label->setTextColor(Color4B::WHITE);
		water_labels.pushBack(water_label);
		this->addChild(water_label, 1, -999);

		auto persons_label = Label::createWithTTF(StringUtils::format("%d", projs[i]->get_persons_assigned()), "fonts/Marker Felt.ttf", font_size);
		/*persons_label->setDimensions(rect_size.width * 0.10, rect_size.height * 0.15);*/
		persons_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		persons_label->setPosition(Vec2(rect_size.width * 0.31, rect_size.height * 0.40));
		persons_label->setTextColor(Color4B::WHITE);
		persons_labels.pushBack(persons_label);
		this->addChild(persons_label, 1, -999);

		auto time_label = Label::createWithTTF(StringUtils::format("%d / %d", projs[i]->get_time_completed(), projs[i]->get_completion_time()), "fonts/Marker Felt.ttf", font_size);
		/*time_label->setDimensions(rect_size.width * 0.10, rect_size.height * 0.15);*/
		time_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		time_label->setPosition(Vec2(rect_size.width * 0.29, rect_size.height * 0.48));
		time_label->setTextColor(Color4B::WHITE);
		time_labels.pushBack(time_label);
		this->addChild(time_label, 1, -999);

		auto change_label = Label::createWithTTF(StringUtils::format("%d", projs[i]->get_change()), "fonts/Marker Felt.ttf", font_size);
		/*change_label->setDimensions(rect_size.width * 0.10, rect_size.height * 0.15);*/
		change_label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
		change_label->setPosition(Vec2(rect_size.width * 0.34, rect_size.height * 0.30));
		change_label->setTextColor(Color4B::WHITE);
		change_labels.pushBack(change_label);
		this->addChild(change_label, 1, -999);
	}
}
