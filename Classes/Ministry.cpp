#include "Ministry.h"
#include "ResourceManager.h"
#include "GameLayer.h"
#include <iostream>
#include <string>
#include <fstream>

USING_NS_CC;


Ministry::Ministry()
	: current_project(0)
{}

Ministry::~Ministry()
{}

bool Ministry::init(const char* pszFileName, const char* projectsFileName)
{
	if (initWithFile(pszFileName))
	{
		setup_projects(projectsFileName);
		setup_menu_items();
		setup_listener();
		return true;
	}

	return false;
}

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
			if (i < 2)
			{
				pmi->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 1 / 2, 
					(Director::getInstance()->getVisibleSize().height * 3 / 4) - i * (pmi->getBoundingBox().size.height))
					- this->getPosition());
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

		return false;
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

Ministry* MinistryOfTechnology::create(const char* pszFileName, const char* projectsFileName)
{
	Ministry* ministry = new MinistryOfTechnology;
	if (ministry && ministry->init(pszFileName, projectsFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void MinistryOfTechnology::setup_projects(const char* projectsFileName)
{
/*	std::ifstream data_file(FileUtils::getInstance()->fullPathForFilename(projectsFileName).c_str());
	if (data_file)
	{
		std::string name;
		std::string desc;
		int cash_cost;
		int water_cost;
		int persons_needed;
		int completion_time;
		int change_in_consumption;
		int num_projects;

		data_file >> num_projects;
		data_file.ignore(10, '\n');

		for (int i = 0; i < num_projects; ++i)
		{
			std::getline(data_file, name);
			std::getline(data_file, desc);
			data_file >> cash_cost;
			data_file >> water_cost;
			data_file >> persons_needed;
			data_file >> completion_time;
			data_file >> change_in_consumption;
			data_file.ignore(10, '\n');

			projects.push_back(new TechnologicalProject(name, desc, cash_cost, water_cost, persons_needed, 
				completion_time, change_in_consumption));
		}
	}

	data_file.close();*/
}



MinistryOfEducation::MinistryOfEducation()
{
	projects.push_back(new EducationalProject("Tip 1", "Spend less time in the bathtub", 200, 400, 15, 7, 2));
	projects.push_back(new EducationalProject("Tip 2", "Use a glass for brushing your teeth", 300, 500, 20, 9, 2));
}

Ministry* MinistryOfEducation::create(const char* pszFileName, const char* projectsFileName)
{
	Ministry* ministry = new MinistryOfEducation;
	if (ministry && ministry->init(pszFileName, projectsFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void MinistryOfEducation::setup_projects(const char* projectsFileName)
{
	
}



MinistryOfCulture::MinistryOfCulture()
{
	projects.push_back(new CulturalProject("Gardening fair", "What the name says", 200, 400, 15, 7, 10));
	projects.push_back(new CulturalProject("Aquatic park", "Yep", 300, 500, 20, 9, 10));
}

Ministry* MinistryOfCulture::create(const char* pszFileName, const char* projectsFileName)
{
	Ministry* ministry = new MinistryOfCulture;
	if (ministry && ministry->init(pszFileName, projectsFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void MinistryOfCulture::setup_projects(const char* projectsFileName)
{
	
}

