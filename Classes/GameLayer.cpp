#include "GameLayer.h"

Scene* GameLayer::createScene()
{
	auto scene = Scene::create();

	auto layer = GameLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    amount_of_line = 40.0f;
    amount_of_line_reserves = 103.0f;

    visible_size = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    top_right.x = origin.x + visible_size.width;
    top_right.y = origin.y + visible_size.height;

     // add sky background
    sky = Sprite::create("images/sky.png");
    sky->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sky->setPosition(origin);

    this->addChild(sky, -1);

    // add background
    background_town = Sprite::create("images/back.png");
    background_town->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_town->setPosition(origin);

    this->addChild(background_town, 1);


    shadow = Sprite::create("images/shadows/shadow.png");
    shadow->setPosition(Vec2(origin.x - shadow->getContentSize().width, origin.y + visible_size.height * 0.3));
    this->addChild(shadow, 1);

    shadow->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveTo::create(120.0f, Vec2(origin.x + visible_size.width + shadow->getContentSize().width, origin.y + visible_size.height * 0.3)),
                Place::create(Vec2(origin.x - shadow->getContentSize().width, origin.y + visible_size.height * 0.3)),
                nullptr
            ))
        );

    shadow2 = Sprite::create("images/shadows/shadow2.png");
    shadow2->setPosition(Vec2(origin.x - shadow2->getContentSize().width, origin.y + visible_size.height * 0.6));
    this->addChild(shadow2, 1);

    shadow2->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveTo::create(60.0f, Vec2(origin.x + visible_size.width + shadow2->getContentSize().width, origin.y + visible_size.height * 0.6)),
                Place::create(Vec2(origin.x - shadow2->getContentSize().width, origin.y + visible_size.height * 0.6)),
                        nullptr
            ))
        );


    // add river animation
    auto river = Sprite::create("images/river_anim/river1.png");
    river->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    river->setPosition(origin);

    this->addChild(river, 1);

    Vector<SpriteFrame*> frames;

    frames.pushBack(SpriteFrame::create("images/river_anim/river1.png", Rect(0, 0, visible_size.width, visible_size.height)));
    frames.pushBack(SpriteFrame::create("images/river_anim/river2.png", Rect(0, 0, visible_size.width, visible_size.height)));
    frames.pushBack(SpriteFrame::create("images/river_anim/river3.png", Rect(0, 0, visible_size.width, visible_size.height)));

    auto animation = Animation::createWithSpriteFrames(frames, 3.0f);
    auto animate = Animate::create(animation);
    river->runAction(RepeatForever::create(animate));
    frames.clear();

    // climate sprites
    sun_bg = Sprite::create("images/sun_anim/sun.png");
    sun_bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    sun_bg->setPosition(origin);
    sun_bg->setVisible(false);

    this->addChild(sun_bg, 1);

    rain_bg = Sprite::create("images/rainclouds.png");
    rain_bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    rain_bg->setPosition(origin);
    rain_bg->setVisible(false);

    this->addChild(rain_bg, 0);

    cloudy_bg = Sprite::create("images/cloudback.png");
    cloudy_bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    cloudy_bg->setPosition(origin);
    cloudy_bg->setVisible(false);

    this->addChild(cloudy_bg, -1);

    rain_drops = Sprite::create("images/rain_anim/raintop.png");
    rain_drops->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    rain_drops->setPosition(origin);
    rain_drops->setVisible(false);

    this->addChild(rain_drops, 1);

    frames.pushBack(SpriteFrame::create("images/rain_anim/raintop.png", Rect(0, 0, rain_drops->getContentSize().width, rain_drops->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/rain_anim/raintop2.png", Rect(0, 0, rain_drops->getContentSize().width, rain_drops->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/rain_anim/raintop3.png", Rect(0, 0, rain_drops->getContentSize().width, rain_drops->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/rain_anim/raintop4.png", Rect(0, 0, rain_drops->getContentSize().width, rain_drops->getContentSize().height)));

    animation = Animation::createWithSpriteFrames(frames, 0.5f);
    animate = Animate::create(animation);
    rain_drops->runAction(RepeatForever::create(animate));
    frames.clear();


    sunny = Sprite::create("images/sunny.png");
    cloudy = Sprite::create("images/cloudy.png");
    rainy = Sprite::create("images/rainy.png");

    sunny->setPosition(Vec2(origin.x + visible_size.width * 0.94, origin.y + visible_size.height * 0.34));
    cloudy->setPosition(Vec2(origin.x + visible_size.width * 0.94, origin.y + visible_size.height * 0.34));
    rainy->setPosition(Vec2(origin.x + visible_size.width * 0.94, origin.y + visible_size.height * 0.34));

    this->addChild(sunny, 3);
    this->addChild(cloudy, 3);
    this->addChild(rainy, 3);

    sunny->setOpacity(0);
    cloudy->setOpacity(0);
    rainy->setOpacity(0);


    frames.pushBack(SpriteFrame::create("images/sunny_anim/sunny.png", Rect(0, 0, sunny->getContentSize().width, sunny->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/sunny_anim/sunny2.png", Rect(0, 0, sunny->getContentSize().width, sunny->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/sunny_anim/sunny3.png", Rect(0, 0, sunny->getContentSize().width, sunny->getContentSize().height)));

    animation = Animation::createWithSpriteFrames(frames, 0.5f);
    animate = Animate::create(animation);
    sunny->runAction(RepeatForever::create(animate));
    frames.clear();


    frames.pushBack(SpriteFrame::create("images/cloudy_anim/cloudy.png", Rect(0, 0, cloudy->getContentSize().width, cloudy->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/cloudy_anim/cloudy2.png", Rect(0, 0, cloudy->getContentSize().width, cloudy->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/cloudy_anim/cloudy3.png", Rect(0, 0, cloudy->getContentSize().width, cloudy->getContentSize().height)));

    animation = Animation::createWithSpriteFrames(frames, 0.5f);
    animate = Animate::create(animation);
    cloudy->runAction(RepeatForever::create(animate));
    frames.clear();


    frames.pushBack(SpriteFrame::create("images/rainy_anim/rainy.png", Rect(0, 0, rainy->getContentSize().width, rainy->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/rainy_anim/rainy2.png", Rect(0, 0, rainy->getContentSize().width, rainy->getContentSize().height)));
    frames.pushBack(SpriteFrame::create("images/rainy_anim/rainy3.png", Rect(0, 0, rainy->getContentSize().width, rainy->getContentSize().height)));

    animation = Animation::createWithSpriteFrames(frames, 0.5f);
    animate = Animate::create(animation);
    rainy->runAction(RepeatForever::create(animate));

    if (climate.get_climate()==climate.SUNNY)
    {
        this->sunny->runAction(FadeIn::create(0.5f));
        this->sun_bg->setVisible(true);
        this->rain_bg->setVisible(false);
        this->rain_drops->setVisible(false);
        this->cloudy_bg->setVisible(false);

        this->shadow->setVisible(false);
        this->shadow2->setVisible(false);

    }
    else if (climate.get_climate()==climate.CLOUDY)
    {
        this->cloudy->runAction(FadeIn::create(0.5f));
        this->sun_bg->setVisible(false);
        this->rain_bg->setVisible(false);
        this->rain_drops->setVisible(false);
        this->cloudy_bg->setVisible(true);

        this->shadow->setVisible(true);
        this->shadow2->setVisible(true);

    }
    else
    {
        this->rainy->runAction(FadeIn::create(0.5f));
        this->sun_bg->setVisible(false);
        this->rain_bg->setVisible(true);
        this->rain_drops->setVisible(true);
        this->cloudy_bg->setVisible(false);

        this->shadow->setVisible(false);
        this->shadow2->setVisible(false);
    }


    // resources sprites
    happy = Sprite::create("images/happy.png");
    mad = Sprite::create("images/mad.png");

    happy->setPosition(Vec2(origin.x + visible_size.width * 0.771, origin.y + visible_size.height * 0.178));
    mad->setPosition(Vec2(origin.x + visible_size.width * 0.771, origin.y + visible_size.height * 0.178));

    this->addChild(happy, 3);
    this->addChild(mad, 3);

    if (rm.get_happiness() < 30)
    {
        happy->setVisible(false);
        mad->setVisible(true);
    }
    else if (rm.get_happiness() < 70)
    {
        happy->setVisible(false);
        mad->setVisible(false);
    }
    else
    {
        happy->setVisible(true);
        mad->setVisible(false);
    }

    water_reserves = Sprite::create("images/waterreserve.png");
    water_reserves->setPosition(Vec2(origin.x + visible_size.width * 0.055, origin.y + visible_size.height * 0.917));
    water_reserves->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(water_reserves, 3);

    water_meter = Sprite::create("images/meter4.png");
    water_meter->setPosition(Vec2(origin.x, origin.y + visible_size.height));
    water_meter->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    this->addChild(water_meter, 3);

    water_gallon = Sprite::create("images/gallon.png");
    water_gallon->setPosition(Vec2(origin.x + visible_size.width * 0.05, origin.y + visible_size.height * 0.03));
    water_gallon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(water_gallon, 2);

    background_consumption = Sprite::create("images/consumptionback.png");
    background_consumption->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_consumption->setPosition(origin);

    this->addChild(background_consumption, 1);

    background_resources = Sprite::create("images/resourcesmenu.png");
    background_resources->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    background_resources->setPosition(origin + Vec2(visible_size.width, 0));

    this->addChild(background_resources, 1);

	ministry_of_technology = MinistryOfTechnology::create("images/technology.png", "tech_projects.txt");
    ministry_of_technology->setPosition(origin.x + visible_size.width * 0.58, origin.y + visible_size.height * 0.66);

    this->addChild(ministry_of_technology, 1);

    menu_technology = ProjectMenuItem::create("images/techmenu.png", ministry_of_technology);
    menu_technology->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.60));
    this->addChild(menu_technology, 2);
    menu_technology->setVisible(false);
    ministry_of_technology->setup_listener();

    ministry_of_education = MinistryOfEducation::create("images/education.png", "tech_projects.txt");
    ministry_of_education->setPosition(origin.x + visible_size.width * 0.76, origin.y + visible_size.height * 0.53);
    this->addChild(ministry_of_education, 1);

    menu_education = ProjectMenuItem::create("images/edumenu.png", ministry_of_education);
    menu_education->setPosition(Vec2(origin.x + visible_size.width * 0.50, origin.y + visible_size.height * 0.60));
    this->addChild(menu_education, 2);
    menu_education->setVisible(false);
    ministry_of_education->setup_listener();

    ministry_of_culture = MinistryOfCulture::create("images/park.png", "tech_projects.txt");
    ministry_of_culture->setPosition(origin.x + visible_size.width * 0.64, origin.y + visible_size.height * 0.52);
    this->addChild(ministry_of_culture, 1);

    menu_culture = ProjectMenuItem::create("images/edumenu.png", ministry_of_culture);
    menu_culture->setPosition(Vec2(origin.x + visible_size.width * 0.45, origin.y + visible_size.height * 0.60));
    this->addChild(menu_culture, 2);
    menu_culture->setVisible(false);
    ministry_of_culture->setup_listener();

	run_week_button = ui::Button::create("images/start.png");
	run_week_button->setPosition(Vec2(origin.x + visible_size.width * 0.735 - run_week_button->getContentSize().width / 2,
		  origin.y + run_week_button->getContentSize().height / 2));
	run_week_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
			case ui::Widget::TouchEventType::BEGAN:
				this->run_week();
				break;
			default:
				break;
		}
	});

    this->addChild(run_week_button, 2);

    add_button = ui::Button::create("images/more.png");
    add_button->setPosition(Vec2(origin.x + visible_size.width * 0.21, origin.y + visible_size.height * 0.18));
    add_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                rm.increase_selected_consumption(amount_of_line);
                this->update_labels();
                break;
            default:
                break;
        }
    });

    this->addChild(add_button, 2);

    substract_button = ui::Button::create("images/less.png");
    substract_button->setPosition(Vec2(origin.x + visible_size.width * 0.21, origin.y + visible_size.height * 0.08));
    substract_button->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                rm.decrease_selected_consumption(amount_of_line);
                this->update_labels();
                break;
            default:
                break;
        }
    });

    this->addChild(substract_button, 2);

    add_labels();

    is_running_breakdowns_minigame = false;
    is_running_prohibited_acts_minigame = false;

    this->scheduleUpdate();

    return true;
}

