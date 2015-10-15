#include "Ministry.h"
#include "ResourceManager.h"
#include "GameLayer.h"

USING_NS_CC;


Ministry::Ministry()
	: current_project(0)
{}

Ministry::~Ministry()
{}

// Ministry* Ministry::create(const char* pszFileName)
// {
// 	Ministry* ministry = new Ministry;
// 	if (ministry && ministry->initWithFile(pszFileName))
// 	{
// 		ministry->autorelease();
//		ministry->setup_menu_items();
// 		ministry->setup_listener();
// 		return ministry;
// 	}
// 	CC_SAFE_DELETE(ministry);
// 	return ministry = nullptr;
// }

void Ministry::setup_menu_items()
{
	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		auto pmi = ProjectMenuItem::create("blue_rectangle.png", projects[i]);
		pmi->setVisible(false);
		this->addChild(pmi, 1);
		project_menu_items.pushBack(pmi);
	}
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
	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		int i = 0;

		for (auto pmi : project_menu_items)
		{
			if (i < 3)
			{
				pmi->setPosition(Vec2(0, 
					(Director::getInstance()->getVisibleSize().height * 3 / 4) - i * (pmi->getBoundingBox().size.height)));
				pmi->setVisible(true);
			}
			++i;
		}

		return true;
	}
	else
	{
		for (auto pmi : project_menu_items)
		{
			pmi->setVisible(false);
		}

		return true;
	}

/*	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		if (has_project() && can_be_funded())
			start_project();

		return true;
	}

	return false;*/
}

bool Ministry::has_project()
{
	return current_project < static_cast<int>(projects.size());
}

bool Ministry::can_be_funded()
{
	ResourceManager &rm = ResourceManager::getInstance();

	return rm.has_enough_water(projects[current_project]->get_water_cost()) &&
		rm.has_enough_cash(projects[current_project]->get_cash_cost());
}

Project* Ministry::get_current_project()
{
	if (has_project())
		return projects[current_project];
	else
		return new Project("None", "", 0, 0, 0, 0);
}

void Ministry::start_project()
{
	if (!is_project_running() && has_project())
	{
		projects[current_project]->start_project();

		ResourceManager::getInstance().spend_water(projects[current_project]->get_water_cost());
		ResourceManager::getInstance().spend_cash(projects[current_project]->get_cash_cost());
	}

	((GameLayer*) this->getParent())->update_labels();
}

void Ministry::complete_project()
{
	projects[current_project]->complete();

	current_project++;
}

void Ministry::develop_project()
{
	if (has_project() && is_project_running())
	{
		projects[current_project]->develop();

		if (is_project_completed())
		{
			complete_project();
		}
	}
}

bool Ministry::is_project_running()
{
	if (has_project())
		return projects[current_project]->is_running();
	else
		return false;
}

bool Ministry::is_project_completed()
{
	if (has_project())
		return projects[current_project]->is_completed();
	else
		return false;
}



MinistryOfTechnology::MinistryOfTechnology()
{
	projects.push_back(new TechnologicalProject("Pipes 1", "Build better pipes", 200, 400, 25, 7, 200));
	projects.push_back(new TechnologicalProject("Pipes 2", "Build even better pipes", 300, 500, 35, 9, 300));
}

Ministry* MinistryOfTechnology::create(const char* pszFileName)
{
	Ministry* ministry = new MinistryOfTechnology;
	if (ministry && ministry->initWithFile(pszFileName))
	{
		ministry->autorelease();
		ministry->setup_menu_items();
		ministry->setup_listener();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}



MinistryOfEducation::MinistryOfEducation()
{
	projects.push_back(new EducationalProject("Tip 1", "Spend less time in the bathtub", 200, 400, 15, 7, 2));
	projects.push_back(new EducationalProject("Tip 2", "Use a glass for brushing your teeth", 300, 500, 20, 9, 2));
}

Ministry* MinistryOfEducation::create(const char* pszFileName)
{
	Ministry* ministry = new MinistryOfEducation;
	if (ministry && ministry->initWithFile(pszFileName))
	{
		ministry->autorelease();
		ministry->setup_menu_items();
		ministry->setup_listener();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}



MinistryOfCulture::MinistryOfCulture()
{
	projects.push_back(new CulturalProject("Gardening fair", "What the name says", 200, 400, 15, 7, 10));
	projects.push_back(new CulturalProject("Aquatic park", "Yep", 300, 500, 20, 9, 10));
}

Ministry* MinistryOfCulture::create(const char* pszFileName)
{
	Ministry* ministry = new MinistryOfCulture;
	if (ministry && ministry->initWithFile(pszFileName))
	{
		ministry->autorelease();
		ministry->setup_menu_items();
		ministry->setup_listener();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}
