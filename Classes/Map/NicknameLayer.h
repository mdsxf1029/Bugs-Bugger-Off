#ifndef __NICKNAMELAYER_H__
#define __NICKNAMELAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class NicknameLayer : public LayerColor {
public:
    NicknameLayer();
    ~NicknameLayer();

    // 创建初始化方法
    virtual bool init();

    static NicknameLayer* create();

    // 获取输入的昵称
    std::string getNickname() const { return _textField->getString(); }
    // 添加验证字符的函数
    bool isValidCharacter(const char32_t ch);

    // 添加验证字符串合法性的函数
    bool isValidString(const std::string& str);
private:
    ui::TextField* _textField;  // 输入框
};

#endif // __NICKNAMELAYER_H__
#pragma once