void GameLayer::update(float dt)
{
    if (is_running_breakdowns_minigame)
    {
        breakdowns_countdown -= dt;

        breakdowns_clock->setString(StringUtils::format("%.0f", breakdowns_countdown + 0.5f));

        if (breakdowns_countdown < 0.0f)
        {
            is_running_breakdowns_minigame = false;
            end_breakdown_minigame();
        }
    }

    if (is_running_prohibited_acts_minigame)
    {
        prohibited_acts_countdown -= dt;

        prohibited_acts_clock->setString(StringUtils::format("%.0f", prohibited_acts_countdown + 0.5f));

        if (prohibited_acts_countdown < 0.0f)
        {
            is_running_prohibited_acts_minigame = false;
            end_prohibited_act_minigame();
        }
    }
}

void GameLayer::run_day()
{
    if (ministry_of_technology->has_project_running() ||
        ministry_of_education->has_project_running())
    {
        auto hap = rm.get_happiness();
        int chance;
        if (hap >= 70)
            chance = 0;
        else
            chance = static_cast<int>(50 * (70 - hap) / 70);

        if (chance > RandomHelper::random_int(0, 100))
        {
            did_riot_happen = true;
        }
        else
        {
            ministry_of_technology->develop_project();
            ministry_of_education->develop_project();

            if (hap >= 70 && 20 > RandomHelper::random_int(0, 100))
            {
                will_reward = true;
                cash_reward = RandomHelper::random_int(500, 1000);
            }
        }
    }

    if (ministry_of_culture->has_project_running())
    {
        ministry_of_culture->develop_project();
    }
    climate.rain();

    rm.update_day();
}

