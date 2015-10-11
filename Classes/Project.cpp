#include "Project.h"
#include "ResourceManager.h"

Project::Project()
{}


TechnologicalProject::TechnologicalProject()
{}

void TechnologicalProject::complete()
{
	ResourceManager::getInstance().decrease_consumption(change_in_consumption);
}


EducationalProject::EducationalProject()
{}

void EducationalProject::complete()
{
	ResourceManager::getInstance().increase_awareness(change_in_awareness);
	ResourceManager::getInstance().increase_awareness_min(change_in_min_awareness);
}


CulturalProject::CulturalProject()
{}

void CulturalProject::complete()
{
	ResourceManager::getInstance().increase_happiness(change_in_happiness);
}

