#include "Project.h"
#include "ResourceManager.h"

Project::Project(std::string name, std::string description, int cash_cost, int water_cost, int completion_time)
	: running(false), name(name), description(description), cash_cost(cash_cost),
	water_cost(water_cost), completion_time(completion_time), time_completed(0)
{}

void Project::start_project()
{
	running = true;
}

void Project::complete()
{
	running = false;
}

void Project::develop()
{
	time_completed++;
}

bool Project::is_running()
{
	return running;
}

bool Project::is_completed()
{
	return time_completed >= completion_time;
}


TechnologicalProject::TechnologicalProject()
{}

TechnologicalProject::TechnologicalProject(std::string name, std::string description, int cash_cost, int water_cost,
							int completion_time, int change_in_consumption)
	: Project(name, description, cash_cost, water_cost, completion_time), change_in_consumption(change_in_consumption)
{}

void TechnologicalProject::complete()
{
	Project::complete();
	ResourceManager::getInstance().decrease_desired_consumption(change_in_consumption);
}



EducationalProject::EducationalProject()
{}

EducationalProject::EducationalProject(std::string name, std::string description, int cash_cost, int water_cost,
							int completion_time, int change_in_awareness)
	: Project(name, description, cash_cost, water_cost, completion_time), change_in_awareness(change_in_awareness)
{}

void EducationalProject::complete()
{
	Project::complete();
	ResourceManager::getInstance().increase_awareness(change_in_awareness);
	// ResourceManager::getInstance().increase_awareness_min(change_in_min_awareness);
}



CulturalProject::CulturalProject()
{}

CulturalProject::CulturalProject(std::string name, std::string description, int cash_cost, int water_cost,
							int completion_time, int change_in_happiness)
	: Project(name, description, cash_cost, water_cost, completion_time), change_in_happiness(change_in_happiness)
{}

void CulturalProject::complete()
{
	Project::complete();
	ResourceManager::getInstance().increase_happiness(change_in_happiness);
}
