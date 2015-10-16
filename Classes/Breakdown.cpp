#include "Breakdown.h"


Breakdown::Breakdown(int num_breakdowns)
	: num_breakdowns(num_breakdowns)
{
	if (num_breakdowns < 3)
		num_breakdowns = 3;

	file_names.push_back("a1.png");
	file_names.push_back("a2.png");
	file_names.push_back("a3.png");
	file_names.push_back("a4.png");

	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (int i = 0; i < num_breakdowns; ++i)
	{
		int type = RandomHelper::random_int(0, 3);

		auto sprite = Sprite::create(file_names[type]);
		auto button = ui::Button::create(file_names[type]);
		sprite->setTag(type);
		button->setTag(type);

		Vec2 pos(RandomHelper::random_real(origin.x, origin.x + visible_size.width), 
				 RandomHelper::random_real(origin.y, origin.y + visible_size.height));

		while (!is_open_space(pos))
		{
			pos.x = RandomHelper::random_real(origin.x, origin.x + visible_size.width);
			pos.y = RandomHelper::random_real(origin.y, origin.y + visible_size.height);
		}

		button->setPosition(pos);
		sprite->setPosition(Vec2(origin.x + visible_size.width * (0.20 + 0.10 * i), origin.y + visible_size.height * 0.10));

		breakdowns.pushBack(button);
		breakdown_sprites.pushBack(sprite);
	}
}

bool Breakdown::is_open_space(Vec2 pos)
{
	bool result = true;
	Size visible_size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (pos.x < origin.x + visible_size.width * 0.15 ||
		pos.x > origin.x + visible_size.width * 0.85 ||
		pos.y < origin.y + visible_size.height * 0.25 || 
		pos.y > origin.y + visible_size.height * 0.85)
	{
		result = false;
	}

	float x_gap = visible_size.width * 0.10;
	float y_gap = visible_size.height * 0.10;

	for (int i = 0; i < static_cast<int>(positions.size()); ++i)
	{
		if ((-x_gap < pos.x - positions[i].x || pos.x - positions[i].x < x_gap) && 
			(-y_gap < pos.y - positions[i].y || pos.y - positions[i].y < y_gap))
		{
			result = false;
		}
	}

	return result;
}
