#include "Project.h"

Project::Project()
	: running(false), paused(false)
{}

Project::~Project()
{}

bool Project::is_affordable()
{
	return ResourceManager::getInstance().has_enough(water_cost, cash_cost);
}

void Project::begin()
{
	if (!running)
	{
		progressed_time = 0.0f;
		paused = false;
		running = true;
	}
}

void Project::pause()
{
	if (running)
	{
		paused = true;
	}
}

void Project::resume()
{
	if (running)
	{
		paused = false;
	}
}

void Project::update(float dt)
{
	if (running && !paused)
	{
		progressed_time += dt;
	}
}

bool Project::is_finished()
{
	return progressed_time >= completion_time;
}
