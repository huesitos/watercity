#include "ProjectMenuItem.h"
#include "ResourceManager.h"
#include "GameLayer.h"
#include <iostream>
#include <string>
#include <fstream>

USING_NS_CC;


Ministry::Ministry()
{}

Ministry::~Ministry()
{}

bool Ministry::init(const char* pszFileName, const char* projectsFileName)
{
	if (initWithFile(pszFileName))
	{
		setup_projects(projectsFileName);
		return true;
	}

	return false;
}

bool Ministry::has_project()
{
	return static_cast<int>(get_projects_to_display().size()) > 0;
}

bool Ministry::can_be_funded()
{
	ResourceManager &rm = ResourceManager::getInstance();

	auto p = get_projects_set_to_start();

	int total_water_cost = 0;
	int total_cash_cost = 0;

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		total_water_cost += p[i]->get_water_cost();
		total_cash_cost += p[i]->get_cash_cost();
	}

	return rm.has_enough_water(total_water_cost) && rm.has_enough_cash(total_cash_cost);
}

std::vector<Project*> Ministry::get_projects_to_display()
{
	std::vector<Project*> p;

	const int MAX_PROJECTS = 1;
	int size = 0;

	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		if (!projects[i]->is_completed())
		{
			p.push_back(projects[i]);
			size++;

			if (size == MAX_PROJECTS)
				break;
		}
	}

	return p;
}

std::vector<Project*> Ministry::get_projects_running()
{
	std::vector<Project*> p;

	const int MAX_PROJECTS = 1;
	int size = 0;

	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		if (projects[i]->is_running())
		{
			p.push_back(projects[i]);
			size++;

			if (size == MAX_PROJECTS)
				break;
		}
	}

	return p;
}

std::vector<Project*> Ministry::get_projects_set_to_start()
{
	std::vector<Project*> p;

	const int MAX_PROJECTS = 1;
	int size = 0;

	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		if (projects[i]->is_set_to_start())
		{
			p.push_back(projects[i]);
			size++;

			if (size == MAX_PROJECTS)
				break;
		}
	}

	return p;
}

void Ministry::start_project()
{
	ResourceManager &rm = ResourceManager::getInstance();

	auto p = get_projects_set_to_start();

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		p[i]->start_project();

		rm.spend_water(p[i]->get_water_cost());
		rm.spend_cash(p[i]->get_cash_cost());
	}

	((GameLayer*) this->getParent())->update_labels();

	animate_icon();
}

void Ministry::develop_project()
{
	auto p = get_projects_running();

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		p[i]->develop();

		if (p[i]->is_completed())
		{
			p[i]->complete();
			stop_animate_icon();
		}
	}
}

bool Ministry::has_project_running()
{
	return static_cast<int>(get_projects_running().size()) > 0;
}

bool Ministry::has_project_set_to_start()
{
	return static_cast<int>(get_projects_set_to_start().size()) > 0;
}



MinistryOfTechnology::MinistryOfTechnology()
	: persons_on_breakdowns(0)
{
	projects.push_back(new TechnologicalProject("Pipes 1", "Build better pipes", 750, 5000, 1, 7, 50));
	projects.push_back(new TechnologicalProject("Pipes 2", "Build even better pipes", 1000, 6000, 1, 7, 50));
	projects.push_back(new TechnologicalProject("Pipes 3", "Build even better pipes", 1250, 7000, 1, 7, 50));
	projects.push_back(new TechnologicalProject("Pipes 4", "Build even better pipes", 1500, 8000, 1, 7, 75));
	projects.push_back(new TechnologicalProject("Pipes 5", "Build even better pipes", 1750, 9000, 1, 7, 75));
	projects.push_back(new TechnologicalProject("Pipes 6", "Build even better pipes", 2000, 10000, 1, 7, 75));
	projects.push_back(new TechnologicalProject("Pipes 7", "Build even better pipes", 2225, 11000, 1, 7, 75));
	projects.push_back(new TechnologicalProject("Pipes 8", "Build even better pipes", 2500, 12000, 1, 7, 100));
	projects.push_back(new TechnologicalProject("Pipes 9", "Build even better pipes", 2750, 13000, 1, 7, 100));
	projects.push_back(new TechnologicalProject("Pipes 10", "Build even better pipes", 3000, 14000, 1, 7, 100));
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

void MinistryOfTechnology::setup_listener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MinistryOfTechnology::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MinistryOfTechnology::on_touch_began(Touch* touch, Event* event)
{
	auto layer = (GameLayer*) (this->getParent());

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		layer->get_menu_technology()->update_projects();
		layer->get_menu_technology()->setVisible(true);
		return true;
	}
	else
	{
		layer->get_menu_technology()->setVisible(false);
		return false;
	}
}

