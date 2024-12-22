#include "PopupLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
//��������
PopupLayer::PopupLayer() : _messageLabel(nullptr) {
}

PopupLayer::~PopupLayer() {
}

bool PopupLayer::init(const std::string& message) {
    if (!LayerColor::init()) {
        return false;
    }

                                                                                                                // ���ñ�����ɫ��͸����
    this->setColor(Color3B(0, 0, 255));                                                                         // ������ɫΪ��ɫ
    this->setOpacity(255);                                                                                      // ����͸����
    this->setContentSize(Size(400, 222));                                                                       // ���õ����Ĵ�С
    this->setPosition(Vec2(600, 444));                                                                          // ���õ�����λ�ã�������Ҫ������
                                                                                                                // ������Ϣ��ǩ��ʹ���Զ�������
    _messageLabel = Label::createWithTTF(message, "fonts/Arial.ttf",30);                                        // ���������С
                                                                                                                // ��ȡ��Ļ����
    _messageLabel->setPosition(Vec2(200, 111));

    _messageLabel->setTextColor(Color4B::YELLOW);                                                               // ����������ɫ
    _messageLabel->setOpacity(255);                                                                             // ����͸����
    this->addChild(_messageLabel,99);
    CCLOG("Showing popup with message: ZITI%s", message.c_str());                                               // ȷ��������־����ӡ����
                                                                                                                // �����رհ�ť
    auto closeButton = ui::Button::create("CloseNormal.png");
    closeButton->setPosition(Vec2(200, 0));                                                                     // ���ùرհ�ť��λ��
    closeButton->addClickEventListener([=](Ref* sender) {
        this->removeFromParent();                                                                               // �رյ���
        });
    this->addChild(closeButton);

    return true;
}

PopupLayer* PopupLayer::create(const std::string& message) {
    PopupLayer* ret = new PopupLayer();
    if (ret && ret->init(message)) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}
