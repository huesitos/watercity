#ifndef __PROHIBITED_ACT_H__
#define __PROHIBITED_ACT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <vector>

USING_NS_CC;


class ProhibitedAct
{
public:
	ProhibitedAct(int num_prohibited_acts = 3);
	~ProhibitedAct() {}

	Vector<ui::Button*> 	get_prohibited_acts() { return prohibited_acts; }
	Vector<Sprite*> 		get_prohibited_act_sprites() { return prohibited_act_sprites; }

private:
	Vector<ui::Button*> 	prohibited_acts;
	Vector<Sprite*> 		prohibited_act_sprites;

	int num_prohibited_acts;

	std::vector<Vec2> positions;
	std::vector<const char*> file_names;
	std::vector<const char*> file_names_sprites;

	bool 	is_occupied[7][2] = {{0}};
	bool 	is_open_space(int x, int y);
};

#endif // __PROHIBITED_ACT_H__
