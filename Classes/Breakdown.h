#ifndef __BREAKDOWN_H__
#define __BREAKDOWN_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;


enum breakdown_type
{
	kWrench,
	kFaucet,
	kToilet,
	kPipe,
};

class Breakdown
{
public:
	Breakdown(int num_breakdowns = 3);
	~Breakdown() {}

	Vector<ui::Button*> 	get_breakdowns() { return breakdowns; }
	Vector<Sprite*> 		get_breakdown_sprites() { return breakdown_sprites; }

private:
	Vector<ui::Button*> 	breakdowns;
	Vector<Sprite*> 		breakdown_sprites;

	int num_breakdowns;

	std::vector<Vec2> positions;
	std::vector<const char*> file_names;

	bool 	is_open_space(Vec2 pos);
};

#endif // __BREAKDOWN_H__
