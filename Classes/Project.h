#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <iostream>


class Project
{
public:
	Project() {}
	Project(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed, int completion_time);
	virtual ~Project() {}

	virtual void complete();

	virtual void start_project();
	virtual void develop();
	virtual bool is_running();
	virtual void set_to_start(bool starting);
	virtual bool is_set_to_start();
	virtual bool is_completed();

	virtual void assign_persons_needed();
	virtual void empty_persons_assigned();
	virtual void increase_persons_assigned();
	virtual void decrease_persons_assigned();

	std::string 	get_name() { return name; }
	std::string 	get_description() { return description; }

	int 	get_cash_cost() { return cash_cost; }
	int 	get_water_cost() { return water_cost; }

	int 	get_persons_assigned() { return persons_assigned; }
	int 	get_persons_needed() { return persons_needed; }

	int 	get_completion_time() { return completion_time; }
	int 	get_time_completed() { return time_completed; }
	int 	get_time_remaining() { return completion_time - time_completed; }

protected:
	std::string 	name;
	std::string 	description;

	int 	cash_cost;
	int 	water_cost;

	int 	persons_assigned;
	int 	persons_needed;

	// time given in "days"
	int 	completion_time;
	int 	time_completed;

	bool 	running;
	bool 	to_start;
};


class TechnologicalProject : public Project
{
public:
	TechnologicalProject();
	TechnologicalProject(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed,
							int completion_time, int change_in_consumption);
	virtual ~TechnologicalProject() {}

	virtual void complete();

	int get_change_in_consumption();

protected:
	int 	change_in_consumption;
};


class EducationalProject : public Project
{
public:
	EducationalProject();
	EducationalProject(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed,
							int completion_time, int change_in_awareness);
	virtual ~EducationalProject() {}

	virtual void complete();
	int get_change_in_awareness();

protected:

	float 	change_in_awareness;
	float 	change_in_min_awareness;
};


class CulturalProject : public Project
{
public:
	CulturalProject();
	CulturalProject(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed,
							int completion_time, int change_in_happiness);
	virtual ~CulturalProject() {}

	virtual void complete();
	int get_change_in_happiness();

protected:
	float 	change_in_happiness;
};


#endif // __PROJECT_H__