void GameLayer::run_week()
{
    did_riot_happen = false;
    will_reward = false;
    cash_reward = 0;

    menu_technology->setVisible(false);
    menu_education->setVisible(false);
    menu_culture->setVisible(false);

    for (int i = 0; i < 7; ++i)
        run_day();

    update_labels();

    menu_technology->update_projects();
    menu_education->update_projects();
    menu_culture->update_projects();

    menu_technology->update_labels();
    menu_education->update_labels();
    menu_culture->update_labels();

    start_breakdown_minigame();
    //start_prohibited_act_minigame();
}

void GameLayer::start_breakdown_minigame()
{
    turn_off_listeners();

    auto label = Label::createWithTTF("Oh no! There's been some breakdowns in the neighborhood!", "fonts/Marker Felt.ttf", 40);
    label->setTextColor(Color4B::BLACK);
    label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
    this->addChild(label, 5);
    label->setOpacity(0.0f);

    auto get_removed = CallFunc::create([this, label](){
       this->removeChild(label);
    });

    label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(1.0f),
        FadeOut::create(1.0f), get_removed, nullptr));

    this->runAction(Sequence::create(DelayTime::create(3.0f),
        CallFunc::create(CC_CALLBACK_0(GameLayer::run_breakdown_minigame, this)), nullptr));
}

