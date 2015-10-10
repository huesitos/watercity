#ifndef __MINISTERIO_H__
#define __MINISTERIO_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Project.h"
#include <vector>

USING_NS_CC;
using namespace ui;


class Ministerio : public Sprite
{
public:
	Ministerio();
	virtual ~Ministerio();

	static Ministerio* create(const char* file_name)
	{
		Ministerio* ministerio = new Ministerio;
		if (ministerio && ministerio->initWithFile(file_name))
		{
			ministerio->autorelease();
			ministerio->init();
			return ministerio;
		}
		CC_SAFE_DELETE(ministerio);
		return ministerio = nullptr;
	}

	const std::vector<Project>& 	get_projects() { return projects; }

protected:
	virtual bool 	init();

	virtual bool 	init_data(const char* data_file_name) { return true; }

private:
	std::vector<Project> 	projects;

	Vector<Button*> 		project_buttons;

	bool 	running_project;
};

#endif // __MINISTERIO_H__
