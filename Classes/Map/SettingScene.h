// SettingScene.h  
#ifndef __SETTING_SCENE_H__  
#define __SETTING_SCENE_H__  

#include "cocos2d.h"  
#include "BackgroundManager.h" 
#include "Map/MiniMap.h"
USING_NS_CC;

class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();                                                                // ��������
	virtual bool init();																				 // ��ʼ������
	void onBigMapButtonClicked(cocos2d::Ref* sender);													 // ���ͼ��ť����¼�
	CREATE_FUNC(Setting);																				 

private:
	BackgroundManager* _backgroundManager;																 // ����������
	void onMouseScroll(cocos2d::Event* event);															 // �������¼�
	void menuItemCallback1(cocos2d::Ref* sender, const std::string& backgroundImage);				     // �˵���ص�����
	void disableBigMapScrolling();																		 // ���ô��ͼ����

	cocos2d::MenuItemLabel* createTextButton(const std::string& text,							  		 // �������ְ�ť
        const std::string& fontFile,
        int fontSize,
        const std::string& backgroundImage);
};

#endif // __SETTING_SCENE_H__