#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <iostream>


class Project
{
public:
	Project();
	virtual ~Project() {}

	virtual void complete() = 0;

	std::string 	get_name() { return name; }
	std::string 	get_description() { return description; }

	int 	get_cash_cost() { return cash_cost; }
	int 	get_water_cost() { return water_cost; }

	float 	get_completion_time() { return completion_time; }
	float 	get_time_completed() { return time_completed; }

protected:
	std::string 	name;
	std::string 	description;

	int 	cash_cost;
	int 	water_cost;

	// time given in "weeks"
	float 	completion_time;
	float 	time_completed;
};


class TechnologicalProject : public Project
{
public:
	TechnologicalProject();
	virtual ~TechnologicalProject() {}

	virtual void complete();

protected:
	int 	change_in_consumption;
};


class EducationalProject : public Project
{
public:
	EducationalProject();
	virtual ~EducationalProject() {}

	virtual void complete();

protected:
	float 	change_in_awareness;
	float 	change_in_min_awareness;
};


class CulturalProject : public Project
{
public:
	CulturalProject();
	virtual ~CulturalProject() {}

	virtual void complete();

protected:
	float 	change_in_happiness;
};


#endif // __PROJECT_H__
