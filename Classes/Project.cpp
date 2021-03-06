#include "Project.h"
#include "ResourceManager.h"


Project::Project(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed, int completion_time)
	: running(false), name(name), description(description), cash_cost(cash_cost),
	water_cost(water_cost), persons_needed(persons_needed), completion_time(completion_time),
	time_completed(0), persons_assigned(0), to_start(false), completed(false), reported(false)
{}

void Project::start_project()
{
	running = true;
	to_start = false;
}

void Project::complete()
{
	running = false;
	ResourceManager::getInstance().unoccupy_persons(persons_assigned);
}

void Project::develop()
{
	time_completed++;
	if (time_completed >= completion_time)
		completed = true;
}

void Project::set_to_start(bool starting)
{
	to_start = starting;
}

void Project::set_reported(bool reported)
{
	this->reported = reported;
}

void Project::assign_persons_needed()
{
	if (persons_assigned == 0 && ResourceManager::getInstance().has_enough_unoccupied(persons_needed))
	{
		persons_assigned = persons_needed;
		ResourceManager::getInstance().occupy_persons(persons_needed);
		set_to_start(true);
	}
}

void Project::empty_persons_assigned()
{
	if (persons_assigned > 0)
	{
		ResourceManager::getInstance().unoccupy_persons(persons_assigned);
		persons_assigned = 0;
	}
}

void Project::increase_persons_assigned()
{
	if (ResourceManager::getInstance().has_enough_unoccupied(1))
	{
		persons_assigned++;
		ResourceManager::getInstance().occupy_persons(1);
	}
}

void Project::decrease_persons_assigned()
{
	if (persons_assigned > persons_needed)
	{
		persons_assigned--;
		ResourceManager::getInstance().unoccupy_persons(1);
	}
}

bool Project::can_be_funded()
{
	ResourceManager &rm = ResourceManager::getInstance();

	return rm.has_enough_water(this->get_water_cost()) && rm.has_enough_cash(this->get_cash_cost()) && rm.has_enough_unoccupied(this->get_persons_needed());
}


TechnologicalProject::TechnologicalProject()
{}

TechnologicalProject::TechnologicalProject(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed,
							int completion_time, int change_in_consumption)
	: Project(name, description, cash_cost, water_cost, persons_needed, completion_time), change_in_consumption(change_in_consumption)
{}

void TechnologicalProject::complete()
{
	Project::complete();
	ResourceManager::getInstance().decrease_actual_consumption(change_in_consumption);
}

int TechnologicalProject::get_change_in_consumption()
{
	return change_in_consumption;
}

EducationalProject::EducationalProject()
{}

EducationalProject::EducationalProject(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed,
							int completion_time, int change_in_awareness)
	: Project(name, description, cash_cost, water_cost, persons_needed, completion_time), change_in_awareness(change_in_awareness)
{}

void EducationalProject::complete()
{
	Project::complete();
	ResourceManager::getInstance().increase_awareness(change_in_awareness);
	// ResourceManager::getInstance().increase_awareness_min(change_in_min_awareness);
}

int EducationalProject::get_change_in_awareness()
{
	return change_in_awareness;
}


CulturalProject::CulturalProject()
{}

CulturalProject::CulturalProject(std::string name, std::string description, int cash_cost, int water_cost, int persons_needed,
							int completion_time, int change_in_happiness)
	: Project(name, description, cash_cost, water_cost, persons_needed, completion_time), change_in_happiness(change_in_happiness)
{}

void CulturalProject::develop()
{
	ResourceManager::getInstance().increase_happiness(change_in_happiness);
}

int CulturalProject::get_change_in_happiness()
{
	return change_in_happiness;
}

void CulturalProject::stop_project()
{
	running = false;
	to_start = true;
}