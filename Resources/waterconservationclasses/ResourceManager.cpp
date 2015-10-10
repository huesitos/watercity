#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	water_reserves = 10000;
	water_inflow = 2000;
	water_consumption = 3000;

	cash_total = 2000;
	fee_per_family = 50;
	number_of_families = 10;

	happiness = 50.0f;
	awareness = 30.0f;
	awareness_min = 10.0f;
}

void ResourceManager::update(float dt)
{
	decrease_awareness(awareness_decay_rate * dt);
}

void ResourceManager::update_day(float dt)
{
	water_reserves += (water_inflow - water_consumption);
	if (water_reserves < 0)
		water_reserves = 0;

	cash_total += (fee_per_family * number_of_families);
}

bool ResourceManager::has_enough(int water_cost, int cash_cost)
{
	return water_reserves > water_cost && cash_total >= cash_cost;
}

void ResourceManager::spend_water(int water_cost)
{
	water_reserves -= water_cost;
}

void ResourceManager::spend_cash(int cash_cost)
{
	cash_total -= cash_cost;
}

void ResourceManager::increase_inflow(int amount)
{
	water_inflow += amount;
}

void ResourceManager::decrease_inflow(int amount)
{
	water_inflow -= amount;
	if (water_inflow < 0)
		water_inflow = 0;
}

void ResourceManager::increase_consumption(int amount)
{
	water_consumption += amount;
}

void ResourceManager::decrease_consumption(int amount)
{
	water_consumption -= amount;
	if (water_consumption < 0)
		water_consumption = 0;
}

void ResourceManager::increase_happiness(float amount)
{
	happiness += amount;
	if (happiness > 100.0f)
		happiness = 100.0f;
}

void ResourceManager::decrease_happiness(float amount)
{
	happiness -= amount;
	if (happiness < 0.0f)
		happiness = 0.0f;
}

void ResourceManager::increase_awareness(float amount)
{
	awareness += amount;
	if (awareness > 100.0f)
		awareness = 100.0f;
}

void ResourceManager::decrease_awareness(float amount)
{
	awareness -= amount;
	if (awareness < awareness_min)
		awareness = awareness_min;
}

void ResourceManager::increase_awareness_min(float amount)
{
	awareness_min += amount;
	if (awareness_min > 100.0f)
		awareness_min = 100.0f;
}
