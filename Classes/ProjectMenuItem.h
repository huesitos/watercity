#ifndef __PROJECT_MENU_ITEM_H__
#define __PROJECT_MENU_ITEM_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Ministry.h"

USING_NS_CC;


class ProjectMenuItem : public Sprite
{
public:
	ProjectMenuItem() {}
	virtual ~ProjectMenuItem() {}

	static ProjectMenuItem* create(const char* pszFileName, Ministry* ministry)
	{
		ProjectMenuItem* pmi = new ProjectMenuItem;
		if (pmi && pmi->initWithFile(pszFileName))
		{
			pmi->autorelease();
			pmi->setup(ministry);
			return pmi;
		}
		CC_SAFE_DELETE(pmi);
		return pmi = nullptr;
	}

	void 		update_projects();
	void 		update_labels();

	bool 		is_filled() { return filled; }
	void 		set_filled(bool filled) { this->filled = filled; }

private:
	void setup(Ministry* ministry);

	Ministry* ministry;

	bool 		filled;

	Vector<Sprite*> 	project_images;

	ui::Button* 	fund_project;

	Label* 			persons_project_label;
	Label* 			persons_work_label;

	Vector<Label*> 	name_labels;
	Vector<Label*> 	description_labels;
	Vector<Label*> 	cash_labels;
	Vector<Label*> 	water_labels;
	Vector<Label*> 	persons_labels;
	Vector<Label*> 	time_labels;
};

#endif // __PROJECT_MENU_ITEM_H__
