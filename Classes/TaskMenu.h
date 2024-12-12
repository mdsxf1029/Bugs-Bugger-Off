#pragma once
#ifndef _TASK_MENU_
#define _TASK_MENU_

#include "cocos2d.h"
USING_NS_CC;

class TaskMenu :public cocos2d::Layer
{
public:
	CREATE_FUNC(TaskMenu);  // �Զ����ɾ�̬ create ����

	virtual bool init();


private:
	std::vector<std::string> taskNames = {
		"pick wood", "pick apple", "pick mushroom", "go fishing", "dance",
		"lying", "building", "cleaning", "making", "save princess"
	};

	void createTaskMenu();
	void showTaskDetails(const std::string& taskDetails);
};

#endif _TASK_MENU_