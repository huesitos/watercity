#include "ProjectMenuItem.h"
#include "ResourceManager.h"
#include "GameLayer.h"
#include <iostream>
#include <string>
#include <fstream>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


Ministry::Ministry()
{}

Ministry::~Ministry()
{}

bool Ministry::init(const char* pszFileName, const char* projectsFileName)
{
	if (initWithFile(pszFileName))
	{
		setup_projects(projectsFileName);
		return true;
	}

	return false;
}

bool Ministry::has_project()
{
	return static_cast<int>(get_projects_to_display().size()) > 0;
}

bool Ministry::can_be_funded()
{
	ResourceManager &rm = ResourceManager::getInstance();

	auto p = get_projects_set_to_start();

	int total_water_cost = 0;
	int total_cash_cost = 0;

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		total_water_cost += p[i]->get_water_cost();
		total_cash_cost += p[i]->get_cash_cost();
	}

	return rm.has_enough_water(total_water_cost) && rm.has_enough_cash(total_cash_cost);
}

std::vector<Project*> Ministry::get_projects_to_display()
{
	std::vector<Project*> p;

	const int MAX_PROJECTS = 1;
	int size = 0;

	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		if (!projects[i]->is_completed())
		{
			p.push_back(projects[i]);
			size++;

			if (size == MAX_PROJECTS)
				break;
		}
	}

	return p;
}

std::vector<Project*> Ministry::get_projects_running()
{
	std::vector<Project*> p;

	const int MAX_PROJECTS = 1;
	int size = 0;

	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		if (projects[i]->is_running())
		{
			p.push_back(projects[i]);
			size++;

			if (size == MAX_PROJECTS)
				break;
		}
	}

	return p;
}

std::vector<Project*> Ministry::get_projects_set_to_start()
{
	std::vector<Project*> p;

	const int MAX_PROJECTS = 1;
	int size = 0;

	for (int i = 0; i < static_cast<int>(projects.size()); ++i)
	{
		if (projects[i]->is_set_to_start())
		{
			p.push_back(projects[i]);
			size++;

			if (size == MAX_PROJECTS)
				break;
		}
	}

	return p;
}

void Ministry::start_project()
{
	ResourceManager &rm = ResourceManager::getInstance();

	auto p = get_projects_set_to_start();

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		p[i]->start_project();

		rm.spend_water(p[i]->get_water_cost());
		rm.spend_cash(p[i]->get_cash_cost());
	}

	((GameLayer*) this->getParent())->update_labels();

	animate_icon();
}

void Ministry::develop_project()
{
	auto p = get_projects_running();

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		p[i]->develop();

		if (p[i]->is_completed())
		{
			p[i]->complete();
			stop_animate_icon();
		}
	}
}

bool Ministry::has_project_running()
{
	return static_cast<int>(get_projects_running().size()) > 0;
}

bool Ministry::has_project_set_to_start()
{
	return static_cast<int>(get_projects_set_to_start().size()) > 0;
}

void Ministry::disable_listener()
{
	listener->setEnabled(false);
}

void Ministry::enable_listener()
{
	listener->setEnabled(true);
}



MinistryOfTechnology::MinistryOfTechnology()
	: persons_on_breakdowns(0)
{
	projects.push_back(new TechnologicalProject("Reemplaza tu tuberia vieja", 
		"Una de las mayores causas de desperdicio de agua es a traves de tuberias rotas causando goteras. Reemplazar estas tuberias ahorraria casi un 20%% del consumo total de la casa.", 
		750, 5000, 1, 7, 100));

	projects.push_back(new TechnologicalProject("Renovacion de inodoros I", 
		"Reemplaza los inodoros convencionales que gastan de 5 galones por flush por inodoros de menor consumo que solo gastan 3.5 galones por flush.", 
		1000, 6000, 1, 7, 100));

	projects.push_back(new TechnologicalProject("Renovacion de inodoros II", 
		"Reemplaza los inodoros convencionales que gastan de 3.5 galones por flush por inodoros de bajo consumo que gastan el mínimo de 1.6 galones por flush.", 
		1250, 7000, 1, 7, 100));

	projects.push_back(new TechnologicalProject("Renovacion de duchas I", 
		"Cambia las duchas convencionales que gastan hasta 4.5 galones por minuto por duchas de bajo consumo que gastan solo 3.5 galones de agua por minuto.", 
		1500, 8000, 1, 7, 150));

	projects.push_back(new TechnologicalProject("Renovacion de duchas II", 
		"Cambia las duchas convencionales que gastan hasta 3.5 galones por minuto por duchas de bajo consumo que gastan solo el minimo de 2.5 galones de agua por minuto.", 
		1750, 9000, 1, 7, 150));

	projects.push_back(new TechnologicalProject("Instalar Sistema de reciclaje de agua", 
		"Con sistemas que reutilizan el agua usada en las cocinas, lavamanos y lavadoras, podemos ahorrar agua usandola para mantener plantas.", 
		2000, 10000, 1, 7, 150));

	projects.push_back(new TechnologicalProject("Instalar recolector de agua en el techo", 
		"Con un Sistema de recoleccion del agua de lluvia podemos obtener agua en buenas condiciones para limpiar y regar las plantas.", 
		2225, 11000, 1, 7, 175));

	projects.push_back(new TechnologicalProject("Instalar cisterna", 
		"La instalacion de una cisterna en las casas ayuda a la recoleccion del agua sobrante para uso en emergencias.", 
		2500, 12000, 1, 7, 175));	
}

