#ifndef __PROHIBITED_ACT_H__
#define __PROHIBITED_ACT_H__

#include "cocos2d.h"
#include <vector>


class ProhibitedAct
{
public:
	~ProhibitedAct() {}

	static void 	run_week(int num_cultural_workers);

	static int 		get_num_prohibited_acts();
	static int 		get_water_lost();
	static int 		get_happiness_cost();

private:
	static std::vector<ProhibitedAct> prohibited_acts;

	static int 		calc_expected_prohibited_acts(int num_cultural_workers);
	static int 		calc_expected_water_lost();
	static int 		calc_expected_happiness_cost();

	ProhibitedAct(int water_lost, int happiness_cost);

	int 	water_lost;
	int 	happiness_cost;
};

#endif // __PROHIBITED_ACT_H__