void GameLayer::run_breakdown_minigame()
{
    Breakdown b(10);

    breakdowns = b.get_breakdowns();
    breakdown_sprites = b.get_breakdown_sprites();

    for (auto breakdown : breakdowns)
    {
        breakdown->setOpacity(0.0f);
        this->addChild(breakdown, 3);
        breakdown->runAction(FadeIn::create(0.5f));
    }

    for (int i = 0; i < static_cast<int>(breakdown_sprites.size()); ++i)
    {
        this->addChild(breakdown_sprites.at(i), 30 - i);
        breakdown_sprites.at(i)->setOpacity(0.0f);
    }

    breakdown_sprites.at(0)->setScale(1.0f);
    breakdown_sprites.at(0)->runAction(FadeIn::create(0.5f));
    breakdown_sprites.at(0)->setPosition(Vec2(origin.x + visible_size.width * 0.38, origin.y + visible_size.height * 0.80));

    breakdown_sprites.at(1)->runAction(FadeTo::create(0.5f, 150.0f));
    breakdown_sprites.at(1)->setPosition(Vec2(origin.x + visible_size.width * 0.28, origin.y + visible_size.height * 0.80));

    breakdown_sprites.at(2)->runAction(FadeTo::create(0.5f, 150.0f));

    for (auto breakdown : breakdowns)
    {
        breakdown->addTouchEventListener([this, breakdown](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    if (breakdown->getTag() % 10 == breakdown_sprites.at(0)->getTag() % 10)
                    {
                        this->on_correct_breakdown(breakdown);
                    }
                    else
                    {
                        this->on_incorrect_breakdown();
                    }
                    break;
                default:
                    break;
            }

            return true;
        });
    }

    breakdowns_countdown = 14.99f;

    breakdowns_clock = Label::createWithTTF(StringUtils::format("%d", static_cast<int>(breakdowns_countdown + 1)),
        "fonts/Marker Felt.ttf", 60);
    breakdowns_clock->setTextColor(Color4B::BLACK);
    breakdowns_clock->setPosition(Vec2(origin.x + visible_size.width * 0.08, origin.y + visible_size.height * 0.80));
    this->addChild(breakdowns_clock, 3);

    is_running_breakdowns_minigame = true;
}

void GameLayer::end_breakdown_minigame()
{
    this->removeChild(breakdowns_clock);

    if (static_cast<int>(breakdowns.size()) == 0)
    {
        auto label = Label::createWithTTF("You fixed all of the breakdowns!", "fonts/Marker Felt.ttf", 50);
        label->setTextColor(Color4B::BLACK);
        label->setDimensions(visible_size.width * 0.30, visible_size.height * 0.30);
        label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
        this->addChild(label, 5);
        label->setOpacity(0.0f);

        auto get_removed = CallFunc::create([this, label](){
            this->removeChild(label);
        });

        label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f),
            FadeOut::create(1.0f), get_removed, nullptr));

        int breakdowns_cash_reward = RandomHelper::random_int(0, 2);
        breakdowns_cash_reward = 500 + 250 * breakdowns_cash_reward;

        rm.spend_cash(-breakdowns_cash_reward);
        update_labels();

        auto label_reward = Label::createWithTTF(StringUtils::format("You earned $ %d", breakdowns_cash_reward), "fonts/Marker Felt.ttf", 50);
        label_reward->setTextColor(Color4B::BLACK);
        label_reward->setDimensions(visible_size.width * 0.30, visible_size.height * 0.30);
        label_reward->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.40));
        this->addChild(label_reward, 5);
        label_reward->setOpacity(0.0f);

        auto get_reward_removed = CallFunc::create([this, label_reward](){
            this->removeChild(label_reward);
        });

        label_reward->runAction(Sequence::create(DelayTime::create(2.0f), FadeIn::create(1.0f), DelayTime::create(2.0f),
            FadeOut::create(1.0f), get_reward_removed, nullptr));
    }
    else
    {
        for (auto breakdown : breakdowns)
        {
            this->removeChild(breakdown);
        }

        for (auto breakdown_sprite : breakdown_sprites)
        {
            this->removeChild(breakdown_sprite);
        }

        breakdowns.clear();
        breakdown_sprites.clear();

        auto label = Label::createWithTTF("You couldn't fix all of the breakdowns :(", "fonts/Marker Felt.ttf", 30);
        label->setTextColor(Color4B::BLACK);
        label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
        this->addChild(label, 5);
        label->setOpacity(0.0f);

        auto get_removed = CallFunc::create([this, label](){
            this->removeChild(label);
        });

        label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(1.0f),
            FadeOut::create(1.0f), get_removed, nullptr));
    }

    turn_on_listeners();

    report();
}

void GameLayer::on_correct_breakdown(ui::Button* breakdown_to_remove)
{
    this->removeChild(breakdown_to_remove);
    this->removeChild(breakdown_sprites.at(0));

    breakdowns.erase(std::find(breakdowns.begin(), breakdowns.end(), breakdown_to_remove));
    breakdown_sprites.erase(breakdown_sprites.begin());

    if (static_cast<int>(breakdowns.size()) == 0)
    {
        is_running_breakdowns_minigame = false;
        end_breakdown_minigame();
    }
    else
    {
        int breakdowns_left = static_cast<int>(breakdown_sprites.size());

        breakdown_sprites.at(0)->runAction(Sequence::create(
            Spawn::createWithTwoActions(MoveBy::create(0.25f, Vec2(visible_size.width * 0.10, 0)),
                                        ScaleTo::create(0.25f, 1.0f)),
            FadeIn::create(0.10f), nullptr));

        if (breakdowns_left > 1)
        {
            breakdown_sprites.at(1)->runAction(MoveBy::create(0.25f, Vec2(visible_size.width * 0.03, 0)));
        }

        if (breakdowns_left > 2)
        {
            breakdown_sprites.at(2)->runAction(FadeTo::create(0.5f, 150.0f));
        }
    }
}

