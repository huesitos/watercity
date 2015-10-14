#ifndef __MINISTRY_H__
#define __MINISTRY_H__

#include "cocos2d.h"
#include "ProjectMenuItem.h"
#include <vector>


class Ministry : public cocos2d::Sprite
{
public:
	virtual ~Ministry();

	// static Ministry* create(const char* pszFileName);

	void setup_menu_items();
	void setup_listener();

	void start_project();
	void complete_project();

	void develop_project();

	bool is_project_running();
	bool is_project_completed();

	Project* get_current_project();

protected:
	Ministry();
	bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

	bool has_project();
	bool can_be_funded();

	cocos2d::Vector<ProjectMenuItem*> project_menu_items;

	std::vector<Project*> projects;

	int current_project;
};

class MinistryOfTechnology : public Ministry
{
public:
	MinistryOfTechnology();
	virtual ~MinistryOfTechnology() {}

	static Ministry* create(const char* pszFileName);

};

class MinistryOfEducation : public Ministry
{
public:
	MinistryOfEducation();
	virtual ~MinistryOfEducation() {}

	static Ministry* create(const char* pszFileName);

};

class MinistryOfCulture : public Ministry
{
public:
	MinistryOfCulture();
	virtual ~MinistryOfCulture() {}

	static Ministry* create(const char* pszFileName);

};

#endif // __MINISTRY_H__
