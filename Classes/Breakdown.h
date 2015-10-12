#ifndef __BREAKDOWN_H__
#define __BREAKDOWN_H__

#include "cocos2d.h"
#include <vector>


class Breakdown
{
public:
	~Breakdown() {}

	static void 	run_week(int num_breakdown_workers);

	static int 		get_num_breakdowns();
	static int 		get_water_lost();
	static int 		get_cash_spent();

private:
	static std::vector<Breakdown> breakdowns;

	static int 		calc_expected_breakdowns(int num_breakdown_workers);
	static int 		calc_expected_water_lost();
	static int 		calc_expected_cash_spent();

	Breakdown(int water_lost, int cash_spent);

	int 	water_lost;
	int 	cash_spent;
};

#endif // __BREAKDOWN_H__
