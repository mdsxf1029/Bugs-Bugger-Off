#include <locale>
#include <codecvt>
#include "ui/CocosGUI.h"
#include "ChooseElement.h"
#include "Sets/manager.h"
#include "Map/MiniMap.h"
#include "NicknameLayer.h"

std::shared_ptr<Player> player2 = GlobalManager::getInstance().getPlayer();

bool ChooseElementLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bg = LayerColor::create(Color4B::WHITE, 2000, 1000);
	bg->setPosition(Vec2(0, 0));                                                                    // ������λ��
	this->addChild(bg);
	createChooseUI();

	return true;
}

ChooseElementLayer* ChooseElementLayer::create() {
    ChooseElementLayer* ret = new ChooseElementLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

void ChooseElementLayer::createChooseUI()
{
    // ��ʾ���ѡ��Ԫ��
    auto instructionLabel = Label::createWithSystemFont("Please Choose One", "fonts/arial", 36);
    instructionLabel->setPosition(Vec2(1000, 700));                                                 // ����ƫ�ϵ�λ��
    instructionLabel->setColor(Color3B::BLACK);
    this->addChild(instructionLabel);

    // �������Ԫ�ص����ơ�ͼƬ�ļ��Ͷ�Ӧ�� ElementType
    std::vector<std::tuple<std::string, std::string, ElementType>> elements = {
        {"GOLD", "GOLD1.png", ElementType::Gold},
        {"WOOD", "WOOD1.png", ElementType::Wood},
        {"WATER", "WATER1.png", ElementType::Water},
        {"FIRE", "FIRE.png", ElementType::Fire},
        {"EARTH", "EARTH.png", ElementType::Earth}
    };

    // ����ÿ����ť��λ��
    float startX = 500;
    float startY = 400;
    float spacing = 300;                                                                            // ��ť֮��ļ��

    // ͼƬ�Ͱ�ť�Ĵ�С
    float buttonSize = 120.0f;                                                                      // ��ť�Ĵ�С
    float imageSize = 400.0f;                                                                       // ͼƬ�Ĵ�С

    for (size_t i = 0; i < elements.size(); ++i)
    {
        // ������ť
        auto button = ui::Button::create("UI/X.png", "UI/X.png");
        button->setPosition(Vec2(startX + i * spacing, startY+75));
        button->setContentSize(Size(buttonSize, buttonSize));                                       // ���ð�ť��С


        // ��������ͼ��
        auto sprite = Sprite::create(std::get<1>(elements[i]));
        sprite->setPosition(Vec2(startX + i * spacing, startY - 150));                                  // ͼƬ��΢��һЩ
        sprite->setContentSize(Size(imageSize, imageSize));                                             // ����ͼƬ��С


        // ������ǩ
        auto elementLabel = Label::createWithSystemFont(std::get<0>(elements[i]), "Arial", 24);
        elementLabel->setPosition(Vec2(startX + i * spacing, startY + 150));                            // ��ǩ�ڰ�ť�Ϸ�
        elementLabel->setColor(Color3B::BLACK);

        // ��ť����¼�
        button->addClickEventListener([this, i, elements](Ref* sender) {
            // ����ѡ���Ԫ��
            player2->setPlayerElement(std::get<2>(elements[i]));                                        // ������ҵ�Ԫ������

            // ������������
            std::string imageName = std::get<1>(elements[i]);                                           // ��ȡ��Ӧ��Ԫ��ͼƬ
            player2->setCharacterImage(imageName);                                                      // ���������������������������
            // �л�����
            auto nicknameLayer = NicknameLayer::create();
            Director::getInstance()->getRunningScene()->addChild(nicknameLayer);                        // ��ӵ����㳡��
            });

        // ����ť��ͼ��ͱ�ǩ��ӵ�������
		this->addChild(button);                                                                         // ��Ӱ�ť
		this->addChild(sprite);     													                // ���ͼƬ                
		this->addChild(elementLabel);       									                        // ��ӱ�ǩ                      

        // Close the popup (remove this layer)
        this->removeFromParentAndCleanup(true);  // This will remove the layer from parent and clean up
    }
}
