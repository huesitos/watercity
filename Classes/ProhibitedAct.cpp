#include "ProhibitedAct.h"


ProhibitedAct::ProhibitedAct(int num_prohibited_acts)
	: num_prohibited_acts(num_prohibited_acts)
{
	if (num_prohibited_acts < 3)
		num_prohibited_acts = 3;

	if (num_prohibited_acts > 10)
		num_prohibited_acts = 10;

	file_names.push_back("images/c1.png");
	file_names.push_back("images/c2.png");
	file_names.push_back("images/c3.png");

	file_names_sprites.push_back("images/c11.png");
	file_names_sprites.push_back("images/c22.png");
	file_names_sprites.push_back("images/c33.png");

	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Vec2 house_pos_base(origin.x + visible_size.width * 0.18, 
						origin.y + visible_size.height * 0.48);

	Vec2 var_x(visible_size.width * 0.055, visible_size.height * -0.045);
	Vec2 var_y(visible_size.width * 0.13, visible_size.height * 0.11);

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 7; ++j)
			for(int k = 0; k < 2; ++k)
				is_occupied[i][j][k] = false;

	for (int i = 0; i < num_prohibited_acts; ++i)
	{
		int type = RandomHelper::random_int(0, 2);

		auto sprite = Sprite::create(file_names_sprites[type]);
		auto button_1 = ui::Button::create(file_names[0]);
		auto button_2 = ui::Button::create(file_names[1]);
		auto button_3 = ui::Button::create(file_names[2]);

		// Breakdowns of the same type share a tag up to the remainder
		// when divided by 10 so that they can be checked for equality of 
		// types while still being differentiable between individual 
		// breakdowns.
		sprite->setTag(type + 10 * i);
		button_1->setTag(0 + 10 * i);
		button_2->setTag(1 + 10 * i);
		button_3->setTag(2 + 10 * i);

		int x[3];
		int y[3];

		for (int j = 0; j < 3; ++j)
		{
			x[j] = RandomHelper::random_int(0, 6);
			y[j] = RandomHelper::random_int(0, 1);

			while (!is_open_space(i, x[j], y[j]))
			{
				x[j] = RandomHelper::random_int(0, 6);
				y[j] = RandomHelper::random_int(0, 1);
			}

			is_occupied[i][x[j]][y[j]] = true;
		}

		button_1->setPosition(house_pos_base + var_x * x[0] + var_y * y[0]);
		button_2->setPosition(house_pos_base + var_x * x[1] + var_y * y[1]);
		button_3->setPosition(house_pos_base + var_x * x[2] + var_y * y[2]);
		sprite->setPosition(Vec2(origin.x + visible_size.width * 0.25, origin.y + visible_size.height * 0.80));

		prohibited_acts.pushBack(button_1);
		prohibited_acts.pushBack(button_2);
		prohibited_acts.pushBack(button_3);
		prohibited_act_sprites.pushBack(sprite);
	}
}

bool ProhibitedAct::is_open_space(int n, int x, int y)
{
	return !is_occupied[n][x][y];
}