void GameLayer::on_incorrect_breakdown()
{
    is_running_breakdowns_minigame = false;
    end_breakdown_minigame();
}

void GameLayer::start_prohibited_act_minigame()
{
    turn_off_listeners();

    auto label = Label::createWithTTF("Oh no! Some of them are wasting water!", "fonts/Marker Felt.ttf", 40);
    label->setTextColor(Color4B::BLACK);
    label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
    this->addChild(label, 5);
    label->setOpacity(0.0f);

    auto get_removed = CallFunc::create([this, label](){
       this->removeChild(label);
    });

    label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(1.0f),
        FadeOut::create(1.0f), get_removed, nullptr));

    this->runAction(Sequence::create(DelayTime::create(3.0f),
        CallFunc::create(CC_CALLBACK_0(GameLayer::run_prohibited_act_minigame, this)), nullptr));
}

void GameLayer::run_prohibited_act_minigame()
{
    ProhibitedAct p(8);

    prohibited_acts = p.get_prohibited_acts();
    prohibited_act_sprites = p.get_prohibited_act_sprites();

    for (int i = 0; i < static_cast<int>(prohibited_acts.size()); ++i)
    {
        //prohibited_acts.at(i)->setOpacity(0.0f);
        prohibited_acts.at(i)->setVisible(false);
        this->addChild(prohibited_acts.at(i), 90 - i);
    }

    prohibited_acts.at(0)->setTag(prohibited_acts.at(0)->getTag() + 200);
    prohibited_acts.at(1)->setTag(prohibited_acts.at(1)->getTag() + 200);
    prohibited_acts.at(2)->setTag(prohibited_acts.at(2)->getTag() + 200);

    prohibited_acts.at(0)->setVisible(true);
    prohibited_acts.at(1)->setVisible(true);
    prohibited_acts.at(2)->setVisible(true);

/*    prohibited_acts.at(0)->runAction(FadeIn::create(0.5f));
    prohibited_acts.at(1)->runAction(FadeIn::create(0.5f));
    prohibited_acts.at(2)->runAction(FadeIn::create(0.5f));*/

    for (int i = 0; i < static_cast<int>(prohibited_act_sprites.size()); ++i)
    {
        this->addChild(prohibited_act_sprites.at(i), 30 - i);
        prohibited_act_sprites.at(i)->setOpacity(0.0f);
    }

    prohibited_act_sprites.at(0)->setScale(1.0f);
    prohibited_act_sprites.at(0)->runAction(FadeIn::create(0.5f));
    prohibited_act_sprites.at(0)->setPosition(Vec2(origin.x + visible_size.width * 0.38, origin.y + visible_size.height * 0.80));

    prohibited_act_sprites.at(1)->runAction(FadeTo::create(0.5f, 150.0f));
    prohibited_act_sprites.at(1)->setPosition(Vec2(origin.x + visible_size.width * 0.28, origin.y + visible_size.height * 0.80));

    prohibited_act_sprites.at(2)->runAction(FadeTo::create(0.5f, 150.0f));

    for (auto prohibited_act : prohibited_acts)
    {
        prohibited_act->addTouchEventListener([this, prohibited_act](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    if (prohibited_act->isVisible() && prohibited_act->getTag() > 100)
                    {
                        if (prohibited_act->getTag() % 10 == prohibited_act_sprites.at(0)->getTag() % 10)
                        {
                            this->on_correct_prohibited_act();
                        }
                        else
                        {
                            this->on_incorrect_prohibited_act();
                        }
                    }
                    break;
                default:
                    break;
            }

            return true;
        });
    }

    prohibited_acts_countdown = 14.99f;

    prohibited_acts_clock = Label::createWithTTF(StringUtils::format("%d", static_cast<int>(prohibited_acts_countdown + 1)),
        "fonts/Marker Felt.ttf", 60);
    prohibited_acts_clock->setTextColor(Color4B::BLACK);
    prohibited_acts_clock->setPosition(Vec2(origin.x + visible_size.width * 0.08, origin.y + visible_size.height * 0.80));
    this->addChild(prohibited_acts_clock, 3);

    is_running_prohibited_acts_minigame = true;
}

void GameLayer::end_prohibited_act_minigame()
{
    this->removeChild(prohibited_acts_clock);

    if (static_cast<int>(prohibited_acts.size()) == 0)
    {
        auto label = Label::createWithTTF("You stopped all of that water wasting!", "fonts/Marker Felt.ttf", 50);
        label->setTextColor(Color4B::BLACK);
        label->setDimensions(visible_size.width * 0.30, visible_size.height * 0.30);
        label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
        this->addChild(label, 5);
        label->setOpacity(0.0f);

        auto get_removed = CallFunc::create([this, label](){
            this->removeChild(label);
        });

        label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(2.0f),
            FadeOut::create(1.0f), get_removed, nullptr));

        int prohibited_acts_water_reward = RandomHelper::random_int(0, 2);
        prohibited_acts_water_reward = 500 + 250 * prohibited_acts_water_reward;

        rm.spend_water(-prohibited_acts_water_reward);
        update_labels();

        auto label_reward = Label::createWithTTF(StringUtils::format("You saved %d gallons of water", prohibited_acts_water_reward), "fonts/Marker Felt.ttf", 50);
        label_reward->setTextColor(Color4B::BLACK);
        label_reward->setDimensions(visible_size.width * 0.30, visible_size.height * 0.30);
        label_reward->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.40));
        this->addChild(label_reward, 5);
        label_reward->setOpacity(0.0f);

        auto get_reward_removed = CallFunc::create([this, label_reward](){
            this->removeChild(label_reward);
        });

        label_reward->runAction(Sequence::create(DelayTime::create(2.0f), FadeIn::create(1.0f), DelayTime::create(2.0f),
            FadeOut::create(1.0f), get_reward_removed, nullptr));
    }
    else
    {
        for (auto prohibited_act : prohibited_acts)
        {
            this->removeChild(prohibited_act);
        }

        for (auto prohibited_act_sprite : prohibited_act_sprites)
        {
            this->removeChild(prohibited_act_sprite);
        }

        prohibited_acts.clear();
        prohibited_act_sprites.clear();

        auto label = Label::createWithTTF("You didn't stop the water from being wasted :(", "fonts/Marker Felt.ttf", 30);
        label->setTextColor(Color4B::BLACK);
        label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
        this->addChild(label, 5);
        label->setOpacity(0.0f);

        auto get_removed = CallFunc::create([this, label](){
            this->removeChild(label);
        });

        label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(1.0f),
            FadeOut::create(1.0f), get_removed, nullptr));
    }

    turn_on_listeners();

    report();
}

