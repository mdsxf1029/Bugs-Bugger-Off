#include "BackgroundManager.h"

USING_NS_CC;

BackgroundManager::BackgroundManager(cocos2d::Scene* scene) : _scene(scene)
{
    // ����Ĭ�ϱ���Ϊ��ɫ
    _background = Sprite::create("BigMap.png");
    if (_background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        _background->setAnchorPoint(Vec2(0.5f, 0.5f));
        _background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
        _scene->addChild(_background, 0, 100); // ���ñ����� tag Ϊ 100
    }
    else {
        CCLOG("Error: Failed to create default background sprite.");
    }
}

void BackgroundManager::setBackground(const std::string& backgroundImage)
{
    // ���ļ�·�������±�������
    auto newBackground = Sprite::create(backgroundImage);
    if (newBackground) {
        // �����±��������λ����ɱ���һ��
        newBackground->setAnchorPoint(Vec2(0.5f, 0.5f));
        newBackground->setPosition(_background->getPosition());

        // ���±�����ӵ��������滻�ɱ���
        _scene->addChild(newBackground, 0, 100); // ���ñ����� tag Ϊ 100
        _scene->removeChild(_background); // �Ƴ��ɱ���

        // ���±���ָ��
        _background = newBackground;
    }
    else {
        // �������ʧ�ܣ���ӡ������Ϣ
        CCLOG("Error: Failed to create sprite with image %s", backgroundImage.c_str());
    }
}
