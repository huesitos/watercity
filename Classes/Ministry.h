#ifndef __MINISTRY_H__
#define __MINISTRY_H__

#include "cocos2d.h"
#include "Project.h"
#include <vector>


class Ministry : public cocos2d::Sprite
{
public:
	Ministry();
	virtual ~Ministry();

	static Ministry* create(const char* pszFileName);

	void setup_listener();

	void start_project();
	void complete_project();

	void develop_project();

	bool is_project_running();
	bool is_project_completed();

	Project get_current_project();

private:
	bool on_touch_began(cocos2d::Touch* touch, cocos2d::Event* event);

	bool has_project();
	bool can_be_funded();

	std::vector<TechnologicalProject> projects;

	int current_project;
};

#endif // __MINISTRY_H__
