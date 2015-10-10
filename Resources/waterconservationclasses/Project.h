#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <iostream>
#include "ResourceManager.h"


class Project
{
public:
	Project();
	virtual ~Project();

	virtual bool 	is_affordable();

	virtual void 	begin();

	virtual void 	pause();
	
	virtual void 	resume();

	virtual void 	update(float dt);

	virtual bool 	is_finished();

	virtual void 	on_finish() {}

protected:
	std::string 	project_name;
	std::string 	project_description;

	float 			completion_time;
	float 			progressed_time;

	int 			water_cost;
	int 			cash_cost;

	bool 			running;
	bool 			paused;

public:
	bool 			is_running() { return running; }
	bool 			is_paused() { return paused; }

	std::string		get_name() { return project_name; }
	std::string		get_description() { return project_description; }

	float 			get_completion_time() { return completion_time; }
	float 			get_progressed_time() { return progressed_time; }

	int 			get_water_cost() { return water_cost; }
	int 			get_cash_cost() { return cash_cost; }

	void 			set_name(std::string name) { project_name = name; }
	void 			set_description(std::string description) { project_description = description; }

	void 			set_completion_time(float time) { completion_time = time; }
	void 			set_progressed_time(float time) { progressed_time = time; }

	void 			set_water_cost(int cost) { water_cost = cost; }
	void 			set_cash_cost(int cost) { cash_cost = cost; }
};

#endif // __PROJECT_H__
