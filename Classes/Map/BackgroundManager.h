#ifndef _BACKGROUND_MANAGER_H_
#define _BACKGROUND_MANAGER_H_

#include "cocos2d.h"

class BackgroundManager
{
public:
	//���캯��
	BackgroundManager(cocos2d::Scene* scene);

	void BackgroundManager::setBackground(const std::string& backgroundImage);

private:

	cocos2d::Node* _background;//��������
	cocos2d::Scene* _scene;//��ǰ��������

};

#endif