void GameLayer::on_correct_prohibited_act()
{
    this->removeChild(prohibited_acts.at(0));
    this->removeChild(prohibited_acts.at(1));
    this->removeChild(prohibited_acts.at(2));
    this->removeChild(prohibited_act_sprites.at(0));

    prohibited_acts.erase(prohibited_acts.begin(), prohibited_acts.begin() + 3);
    prohibited_act_sprites.erase(prohibited_act_sprites.begin());

    if (static_cast<int>(prohibited_acts.size()) == 0)
    {
        is_running_prohibited_acts_minigame = false;
        end_prohibited_act_minigame();
    }
    else
    {
        prohibited_acts.at(0)->setTag(prohibited_acts.at(0)->getTag() + 200);
        prohibited_acts.at(1)->setTag(prohibited_acts.at(1)->getTag() + 200);
        prohibited_acts.at(2)->setTag(prohibited_acts.at(2)->getTag() + 200);

        prohibited_acts.at(0)->setVisible(true);
        prohibited_acts.at(1)->setVisible(true);
        prohibited_acts.at(2)->setVisible(true);

/*        prohibited_acts.at(0)->runAction(FadeIn::create(0.25f));
        prohibited_acts.at(1)->runAction(FadeIn::create(0.25f));
        prohibited_acts.at(2)->runAction(FadeIn::create(0.25f));*/

        int prohibited_acts_left = static_cast<int>(prohibited_act_sprites.size());

        prohibited_act_sprites.at(0)->runAction(Sequence::create(
            Spawn::createWithTwoActions(MoveBy::create(0.25f, Vec2(visible_size.width * 0.10, 0)),
                                        ScaleTo::create(0.25f, 1.0f)),
            FadeIn::create(0.10f), nullptr));

        if (prohibited_acts_left > 1)
        {
            prohibited_act_sprites.at(1)->runAction(MoveBy::create(0.25f, Vec2(visible_size.width * 0.03, 0)));
        }

        if (prohibited_acts_left > 2)
        {
            prohibited_act_sprites.at(2)->runAction(FadeTo::create(0.5f, 150.0f));
        }
    }
}

void GameLayer::on_incorrect_prohibited_act()
{
    is_running_prohibited_acts_minigame = false;
    end_prohibited_act_minigame();
}

void GameLayer::report()
{
    update_labels();

    if (rm.is_water_depleted())
    {
        game_over();
    }

    if (rm.get_water_reserves() >= 50000 && rm.get_actual_water_consumption() == rm.get_desired_water_consumption())
    {
        finished();
    }

    if (did_riot_happen && (ministry_of_technology->has_project_running() || ministry_of_education->has_project_running()))
    {
        auto label = Label::createWithTTF("Oh no! The people rioted. Your projects were not completed.",
            "fonts/Marker Felt.ttf", 30);
        label->setTextColor(Color4B::BLACK);
        label->setPosition(Vec2(origin.x + visible_size.width * 0.40, origin.y + visible_size.height * 0.60));
        this->addChild(label, 5);
        label->setOpacity(0.0f);

        auto get_removed = CallFunc::create([this, label](){
            this->removeChild(label);
        });

        label->runAction(Sequence::create(FadeIn::create(1.0f), DelayTime::create(1.0f),
            FadeOut::create(1.0f), get_removed, nullptr));
    }
    else if (will_reward)
    {

    }

    if (ministry_of_culture->has_project_running())
    {
        ministry_of_culture->stop_project();
        this->update_labels();
        menu_culture->update_labels();
    }

    climate.set_week_climate();
    sunny->setOpacity(0);
    cloudy->setOpacity(0);
    rainy->setOpacity(0);

    if (climate.get_climate()==climate.SUNNY)
    {
        this->sunny->runAction(FadeIn::create(0.5f));
        this->sun_bg->setVisible(true);
        this->rain_bg->setVisible(false);
        this->rain_drops->setVisible(false);
        this->cloudy_bg->setVisible(false);

        this->shadow->setVisible(false);
        this->shadow2->setVisible(false);

    }
    else if (climate.get_climate()==climate.CLOUDY)
    {
        this->cloudy->runAction(FadeIn::create(0.5f));
        this->sun_bg->setVisible(false);
        this->rain_bg->setVisible(false);
        this->rain_drops->setVisible(false);
        this->cloudy_bg->setVisible(true);

        this->shadow->setVisible(true);
        this->shadow2->setVisible(true);
    }
    else
    {
        this->rainy->runAction(FadeIn::create(0.5f));
        this->sun_bg->setVisible(false);
        this->rain_bg->setVisible(true);
        this->rain_drops->setVisible(true);
        this->cloudy_bg->setVisible(false);

        this->shadow->setVisible(false);
        this->shadow2->setVisible(false);
    }
}

