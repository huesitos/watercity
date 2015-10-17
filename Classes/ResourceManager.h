#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <iostream>

#define TECH 100
#define EDU 200
#define CULT 300

class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		static ResourceManager *resource_manager = new ResourceManager;
		return *resource_manager;
	}

	// Resets resources to their initial values
	// Called after a game over
	void reset();

	// Update function to be called every frame
	// void update(float dt);

	// Update function to be called on at the beginning of each
	// day by... (?)
	void update_day();

	// Checks whether the user has enough water
	bool has_enough_water(int water_cost);

	// Checks whether the user has enough cash
	bool has_enough_cash(int cash_cost);

	// Checks whether the user has enough happiness
	bool has_enough_happiness(float happiness_cost);

	// Checks whether the user has enough unoccupied persons
	bool has_enough_unoccupied(int persons_needed);

	// Spend some water from the reserve
	void spend_water(int water_cost);

	// Spend some cash from the reserve
	void spend_cash(int cash_cost);

	// Increases the number of occupied persons
	void occupy_persons(int num_persons);

	// Decreases the number of occupied persons
	void unoccupy_persons(int num_persons);

	// Adds 'amount' to the total inflow
	void increase_inflow(int amount);
	// Substracts 'amount' to the total inflow
	void decrease_inflow(int amount);

	// Adds 'amount' to the total consumption
	// void increase_consumption(int amount);
	void increase_selected_consumption(int amount);
	// Substracts 'amount' to the total consumption
	void decrease_actual_consumption(int amount);
	void decrease_desired_consumption(int amount);
	void decrease_selected_consumption(int amount);

	// Adds 'amount' to the total happiness
	void increase_happiness(float amount);
	// Substracts 'amount' to the total happiness
	void decrease_happiness(float amount);

	// Adds 'amount' to the total awareness
	void increase_awareness(float amount);
	// Substracts 'amount' to the total awareness
	// void decrease_awareness(float amount);

	// Adds 'amount' to the minimum awareness
	void increase_awareness_min(float amount);

	// Adds 'amount' to the water reserves
	void increase_water_reserves(float amount);

	// Effect awareness has on actual water consumed
	float awareness_actual_consumption_conversion(float awareness_amount);

private:
	ResourceManager();

	// Resource Variables

	int 	water_reserves;
	int 	water_reserves_limit;
	int 	water_inflow;
	int 	initial_actual_water_consumption;
	int 	actual_water_consumption;
	int 	initial_desired_water_consumption;
	int 	desired_water_consumption;
	int 	selected_water_consumption;

	int 	cash_total;
	int 	fee_per_family;
	int 	number_of_families;

	int 	population_total;
	int 	population_occupied;

	float 	happiness;
	float 	awareness;
	float 	awareness_min;

	// Decay rate in percentage points per second

	const float awareness_decay_rate = 5.0 / 60;

public:
	bool 	is_water_depleted() { return water_reserves <= 0; }

	int 	get_water_reserves() { return water_reserves; }
	int 	get_water_reserves_limit() { return water_reserves_limit; }
	int 	get_water_inflow() { return water_inflow; }
	int 	get_actual_water_consumption() { return actual_water_consumption; }
	int 	get_desired_water_consumption() { return desired_water_consumption; }
	int 	get_selected_water_consumption() { return selected_water_consumption; }

	int 	get_cash_total() { return cash_total; }
	int 	get_fee_per_family() { return fee_per_family; }
	int 	get_number_of_families() { return number_of_families; }

	int 	get_population_total() { return population_total; }
	int 	get_population_occupied() { return population_occupied; }
	int 	get_population_unoccupied() { return population_total - population_occupied; }

	float 	get_happiness_penalty();

	float 	get_happiness() { return happiness; }
	float 	get_awareness() { return awareness; }
};

#endif // __RESOURCE_MANAGER_H__
