#include "GameLayer.h"
#include "Breakdown.h"
#include "ProhibitedAct.h"
#include "Climate.h"
#include "Project.h"

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

    // initialize sprites
    sunny = Sprite::create("images/sunny.png");
    cloudy = Sprite::create("images/cloudy.png");
    rainy = Sprite::create("images/rainy.png");

    sunny->setPosition(Vec2(origin.x + visible_size.width * 0.97, origin.y + visible_size.height * 0.40));
    cloudy->setPosition(Vec2(origin.x + visible_size.width * 0.97, origin.y + visible_size.height * 0.40));
    rainy->setPosition(Vec2(origin.x + visible_size.width * 0.97, origin.y + visible_size.height * 0.40));

    this->addChild(sunny, 3);
    this->addChild(cloudy, 3);
    this->addChild(rainy, 3);

    sunny->setVisible(false);
    cloudy->setVisible(false);
    rainy->setVisible(false);

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



    if (climate.get_climate()==climate.SUNNY)
    {
        this->sunny->setVisible(true);
    }
    else if (climate.get_climate()==climate.CLOUDY)
    {
        this->cloudy->setVisible(true);
    }
    else
    {
        this->rainy->setVisible(true);
    }

    background_town = Sprite::create("images/back.png");
    background_town->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    background_town->setPosition(origin);

    this->addChild(background_town, 1);

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

    return true;
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
}

void GameLayer::start_breakdown_minigame()
{
    turn_off_listeners();
    ministry_of_technology->setVisible(false);
    ministry_of_education->setVisible(false);

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
    Breakdown b(3);

    breakdowns = b.get_breakdowns();
    breakdown_sprites = b.get_breakdown_sprites();

    for (auto breakdown : breakdowns)
    {
        breakdown->setOpacity(0.0f);
        this->addChild(breakdown, 3);
        breakdown->runAction(FadeIn::create(0.5f));
    }

    for (auto breakdown_sprite : breakdown_sprites)
    {
        breakdown_sprite->setOpacity(0.0f);
        this->addChild(breakdown_sprite, 3);
        breakdown_sprite->runAction(FadeIn::create(0.5f));
    }

    for (auto breakdown : breakdowns)
    {
        breakdown->addTouchEventListener([this, breakdown](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type)
            {
                case ui::Widget::TouchEventType::BEGAN:
                    if (breakdown->getTag() == breakdown_sprites.at(0)->getTag())
                    {
                        this->on_correct_breakdown();
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
}

void GameLayer::end_breakdown_minigame()
{
    if (static_cast<int>(breakdowns.size()) == 0)
    {
        auto label = Label::createWithTTF("You fixed all of the breakdowns!", "fonts/Marker Felt.ttf", 30);
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

    ministry_of_technology->setVisible(true);
    ministry_of_education->setVisible(true);
    turn_on_listeners();

    report();
}

void GameLayer::on_correct_breakdown()
{
    this->removeChild(breakdowns.at(0));
    this->removeChild(breakdown_sprites.at(0));

    breakdowns.erase(breakdowns.begin());
    breakdown_sprites.erase(breakdown_sprites.begin());

    for (auto breakdown_sprite : breakdown_sprites)
    {
        breakdown_sprite->runAction(MoveBy::create(0.25f, Vec2(visible_size.width * -0.10, 0)));
    }

    if (static_cast<int>(breakdowns.size()) == 0)
    {
        end_breakdown_minigame();
    }
}

void GameLayer::on_incorrect_breakdown()
{
    end_breakdown_minigame();
}

void GameLayer::report()
{
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
    sunny->setVisible(false);
    cloudy->setVisible(false);
    rainy->setVisible(false);

    if (climate.get_climate()==climate.SUNNY)
    {
        this->sunny->setVisible(true);
    }
    else if (climate.get_climate()==climate.CLOUDY)
    {
        this->cloudy->setVisible(true);
    }
    else
    {
        this->rainy->setVisible(true);
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
    printf("%d\n", current_num_lines);

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
    ministry_of_technology->pause();
    ministry_of_education->pause();
    menu_technology->pause();
    menu_education->pause();
    run_week_button->pause();
    add_button->pause();
    substract_button->pause();
}

void GameLayer::turn_on_listeners()
{
    ministry_of_technology->resume();
    ministry_of_education->resume();
    menu_technology->resume();
    menu_education->resume();
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
