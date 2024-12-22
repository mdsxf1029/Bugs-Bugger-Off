#ifndef __NICKNAMELAYER_H__
#define __NICKNAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class NicknameLayer : public LayerColor {
public:
    NicknameLayer();
    ~NicknameLayer();
    virtual bool init();                                                            // ������ʼ������ 
	static NicknameLayer* create(); 											    // ������̬��������
	std::string getNickname() const { return _textField->getString(); }			    // ��ȡ�ǳ�
    bool isValidCharacter(const char32_t ch);                                       // �����֤�ַ��ĺ��� 
	bool isValidString(const std::string& str);									    // �����֤�ַ����ĺ���
private:
    ui::TextField* _textField;                                                      // �����
};

#endif                                                                              // __NICKNAMELAYER_H__
#pragma once
