
#ifndef __OVER_MAP_H__  

#include "cocos2d.h"  

class Setting6 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                           // ��������  
	virtual bool init();															// ��ʼ��
	CREATE_FUNC(Setting6);															// ��������

private:

	void onMouseScroll(cocos2d::Event* event);											// �������¼�
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);   // �˵���ص�����
	void disableBigMapScrolling();														// ���ô��ͼ����
	// ȷ�������к�������  
	cocos2d::MenuItemLabel* createTextButton(const std::string& text,
		const std::string& fontFile,
		int fontSize,
		const std::string& backgroundImage);											// �������ְ�ť
};

#endif // __SOIL_WATER_GOLD_FIRE_WOOD_H__#pragma once
#pragma once
