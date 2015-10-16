#ifndef __MINISTRY_H__
#define __MINISTRY_H__

#include "cocos2d.h"
#include <vector>
#include "Project.h"


class Ministry : public cocos2d::Sprite
{
public:
	virtual ~Ministry();

	bool init(const char* pszFileName, const char* projectsFileName);

	virtual void setup_projects(const char* projectsFileName) = 0;
	virtual void setup_listener() = 0;

	bool can_be_funded();
	void start_project();

	void develop_project();

	bool has_project_running();
	bool has_project_set_to_start();

	std::vector<Project*> get_projects_to_display();
	std::vector<Project*> get_projects_running();
	std::vector<Project*> get_projects_set_to_start();

protected:
	Ministry();
	bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

	bool has_project();
	bool can_be_funded();

	std::vector<Project*> projects;
};

class MinistryOfTechnology : public Ministry
{
public:
	MinistryOfTechnology();
	virtual ~MinistryOfTechnology() {}

	static Ministry* create(const char* pszFileName, const char* projectsFileName);

	virtual void setup_projects(const char* projectsFileName);

	virtual void setup_listener();

	int get_persons_on_breakdowns() { return persons_on_breakdowns; }

	void increase_persons_on_breakdowns();
	void decrease_persons_on_breakdowns();

protected:
	bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

	int persons_on_breakdowns;

};

class MinistryOfEducation : public Ministry
{
public:
	MinistryOfEducation();
	virtual ~MinistryOfEducation() {}

	static Ministry* create(const char* pszFileName, const char* projectsFileName);

	virtual void setup_projects(const char* projectsFileName);

	virtual void setup_listener();

protected:
	bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

};

class MinistryOfCulture : public Ministry
{
public:
	MinistryOfCulture();
	virtual ~MinistryOfCulture() {}

	static Ministry* create(const char* pszFileName, const char* projectsFileName);
	virtual void complete_project();

	virtual void setup_projects(const char* projectsFileName);

	virtual void setup_listener();

protected:
	bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

};

#endif // __MINISTRY_H__