void MinistryOfTechnology::increase_persons_on_breakdowns()
{
	persons_on_breakdowns++;
	ResourceManager::getInstance().occupy_persons(1);
}

void MinistryOfTechnology::decrease_persons_on_breakdowns()
{
	if (persons_on_breakdowns > 0)
	{
		persons_on_breakdowns--;
		ResourceManager::getInstance().unoccupy_persons(1);
	}
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

void MinistryOfTechnology::animate_icon()
{
	Vector<SpriteFrame*> frames;
	Size mSize = this->getContentSize();

	frames.pushBack(SpriteFrame::create("images/technology_anim/technology.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology3.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology4.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology5.png", Rect(0, 0, mSize.width, mSize.height)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void MinistryOfTechnology::stop_animate_icon()
{
	this->stopAllActions();
}




MinistryOfEducation::MinistryOfEducation()
{
	projects.push_back(new EducationalProject("Tip 1", "Spend less time in the bathtub", 1500, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 2", "Use a glass for brushing your teeth", 1500, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 3", "Use a glass for brushing your teeth", 1500, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 4", "Use a glass for brushing your teeth", 1750, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 5", "Use a glass for brushing your teeth", 1750, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 6", "Use a glass for brushing your teeth", 1750, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 7", "Use a glass for brushing your teeth", 2000, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 8", "Use a glass for brushing your teeth", 2000, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 9", "Use a glass for brushing your teeth", 2000, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Tip 10", "Use a glass for brushing your teeth", 2250, 3000, 1, 7, 10));
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

void MinistryOfEducation::setup_listener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MinistryOfEducation::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MinistryOfEducation::on_touch_began(Touch* touch, Event* event)
{
	auto layer = (GameLayer*) (this->getParent());

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		layer->get_menu_education()->update_projects();
		layer->get_menu_education()->setVisible(true);
		return true;
	}
	else
	{
		layer->get_menu_education()->setVisible(false);
		return false;
	}
}

void MinistryOfEducation::setup_projects(const char* projectsFileName)
{

}

void MinistryOfEducation::animate_icon()
{
	Vector<SpriteFrame*> frames;
	Size mSize = this->getContentSize();

	frames.pushBack(SpriteFrame::create("images/education_anim/education.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education3.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education4.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education5.png", Rect(0, 0, mSize.width, mSize.height)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void MinistryOfEducation::stop_animate_icon()
{
	this->stopAllActions();
}



MinistryOfCulture::MinistryOfCulture()
{
	projects.push_back(new CulturalProject("Gardening fair", "What the name says", 0, 3500, 1, 7, 2));
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

void MinistryOfCulture::setup_listener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MinistryOfCulture::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MinistryOfCulture::on_touch_began(Touch* touch, Event* event)
{
	auto layer = (GameLayer*) (this->getParent());

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		layer->get_menu_culture()->update_projects();
		layer->get_menu_culture()->setVisible(true);
		return true;
	}
	else
	{
		layer->get_menu_culture()->setVisible(false);
		return false;
	}
}

void MinistryOfCulture::stop_project()
{
	auto p = get_projects_running();

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		p[i]->stop_project();
		p[i]->empty_persons_assigned();
		p[i]->set_to_start(false);
		stop_animate_icon();
	}
}

void MinistryOfCulture::setup_projects(const char* projectsFileName)
{

}

void MinistryOfCulture::animate_icon()
{
	Vector<SpriteFrame*> frames;
	Size mSize = this->getContentSize();

	frames.pushBack(SpriteFrame::create("images/park_anim/park.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park3.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park.png", Rect(0, 0, mSize.width, mSize.height)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void MinistryOfCulture::stop_animate_icon()
{
	this->stopAllActions();
}