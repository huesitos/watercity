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

	persons_project_label = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
	persons_project_label->setDimensions(rect_size.width * 0.10, rect_size.height * 0.15);
	persons_project_label->setPosition(Vec2(rect_size.width * 0.20, rect_size.height * 0.35));
	persons_project_label->setTextColor(Color4B::WHITE);
	this->addChild(persons_project_label, 1);

	// Fund/defund project
	// Assign persons and check if can be funded
	fund_project = ui::Button::create("images/more.png");
	fund_project->setPosition(Vec2(rect_size.width * 0.80, rect_size.height * 0.45));

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
                if (proj && !proj->is_set_to_start() && proj->can_be_funded())
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

	persons_project_label->setString(StringUtils::format("%d", persons_on_projects));

	projs = ministry->get_projects_to_display();
	num_projs = static_cast<int>(projs.size());

	for (int i = 0; i < num_projs; ++i)
	{
		persons_labels.at(i)->setString(StringUtils::format("%d / %d", projs[i]->get_persons_assigned(), projs[i]->get_persons_needed()));
		time_labels.at(i)->setString(StringUtils::format("%d / %d", projs[i]->get_time_completed(), projs[i]->get_completion_time()));
	}
}

void ProjectMenuItem::update_projects()
{
	int num_removals = static_cast<int>(project_images.size());

	project_images.clear();
	name_labels.clear();
	description_labels.clear();
	cash_labels.clear();
	water_labels.clear();
	persons_labels.clear();
	time_labels.clear();

	for (int i = 0; i < num_removals; ++i)
		this->removeChildByTag(-999);

	Size rect_size = this->getBoundingBox().size;

	auto projs = ministry->get_projects_to_display();
	const int num_projs = static_cast<int>(projs.size());

	for (int i = 0; i < num_projs; ++i)
	{
		auto project_image = Sprite::create("images/proyectos.png");
		project_images.pushBack(project_image);
		this->addChild(project_image, 1, -999);
		project_image->setPosition(Vec2(rect_size.width * 0.65, rect_size.height * (0.70 - 0.25 * i)));

		auto size = project_image->getContentSize();

		int font_size = 20;

		auto name_label = Label::createWithTTF(projs[i]->get_name(), "fonts/Marker Felt.ttf", font_size);
		name_label->setDimensions(size.width * 0.90, size.height * 0.30);
		name_label->setPosition(Vec2(size.width * 0.50, size.height - name_label->getContentSize().height * 0.75));
		name_label->setTextColor(Color4B::BLACK);
		name_labels.pushBack(name_label);
		project_image->addChild(name_label, 1);

		auto description_label = Label::createWithTTF(projs[i]->get_description(), "fonts/Marker Felt.ttf", font_size);
		description_label->setDimensions(size.width * 0.90, size.height * 0.30);
		description_label->setPosition(Vec2(size.width * 0.50, size.height * 0.70 - description_label->getContentSize().height * 0.75));
		description_label->setTextColor(Color4B::BLACK);
		description_labels.pushBack(description_label);
		project_image->addChild(description_label, 1);

		auto cash_label = Label::createWithTTF(StringUtils::format("$ %d", projs[i]->get_cash_cost()), "fonts/Marker Felt.ttf", font_size);
		cash_label->setDimensions(size.width * 0.20, size.height * 0.20);
		cash_label->setPosition(Vec2(size.width * 0.15, size.height * 0.30 - cash_label->getContentSize().height / 2));
		cash_label->setTextColor(Color4B::BLACK);
		cash_labels.pushBack(cash_label);
		project_image->addChild(cash_label, 1);

		auto water_label = Label::createWithTTF(StringUtils::format("Water: %d", projs[i]->get_water_cost()), "fonts/Marker Felt.ttf", font_size);
		water_label->setDimensions(size.width * 0.30, size.height * 0.20);
		water_label->setPosition(Vec2(size.width * 0.35, size.height * 0.30 - water_label->getContentSize().height / 2));
		water_label->setTextColor(Color4B::BLACK);
		water_labels.pushBack(water_label);
		project_image->addChild(water_label, 1);

		auto persons_label = Label::createWithTTF(StringUtils::format("%d / %d", projs[i]->get_persons_assigned(), projs[i]->get_persons_needed()), "fonts/Marker Felt.ttf", font_size);
		persons_label->setDimensions(size.width * 0.30, size.height * 0.20);
		persons_label->setPosition(Vec2(size.width * 0.65, size.height * 0.30 - persons_label->getContentSize().height / 2));
		persons_label->setTextColor(Color4B::BLACK);
		persons_labels.pushBack(persons_label);
		project_image->addChild(persons_label, 1);

		auto time_label = Label::createWithTTF(StringUtils::format("%d / %d", projs[i]->get_time_completed(), projs[i]->get_completion_time()), "fonts/Marker Felt.ttf", font_size);
		time_label->setDimensions(size.width * 0.30, size.height * 0.20);
		time_label->setPosition(Vec2(size.width * 0.90, size.height * 0.30 - time_label->getContentSize().height / 2));
		time_label->setTextColor(Color4B::BLACK);
		time_labels.pushBack(time_label);
		project_image->addChild(time_label, 1);
	}
}
