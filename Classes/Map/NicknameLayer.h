#ifndef __NICKNAMELAYER_H__
#define __NICKNAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class NicknameLayer : public LayerColor {
public:
    NicknameLayer();
    ~NicknameLayer();

    // ������ʼ������
    virtual bool init();

    static NicknameLayer* create();

    // ��ȡ������ǳ�
    std::string getNickname() const { return _textField->getString(); }
    // �����֤�ַ��ĺ���
    bool isValidCharacter(const char32_t ch);

    // �����֤�ַ����Ϸ��Եĺ���
    bool isValidString(const std::string& str);
private:
    ui::TextField* _textField;  // �����
};

#endif // __NICKNAMELAYER_H__
#pragma once
