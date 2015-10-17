#include "ProhibitedAct.h"


ProhibitedAct::ProhibitedAct(int num_prohibited_acts)
	: num_prohibited_acts(num_prohibited_acts)
{
	if (num_prohibited_acts < 3)
		num_prohibited_acts = 3;

	file_names.push_back("a1.png");
	file_names.push_back("a2.png");
	file_names.push_back("a3.png");

	file_names_sprites.push_back("a11.png");
	file_names_sprites.push_back("a22.png");
	file_names_sprites.push_back("a33.png");

	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 house_pos_base(origin.x + visible_size.width * 0.18, 
						origin.y + visible_size.height * 0.48);

	Vec2 var_x(visible_size.width * 0.055, visible_size.height * -0.045);
	Vec2 var_y(visible_size.width * 0.13, visible_size.height * 0.11);

	for (int i = 0; i < 7; ++i)
		for(int j = 0; j < 2; ++j)
			is_occupied[i][j] = false;

	for (int i = 0; i < num_prohibited_acts; ++i)
	{
		int type = RandomHelper::random_int(0, 3);

		auto sprite = Sprite::create(file_names_sprites[type]);
		auto button = ui::Button::create(file_names[type]);

		// Breakdowns of the same type share a tag up to the remainder
		// when divided by 10 so that they can be checked for equality of 
		// types while still being differentiable between individual 
		// breakdowns.
		sprite->setTag(type + 10 * i);
		button->setTag(type + 10 * i);

		int x = RandomHelper::random_int(0, 6);
		int y = RandomHelper::random_int(0, 1);

		while (!is_open_space(x, y))
		{
			x = RandomHelper::random_int(0, 6);
			y = RandomHelper::random_int(0, 1);
		}

		is_occupied[x][y] = true;

		button->setPosition(house_pos_base + var_x * x + var_y * y);
		sprite->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.80));
		sprite->setVisible(false);

		prohibited_acts.pushBack(button);
		prohibited_act_sprites.pushBack(sprite);
	}
}

bool ProhibitedAct::is_open_space(int x, int y)
{
	return !is_occupied[x][y];
}
