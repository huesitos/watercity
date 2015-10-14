#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	water_reserves = 100000;
	water_inflow = 2000;
	actual_water_consumption = 3000;
	initial_actual_water_consumption = actual_water_consumption;
	desired_water_consumption = 1500;
	initial_desired_water_consumption = desired_water_consumption;
	selected_water_consumption = actual_water_consumption;

	cash_total = 2000;
	fee_per_family = 5;
	number_of_families = 10;

	population_total = 50;
	population_occupied = 0;

	happiness = 50.0f;
	awareness = 0.0f;
	awareness_min = 0.0f;
}

// void ResourceManager::update(float dt)
// {
// 	decrease_awareness(awareness_decay_rate * dt);
// }

void ResourceManager::update_day()
{
	water_reserves += (water_inflow - selected_water_consumption);
	if (water_reserves < 0)
		water_reserves = 0;

	int happiness_penalty = get_happiness_penalty();

	if (happiness_penalty < 0)
		decrease_happiness(-1*get_happiness_penalty());
	else
		increase_happiness(get_happiness_penalty());

	cash_total += (fee_per_family * number_of_families);
}

bool ResourceManager::has_enough_water(int water_cost)
{
	return water_reserves > water_cost;
}

bool ResourceManager::has_enough_cash(int cash_cost)
{
	return cash_total >= cash_cost;
}

bool ResourceManager::has_enough_happiness(float happiness_cost)
{
	return happiness >= happiness_cost;
}

bool ResourceManager::has_enough_unoccupied(int persons_needed)
{
	return get_population_unoccupied() >= persons_needed;
}

void ResourceManager::spend_water(int water_cost)
{
	water_reserves -= water_cost;
}

void ResourceManager::spend_cash(int cash_cost)
{
	cash_total -= cash_cost;
}

void ResourceManager::occupy_persons(int num_persons)
{
	population_occupied += num_persons;
}

void ResourceManager::unoccupy_persons(int num_persons)
{
	population_occupied -= num_persons;
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

void ResourceManager::increase_selected_consumption(int amount)
{
	selected_water_consumption += amount;
}

void ResourceManager::decrease_actual_consumption(int amount)
{
	actual_water_consumption -= amount;
	if (actual_water_consumption < 0)
		actual_water_consumption = 0;
}

void ResourceManager::decrease_desired_consumption(int amount)
{
	desired_water_consumption -= amount;
	if (desired_water_consumption < 0)
		desired_water_consumption = 0;
}

void ResourceManager::decrease_selected_consumption(int amount)
{
	selected_water_consumption -= amount;
	if (selected_water_consumption < 0)
		selected_water_consumption = 0;
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

void ResourceManager::increase_water_reserves(float amount)
{
	water_reserves += amount;
}

int ResourceManager::get_happiness_penalty()
{
	// Penalty rate based on the difference between the actual and desired consumption
	int consumption_difference = initial_actual_water_consumption - initial_desired_water_consumption;
	double penalty_rate = 20.0/consumption_difference;
	double water_difference = selected_water_consumption - actual_water_consumption;

	return penalty_rate * water_difference;
}
