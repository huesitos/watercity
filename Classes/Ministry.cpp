#include "Ministry.h"
#include "ResourceManager.h"
#include "GameLayer.h"

USING_NS_CC;


Ministry::Ministry()
	: current_project(0)
{
	TechnologicalProject p1("Pipes 1", "Build better pipes", 200, 400, 7, 200);
	TechnologicalProject p2("Pipes 2", "Build even better pipes", 300, 500, 9, 300);

	projects.push_back(p1);
	projects.push_back(p2);
}

Ministry::~Ministry()
{}

Ministry* Ministry::create(const char* pszFileName)
{
	Ministry* ministry = new Ministry;
	if (ministry && ministry->initWithFile(pszFileName))
	{
		ministry->autorelease();
		ministry->setup_listener();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void Ministry::setup_listener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Ministry::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Ministry::on_touch_began(Touch* touch, Event* event)
{
	if (has_project() && can_be_funded())
		start_project();

	return true;
}

bool Ministry::has_project()
{
	return current_project < static_cast<int>(projects.size());
}

bool Ministry::can_be_funded()
{
	ResourceManager &rm = ResourceManager::getInstance();

	return rm.has_enough_water(projects[current_project].get_water_cost()) && 
		rm.has_enough_cash(projects[current_project].get_cash_cost());
}

Project Ministry::get_current_project()
{
	if (has_project())
		return projects[current_project];
	else
		return Project("None", "", 0, 0 ,0);
}

void Ministry::start_project()
{
	if (!is_project_running() && has_project())
	{
		projects[current_project].start_project();

		ResourceManager::getInstance().spend_water(projects[current_project].get_water_cost());
		ResourceManager::getInstance().spend_cash(projects[current_project].get_cash_cost());
	}

	((GameLayer*) this->getParent())->update_labels();
}

void Ministry::complete_project()
{
	projects[current_project].complete();

	current_project++;
}

void Ministry::develop_project()
{
	if (has_project() && is_project_running())
	{
		projects[current_project].develop();

		if (is_project_completed())
		{
			complete_project();
		}
	}
}

bool Ministry::is_project_running()
{
	if (has_project())
		return projects[current_project].is_running();
	else
		return false;
}

bool Ministry::is_project_completed()
{
	if (has_project())
		return projects[current_project].is_completed();
	else
		return false;
}