void GameLayer::update_labels()
{
    _happinessLabel->setString(StringUtils::format("%.0f%%", rm.get_happiness()));
    _happinessPenaltyLabel->setString(StringUtils::format("%.0f", rm.get_happiness_penalty() * 7));
    _awarenessLabel->setString(StringUtils::format("%.0f%%", rm.get_awareness()));
    _waterReservesLabel->setString(StringUtils::format("%d", rm.get_water_reserves()));
    _selectedWaterConsumptionLabel->setString(StringUtils::format("%d gl", rm.get_selected_water_consumption() * 7));

    _cashLabel->setString(StringUtils::format("$%d", rm.get_cash_total()));
    _feeLabel->setString(StringUtils::format("$%d", rm.get_fee_per_family()*rm.get_number_of_families()*7));
    _populationLabel->setString(StringUtils::format("%d / %d",
        rm.get_population_total()-rm.get_population_occupied(),
        rm.get_population_total()));


    // update gallon
    int current_num_lines = (rm.get_selected_water_consumption() - rm.get_desired_water_consumption()) / amount_of_line;
    int i = 0;

    auto wl = Sprite::create("images/galonaguamedio.png");

    float new_water_lines = (rm.get_actual_water_consumption() - rm.get_desired_water_consumption()) / amount_of_line;
    actual_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.70) * new_water_lines);

    for (; i < current_num_lines; ++i)
    {
        water_lines.at(i)->setVisible(true);
    }
    for (; i < num_of_water_lines_gallon; ++i)
    {
        water_lines.at(i)->setVisible(false);
    }


    //update reserves
    current_num_lines = rm.get_water_reserves() / (rm.get_water_reserves_limit() / amount_of_line_reserves);

    wl = Sprite::create("images/meteragua2.png");

    for (i = 0; i < current_num_lines ; ++i)
    {
        water_lines_meter.at(i)->setVisible(true);
    }
    for (; i < num_of_water_lines_meter ; ++i)
    {
        water_lines_meter.at(i)->setVisible(false);
    }


    if (rm.get_happiness() < 30)
    {
        happy->setVisible(false);
        mad->setVisible(true);
    }
    else if (rm.get_happiness() < 70)
    {
        happy->setVisible(false);
        mad->setVisible(false);
    }
    else
    {
        happy->setVisible(true);
        mad->setVisible(false);
    }
}

