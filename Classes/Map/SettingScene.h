#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"
#include "BackgroundManager.h"

class Setting : public cocos2d::Scene
{
public:
    // ��������
    static cocos2d::Scene* createScene();
    // ��ʼ������
    virtual bool init();
    // ����С��ͼ�Ŵ���С�Ļص�����
    void onMouseScroll(cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Setting);

private:
    BackgroundManager* _backgroundManager; // ��������ʵ��

    // ���ð�ť�Ļص�����
    void menuItemCallback1(Ref* sender, const std::string& backgroundImage);
    //
    cocos2d::MenuItemLabel* Setting::createTextButton(const std::string& text, const std::string& fontFile, int fontSize, const std::string& backgroundImage);


};
#endif // __HELLOWORLD_SCENE_H__