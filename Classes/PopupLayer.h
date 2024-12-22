#ifndef __POPUP_LAYER_H__
#define __POPUP_LAYER_H__

#include "cocos2d.h"

class PopupLayer : public cocos2d::LayerColor {
public:
    PopupLayer();
    ~PopupLayer();
    static PopupLayer* create(const std::string& message);              // ��������
	bool init(const std::string& message);  					        // ��ʼ������   
private:
	cocos2d::Label* _messageLabel;									    // ��Ϣ��ǩ
};

#endif // __POPUP_LAYER_H__
#pragma once