void GameLayer::add_labels()
{
    int fontSize = 18;

    _happinessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", rm.get_happiness()), "fonts/Marker Felt.ttf", fontSize);
    _happinessLabel->setPosition(Vec2(origin.x + visible_size.width * 0.81, origin.y + visible_size.height * 0.19));

    _awarenessLabel = Label::createWithTTF(StringUtils::format("%.0f%%", rm.get_awareness()), "fonts/Marker Felt.ttf", fontSize);
    _awarenessLabel->setPosition(Vec2(origin.x + visible_size.width * 0.81, origin.y + visible_size.height * 0.12));

    _waterReservesLabel = Label::createWithTTF(StringUtils::format("%d",
            rm.get_water_reserves()), "fonts/Marker Felt.ttf", fontSize);
    _waterReservesLabel->setPosition(Vec2(origin.x+110, origin.y + visible_size.height - 36));

    _selectedWaterConsumptionLabel = Label::createWithTTF(StringUtils::format("%d gl",
            rm.get_selected_water_consumption() * 7), "fonts/Marker Felt.ttf", fontSize);
    _selectedWaterConsumptionLabel->setPosition(Vec2(origin.x + visible_size.width * 0.095, origin.y + visible_size.height * 0.08));

    _cashLabel = Label::createWithTTF(StringUtils::format("$%d", rm.get_cash_total()), "fonts/Marker Felt.ttf", fontSize);
    _cashLabel->setPosition(Vec2(origin.x + visible_size.width * 0.93, origin.y + visible_size.height * 0.19));

    _feeLabel = Label::createWithTTF(StringUtils::format("$%d", rm.get_fee_per_family()*rm.get_number_of_families()*7), "fonts/Marker Felt.ttf", fontSize);
    _feeLabel->setPosition(Vec2(origin.x + visible_size.width * 0.948, origin.y + visible_size.height * 0.11));

    _populationLabel = Label::createWithTTF(StringUtils::format("%d / %d",
        rm.get_population_total()-rm.get_population_occupied(), rm.get_population_total()),
        "fonts/Marker Felt.ttf", fontSize);
    _populationLabel->setPosition(Vec2(origin.x + visible_size.width * 0.87, origin.y + visible_size.height * 0.055));

    _happinessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _awarenessLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _waterReservesLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _selectedWaterConsumptionLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _cashLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _populationLabel->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

    _happinessLabel->setTextColor(Color4B::WHITE);
    _awarenessLabel->setTextColor(Color4B::WHITE);
    _waterReservesLabel->setTextColor(Color4B::WHITE);
    _selectedWaterConsumptionLabel->setTextColor(Color4B::WHITE);
    _cashLabel->setTextColor(Color4B::WHITE);
    _feeLabel->setTextColor(Color4B::WHITE);
    _populationLabel->setTextColor(Color4B::WHITE);

    this->addChild(_happinessLabel, 3);
    this->addChild(_awarenessLabel, 3);
    this->addChild(_waterReservesLabel, 3);
    this->addChild(_selectedWaterConsumptionLabel, 3);
    this->addChild(_cashLabel, 3);
    this->addChild(_feeLabel, 3);
    this->addChild(_populationLabel, 3);

    _happinessPenaltyLabel = Label::createWithTTF(StringUtils::format("%.0f", rm.get_happiness_penalty() * 7), "fonts/Marker Felt.ttf", fontSize);
    _happinessPenaltyLabel->setPosition(Vec2(origin.x + visible_size.width * 0.13, origin.y + visible_size.height * 0.02));

    this->addChild(_happinessPenaltyLabel, 3);


    // galon de agua
    num_of_water_lines_gallon = (rm.get_actual_water_consumption()-rm.get_desired_water_consumption())/amount_of_line;

    desired_consumption = Sprite::create("images/need.png");
    actual_consumption = Sprite::create("images/want.png");

    // el actual deberia tener el mismo height?
    auto wl = Sprite::create("images/galonaguamedio.png");

    desired_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.40));
    actual_consumption->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.70) * num_of_water_lines_gallon);

    this->addChild(desired_consumption, 3);
    this->addChild(actual_consumption, 2);

    for (int i = 0; i < num_of_water_lines_gallon; ++i)
    {
        auto wl = Sprite::create("images/galonaguamedio.png");
        wl->setPosition(Vec2(origin.x + visible_size.width * 0.12, origin.y + visible_size.height * 0.1425)
            + Vec2(0, wl->getContentSize().height * 0.70) * i);
        wl->setVisible(false);

        this->addChild(wl, 1);
        water_lines.pushBack(wl);
    }

    int current_num_lines = (rm.get_selected_water_consumption() - rm.get_desired_water_consumption()) / amount_of_line;
    for (int i = 0; i < current_num_lines; ++i)
    {
        water_lines.at(i)->setVisible(true);
    }



    // galon de agua
    num_of_water_lines_meter = amount_of_line_reserves;

    wl = Sprite::create("images/meteragua1.png");
    wl->setPosition(Vec2(origin.x + visible_size.width * 0.03, origin.y + visible_size.height * 0.170));
    this->addChild(wl, 1);

    for (int i = 0; i < num_of_water_lines_meter; ++i)
    {
        wl = Sprite::create("images/meteragua2.png");
        wl->setPosition(Vec2(origin.x + visible_size.width * 0.03, origin.y + visible_size.height * 0.178)
            + Vec2(0, wl->getContentSize().height * 0.70) * i);
        wl->setVisible(false);

        this->addChild(wl, 1);
        water_lines_meter.pushBack(wl);
    }

    current_num_lines = amount_of_line_reserves;
    for (int i = 0; i < current_num_lines; ++i)
    {
        water_lines_meter.at(i)->setVisible(true);
    }
}

void GameLayer::turn_off_listeners()
{
    ministry_of_technology->disable_listener();
    ministry_of_education->disable_listener();
    ministry_of_culture->disable_listener();
    menu_technology->pause();
    menu_education->pause();
    menu_culture->pause();
    run_week_button->pause();
    add_button->pause();
    substract_button->pause();
}

void GameLayer::turn_on_listeners()
{
    ministry_of_technology->enable_listener();
    ministry_of_education->enable_listener();
    ministry_of_culture->enable_listener();
    menu_technology->resume();
    menu_education->resume();
    menu_culture->resume();
    run_week_button->resume();
    add_button->resume();
    substract_button->resume();
}

void GameLayer::game_over()
{
    menu_technology->setVisible(false);
    menu_education->setVisible(false);
    turn_off_listeners();

    auto gameOver = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 50);
    gameOver->setPosition(visible_size.width/2, visible_size.height/2);

    this->addChild(gameOver, 10);

    auto main_menu = ui::Button::create("images/play.png");
    main_menu->setPosition(Vec2(origin.x + visible_size.width/2,
                                      origin.y + visible_size.height/2 + - main_menu->getContentSize().height));
    main_menu->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene()));
                break;
            default:
                break;
        }

        return true;
    });

    this->addChild(main_menu, 10);
}

void GameLayer::finished()
{
    menu_technology->setVisible(false);
    menu_education->setVisible(false);
    turn_off_listeners();

    auto gameOver = Label::createWithTTF("Congrats!", "fonts/Marker Felt.ttf", 50);
    gameOver->setPosition(visible_size.width/2, visible_size.height/2);

    this->addChild(gameOver, 10);

    auto main_menu = ui::Button::create("images/play.png");
    main_menu->setPosition(Vec2(origin.x + visible_size.width/2,
                                      origin.y + visible_size.height/2 + - main_menu->getContentSize().height));
    main_menu->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameLayer::createScene()));
                break;
            default:
                break;
        }

        return true;
    });

    this->addChild(main_menu, 10);
}
