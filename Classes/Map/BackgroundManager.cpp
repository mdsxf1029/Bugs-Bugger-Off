#include "BackgroundManager.h"

USING_NS_CC;

BackgroundManager::BackgroundManager(cocos2d::Node* parentNode) : _parentNode(parentNode), _background(nullptr) {
    // ������ʼ��������
	_background = Sprite::create("black.png");                                                                        // ������������
    if (_background) {
		auto visibleSize = Director::getInstance()->getVisibleSize();                                                 // ��ȡ�ɼ�����Ĵ�С
		auto origin = Director::getInstance()->getVisibleOrigin();													  // ��ȡ�ɼ������ԭ��
		_background->setAnchorPoint(Vec2(0.5f, 0.5f));																  // ����ê��
		_background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));		  // ����λ��

        // ��������ӵ�����ĸ��ڵ���
        _parentNode->addChild(_background, -1);                                                                       // ȷ������λ����ײ�
    }
    else {
		CCLOG("Error: Failed to create default background sprite.");                                                   // ���������Ϣ
    }
}

void BackgroundManager::setBackground(const std::string& backgroundImage) {
    // �����µı�������
	auto newBackground = Sprite::create(backgroundImage);                                                              // �����±�������
    if (newBackground) {                                                                                
		newBackground->setAnchorPoint(Vec2(0.5f, 0.5f));															   // ����ê��
		newBackground->setPosition(_background->getPosition());													       // ����λ��
        // �滻����
        _parentNode->addChild(newBackground, 0);                                                                       // ���±�����ӵ�ͬһ���ڵ�
        _parentNode->removeChild(_background);                                                                         // �Ƴ��ɱ���
		_background = newBackground;																				   // ���±���ָ��
    }
    else {
		CCLOG("Error: Failed to create sprite with image %s", backgroundImage.c_str());								// ���������Ϣ
    }
}
