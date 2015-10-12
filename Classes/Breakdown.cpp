#include "Breakdown.h"

USING_NS_CC;


std::vector<Breakdown> Breakdown::breakdowns;

Breakdown::Breakdown(int water_lost, int cash_spent)
	: water_lost(water_lost), cash_spent(cash_spent)
{}

void Breakdown::run_week(int num_breakdown_workers)
{
	const int EXPECTED_NUM_BREAKDOWNS 	= calc_expected_breakdowns(num_breakdown_workers);
	const int EXPECTED_WATER_LOST 		= calc_expected_water_lost();
	const int EXPECTED_CASH_SPENT 		= calc_expected_cash_spent();

	const int SPREAD_BREAKDOWNS = 1;
	const int SPREAD_WATER_LOST = 2;
	const int SPREAD_CASH_SPENT = 2;

	Breakdown::breakdowns.clear();

	int num_breakdowns = RandomHelper::random_int(EXPECTED_NUM_BREAKDOWNS - SPREAD_BREAKDOWNS, EXPECTED_NUM_BREAKDOWNS + SPREAD_BREAKDOWNS);

	for (int i = 0; i < num_breakdowns; ++i)
	{
		Breakdown::breakdowns.push_back(Breakdown(RandomHelper::random_int(EXPECTED_WATER_LOST - SPREAD_WATER_LOST, EXPECTED_WATER_LOST + SPREAD_WATER_LOST), 
									   RandomHelper::random_int(EXPECTED_CASH_SPENT - SPREAD_CASH_SPENT, EXPECTED_CASH_SPENT + SPREAD_CASH_SPENT)));
	}
}

int Breakdown::calc_expected_breakdowns(int num_breakdown_workers)
{
	return 5;
}

int Breakdown::calc_expected_water_lost()
{
	return 20;
}

int Breakdown::calc_expected_cash_spent()
{
	return 10;
}

int Breakdown::get_num_breakdowns()
{
	return static_cast<int>(Breakdown::breakdowns.size());
}

int Breakdown::get_water_lost()
{
	int water_lost = 0;

	for (int i = 0; i < static_cast<int>(Breakdown::breakdowns.size()); ++i)
	{
		water_lost += Breakdown::breakdowns[i].water_lost;
	}

	return water_lost;
}

int Breakdown::get_cash_spent()
{
	int cash_spent = 0;

	for (int i = 0; i < static_cast<int>(Breakdown::breakdowns.size()); ++i)
	{
		cash_spent += Breakdown::breakdowns[i].cash_spent;
	}

	return cash_spent;
}
