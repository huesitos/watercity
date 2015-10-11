#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__


class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		static ResourceManager *resource_manager = new ResourceManager;
		return *resource_manager;
	}

	// Update function to be called every frame
	void update(float dt);

	// Update function to be called on at the beginning of each
	// day by... (?)
	void update_day(float dt);

	// Checks whether the user has enough water
	bool has_enough_water(int water_cost);

	// Checks whether the user has enough cash
	bool has_enough_cash(int cash_cost);

	// Checks whether the user has enough happiness
	bool has_enough_happiness(float happiness_cost);

	// Spend some water from the reserve
	void spend_water(int water_cost);

	// Spend some cash from the reserve
	void spend_cash(int cash_cost);

	// Adds 'amount' to the total inflow
	void increase_inflow(int amount);
	// Substracts 'amount' to the total inflow
	void decrease_inflow(int amount);

	// Adds 'amount' to the total consumption
	void increase_consumption(int amount);
	// Substracts 'amount' to the total consumption
	void decrease_consumption(int amount);

	// Adds 'amount' to the total happiness
	void increase_happiness(float amount);
	// Substracts 'amount' to the total happiness
	void decrease_happiness(float amount);

	// Adds 'amount' to the total awareness
	void increase_awareness(float amount);
	// Substracts 'amount' to the total awareness
	void decrease_awareness(float amount);

	// Adds 'amount' to the minimum awareness
	void increase_awareness_min(float amount);

private:
	ResourceManager();

	// Resource Variables

	int 	water_reserves;
	int 	water_inflow;
	int 	water_consumption;

	int 	cash_total;
	int 	fee_per_family;
	int 	number_of_families;

	float 	happiness;
	float 	awareness;
	float 	awareness_min;

	// Decay rate in percentage points per second

	const float awareness_decay_rate = 5.0 / 60;

public:
	bool 	is_water_depleted() { return water_reserves == 0; }

	int 	get_water_reserves() { return water_reserves; }
	int 	get_water_inflow() { return water_inflow; }
	int 	get_water_consumption() { return water_consumption; }

	int 	get_cash_total() { return cash_total; }
	int 	get_fee_per_family() { return fee_per_family; }
	int 	get_number_of_families() { return number_of_families; }

	float 	get_happiness() { return happiness; }
	float 	get_awareness() { return awareness; }
};

#endif // __RESOURCE_MANAGER_H__