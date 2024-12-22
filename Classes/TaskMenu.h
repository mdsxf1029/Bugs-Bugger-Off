#pragma once
#ifndef _TASK_MENU_
#define _TASK_MENU_

#include "cocos2d.h"
#include "Sets/manager.h"
USING_NS_CC;

class TaskMenu :public cocos2d::Layer
{
public:
	CREATE_FUNC(TaskMenu);												// �Զ����ɾ�̬ create ���� 
	virtual bool init();												// ��ʼ������ 
private:
	
	std::vector<std::shared_ptr<Task>> tasks;							// �����б��洢 Task ����	 
	void createTaskMenu();												// ��������˵�	
	void showTaskDetails(const std::string& taskDetails);				// ��ʾ��������
};

#endif _TASK_MENU_