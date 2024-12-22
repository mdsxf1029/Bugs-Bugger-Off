#pragma once
#ifndef __CHOOSE_ELEMENT_H__
#define __CHOOSE_ELEMENT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class ChooseElementLayer : public Layer
{
public:
    ChooseElementLayer() {};
    ~ChooseElementLayer() {};

    // ������ʼ������
    virtual bool init();
    static ChooseElementLayer* create();
    void createChooseUI();
};

#endif // __CHOOSE_ELEMENT_H__