Ministry* MinistryOfTechnology::create(const char* pszFileName, const char* projectsFileName)
{
	Ministry* ministry = new MinistryOfTechnology;
	if (ministry && ministry->init(pszFileName, projectsFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void MinistryOfTechnology::setup_listener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MinistryOfTechnology::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MinistryOfTechnology::on_touch_began(Touch* touch, Event* event)
{
	auto layer = (GameLayer*) (this->getParent());

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		layer->get_menu_technology()->update_projects();
		layer->get_menu_education()->setVisible(false);
		layer->get_menu_culture()->setVisible(false);
		layer->get_menu_technology()->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("button.wav");
		return true;
	}
	else
	{
		layer->get_menu_technology()->setVisible(false);
		return false;
	}
}

void MinistryOfTechnology::increase_persons_on_breakdowns()
{
	persons_on_breakdowns++;
	ResourceManager::getInstance().occupy_persons(1);
}

void MinistryOfTechnology::decrease_persons_on_breakdowns()
{
	if (persons_on_breakdowns > 0)
	{
		persons_on_breakdowns--;
		ResourceManager::getInstance().unoccupy_persons(1);
	}
}

void MinistryOfTechnology::setup_projects(const char* projectsFileName)
{
/*	std::ifstream data_file(FileUtils::getInstance()->fullPathForFilename(projectsFileName).c_str());
	if (data_file)
	{
		std::string name;
		std::string desc;
		int cash_cost;
		int water_cost;
		int persons_needed;
		int completion_time;
		int change_in_consumption;
		int num_projects;

		data_file >> num_projects;
		data_file.ignore(10, '\n');

		for (int i = 0; i < num_projects; ++i)
		{
			std::getline(data_file, name);
			std::getline(data_file, desc);
			data_file >> cash_cost;
			data_file >> water_cost;
			data_file >> persons_needed;
			data_file >> completion_time;
			data_file >> change_in_consumption;
			data_file.ignore(10, '\n');

			projects.push_back(new TechnologicalProject(name, desc, cash_cost, water_cost, persons_needed,
				completion_time, change_in_consumption));
		}
	}

	data_file.close();*/
}

void MinistryOfTechnology::animate_icon()
{
	Vector<SpriteFrame*> frames;
	Size mSize = this->getContentSize();

	frames.pushBack(SpriteFrame::create("images/technology_anim/technology.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology3.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology4.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/technology_anim/technology5.png", Rect(0, 0, mSize.width, mSize.height)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void MinistryOfTechnology::stop_animate_icon()
{
	this->stopAllActions();
}



MinistryOfEducation::MinistryOfEducation()
{
	projects.push_back(new EducationalProject("Ahorra en la ducha", 
		"No seas manoso y deja de durar 30 minutos en el bano. Si reduces tus duchas a 10 mins ahorrarias hasta 15 galones de agua al dia.", 
		1500, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Duchate, no te banes", 
		"Es decir, no llenes tu tina hasta el tope y mejor usa la ducha para bañarte. Una tina puede usar hasta 70 galones de agua en una sola lavada.", 
		1500, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Cepillate con un vaso de agua", 
		"En vez de dejar la llave corriendo cuando te estes cepillando, llena un vaso con agua y usalo para enjuagarte para no desperdiciar el agua no utilizada.", 
		1500, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Cierra la ducha mientras te enjabonas", 
		"Cuando estes tomando tus duchas recuerda cerrar la llave mientras usas el jabon. Esto no solo ayuda a que te puedas enjabonar mejor (duh), sino que ahorra mucha agua que se desperdicia por el caño.", 
		1750, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("No laves tu carro con manguera", 
		"Lavar tu carro con manguera utiliza alrededor de 150 galones de agua. Existen muchos sistemas de limpieza en seco para carros que son eficientes tanto en el ahorro de agua como en la limpieza.", 
		1750, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Lava menos frecuentemente", 
		"Lava tu ropa con menos frecuencia, pero con mayores cargas. Que conste, dijimos menos frecuencia, ¡no andes con ropa sucia!", 
		1750, 3000, 1, 7, 10));
	projects.push_back(new EducationalProject("Lava los platos utilizando envases", 
		"En vez de dejar el agua cayendo, retenla en un contenedor y reutilizala tanto como puedas.", 
		2000, 3000, 1, 7, 10));
}

Ministry* MinistryOfEducation::create(const char* pszFileName, const char* projectsFileName)
{
	Ministry* ministry = new MinistryOfEducation;
	if (ministry && ministry->init(pszFileName, projectsFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void MinistryOfEducation::setup_listener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MinistryOfEducation::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MinistryOfEducation::on_touch_began(Touch* touch, Event* event)
{
	auto layer = (GameLayer*) (this->getParent());

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		layer->get_menu_education()->update_projects();
		layer->get_menu_technology()->setVisible(false);
		layer->get_menu_culture()->setVisible(false);
		layer->get_menu_education()->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("button.wav");
		return true;
	}
	else
	{
		layer->get_menu_education()->setVisible(false);
		return false;
	}
}

void MinistryOfEducation::setup_projects(const char* projectsFileName)
{

}

void MinistryOfEducation::animate_icon()
{
	Vector<SpriteFrame*> frames;
	Size mSize = this->getContentSize();

	frames.pushBack(SpriteFrame::create("images/education_anim/education.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education3.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education4.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/education_anim/education5.png", Rect(0, 0, mSize.width, mSize.height)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void MinistryOfEducation::stop_animate_icon()
{
	this->stopAllActions();
}



MinistryOfCulture::MinistryOfCulture()
{
	projects.push_back(new CulturalProject("Parque Acuatico", 
		"Disfruta con toda tu familia de un hermoso dia lleno de diversiones!", 0, 3500, 1, 7, 2));
}

Ministry* MinistryOfCulture::create(const char* pszFileName, const char* projectsFileName)
{
	Ministry* ministry = new MinistryOfCulture;
	if (ministry && ministry->init(pszFileName, projectsFileName))
	{
		ministry->autorelease();
		return ministry;
	}
	CC_SAFE_DELETE(ministry);
	return ministry = nullptr;
}

void MinistryOfCulture::setup_listener()
{
	listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(MinistryOfCulture::on_touch_began, this);
	listener->onTouchMoved = [] (Touch* touch, Event* event) {};
	listener->onTouchEnded = [] (Touch* touch, Event* event) {};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MinistryOfCulture::on_touch_began(Touch* touch, Event* event)
{
	auto layer = (GameLayer*) (this->getParent());

	if (this->getBoundingBox().containsPoint(touch->getLocation()))
	{
		layer->get_menu_culture()->update_projects();
		layer->get_menu_technology()->setVisible(false);
		layer->get_menu_education()->setVisible(false);
		layer->get_menu_culture()->setVisible(true);
		SimpleAudioEngine::getInstance()->playEffect("button.wav");
		return true;
	}
	else
	{
		layer->get_menu_culture()->setVisible(false);
		return false;
	}
}

void MinistryOfCulture::stop_project()
{
	auto p = get_projects_running();

	for (int i = 0; i < static_cast<int>(p.size()); ++i)
	{
		p[i]->stop_project();
		p[i]->empty_persons_assigned();
		p[i]->set_to_start(false);
		stop_animate_icon();
	}
}

void MinistryOfCulture::setup_projects(const char* projectsFileName)
{

}

void MinistryOfCulture::animate_icon()
{
	Vector<SpriteFrame*> frames;
	Size mSize = this->getContentSize();

	frames.pushBack(SpriteFrame::create("images/park_anim/park.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park3.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park2.png", Rect(0, 0, mSize.width, mSize.height)));
	frames.pushBack(SpriteFrame::create("images/park_anim/park.png", Rect(0, 0, mSize.width, mSize.height)));

	auto animation = Animation::createWithSpriteFrames(frames, 0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));
}

void MinistryOfCulture::stop_animate_icon()
{
	this->stopAllActions();
}
