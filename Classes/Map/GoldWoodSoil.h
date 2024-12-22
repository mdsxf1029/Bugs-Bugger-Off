// SoilWaterGold.h  
#ifndef __SOIL_WATER_GOLD_H__  
#define __SOIL_WATER_GOLD_H__  

#include "cocos2d.h"  
#include "BackgroundManager.h"  

class Setting3 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                                                       // ��������
	virtual bool init();																						// ��ʼ��
	CREATE_FUNC(Setting3);																					    // ��������

private:
	BackgroundManager* _backgroundManager;																		// ����������
	void onMouseScroll(cocos2d::Event* event);																	// �������¼�
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);							// �˵���ص�����
	void disableBigMapScrolling();																				// ���ô��ͼ����
    // ȷ�������к�������  
    cocos2d::MenuItemLabel* createTextButton(const std::string& text,
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __SOIL_WATER_GOLD_H__#pragma once
