#ifndef __PROJECT_MENU_ITEM_H__
#define __PROJECT_MENU_ITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Project.h"

USING_NS_CC;


class ProjectMenuItem : public Sprite
{
public:
	ProjectMenuItem() {}
	virtual ~ProjectMenuItem() {}

	static ProjectMenuItem* create(const char* pszFileName, Project* project)
	{
		ProjectMenuItem* pmi = new ProjectMenuItem;
		if (pmi && pmi->initWithFile(pszFileName))
		{
			pmi->autorelease();
			pmi->setup(project);
			return pmi;
		}
		CC_SAFE_DELETE(pmi);
		return pmi = nullptr;
	}

	void 		update_labels();

	bool 		is_filled() { return filled; }
	void 		set_filled(bool filled) { this->filled = filled; }

private:
	void setup(Project* project);

	Project* project;

	bool 		filled;

	Sprite* 	project_image;
	ui::Button* fill_button;
	ui::Button* empty_button;

	Label* 		name_label;
	Label* 		description_label;
	Label* 		cash_label;
	Label* 		water_label;
	Label* 		persons_label;
	Label* 		time_label;
};

#endif // __PROJECT_MENU_ITEM_H__
