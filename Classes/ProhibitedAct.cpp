#include "ProhibitedAct.h"

USING_NS_CC;


std::vector<ProhibitedAct> ProhibitedAct::prohibited_acts;

ProhibitedAct::ProhibitedAct(int water_lost, int happiness_cost)
	: water_lost(water_lost), happiness_cost(happiness_cost)
{}

void ProhibitedAct::run_week(int num_cultural_workers)
{
	const int EXPECTED_NUM_PROHIBITED_ACTS 	= calc_expected_prohibited_acts(num_cultural_workers);
	const int EXPECTED_WATER_LOST 			= calc_expected_water_lost();
	const int EXPECTED_HAPPINESS_COST 		= calc_expected_happiness_cost();

	const int SPREAD_PROHIBITED_ACTS 	= 1;
	const int SPREAD_WATER_LOST 		= 2;

	ProhibitedAct::prohibited_acts.clear();

	int num_prohibited_acts = RandomHelper::random_int(EXPECTED_NUM_PROHIBITED_ACTS - SPREAD_PROHIBITED_ACTS, EXPECTED_NUM_PROHIBITED_ACTS + SPREAD_PROHIBITED_ACTS);

	for (int i = 0; i < num_prohibited_acts; ++i)
	{
		ProhibitedAct::prohibited_acts.push_back(ProhibitedAct(RandomHelper::random_int(EXPECTED_WATER_LOST - SPREAD_WATER_LOST, EXPECTED_WATER_LOST + SPREAD_WATER_LOST), 
									   	   		2));
	}
}

int ProhibitedAct::calc_expected_prohibited_acts(int num_cultural_workers)
{
	return 3;
}

int ProhibitedAct::calc_expected_water_lost()
{
	return 25;
}

int ProhibitedAct::calc_expected_happiness_cost()
{
	return 2;
}

int ProhibitedAct::get_num_prohibited_acts()
{
	return static_cast<int>(ProhibitedAct::prohibited_acts.size());
}

int ProhibitedAct::get_water_lost()
{
	int water_lost = 0;

	for (int i = 0; i < static_cast<int>(ProhibitedAct::prohibited_acts.size()); ++i)
	{
		water_lost += ProhibitedAct::prohibited_acts[i].water_lost;
	}

	return water_lost;
}

int ProhibitedAct::get_happiness_cost()
{
	return 0;
}
