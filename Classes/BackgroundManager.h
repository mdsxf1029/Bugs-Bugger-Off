#ifndef __BACKGROUND_MANAGER_H__
#define __BACKGROUND_MANAGER_H__

#include "cocos2d.h"

class BackgroundManager {
public:
    explicit BackgroundManager(cocos2d::Node* parentNode);
    void setBackground(const std::string& backgroundImage);

private:
    cocos2d::Node* _parentNode; // ���ڴ�ű����ĸ��ڵ�
    cocos2d::Sprite* _background; // ��ǰ��������
};

#endif // __BACKGROUND_MANAGER_H__
