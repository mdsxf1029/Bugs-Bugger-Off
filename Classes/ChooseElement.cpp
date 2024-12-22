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

	auto bg = LayerColor::create(Color4B::WHITE, 2000, 1000);									    // ������ɫ
	bg->setPosition(Vec2(0, 0));                                                                    // ������λ��
	this->addChild(bg);																			    // ��ӵ�������
	createChooseUI();																			    // ����ѡ��Ԫ�ص� UI
	return true;
}

ChooseElementLayer* ChooseElementLayer::create() {
    ChooseElementLayer* ret = new ChooseElementLayer();
	if (ret && ret->init()) {                                                                       // ��ʼ���ɹ�
		ret->autorelease();                                                                         // �Զ��ͷ�
		return ret;                                                                                 // ����ʵ��
    }
    else {
		delete ret;		    																		// ɾ��ʵ��
		return nullptr;																			    // ���ؿ�ָ��
    }
}

void ChooseElementLayer::createChooseUI()
{
    /*��ʾ���ѡ��Ԫ��*/ 
	auto instructionLabel = Label::createWithSystemFont("Please Choose One", "fonts/arial", 36);    // ����һ�� Label ����ʾ���ѡ��Ԫ��
    instructionLabel->setPosition(Vec2(1000, 700));                                                 // ����ƫ�ϵ�λ��
	instructionLabel->setColor(Color3B::BLACK);													    // ������ɫ
	this->addChild(instructionLabel);															    // ��ӵ�������

    /*�������Ԫ�ص����ơ�ͼƬ�ļ��Ͷ�Ӧ�� ElementType*/ 
    std::vector<std::tuple<std::string, std::string, ElementType>> elements = {
		{"GOLD", "GOLD1.png", ElementType::Gold},                                                   // Ԫ�����ơ�ͼƬ�ļ���ElementType
        {"WOOD", "WOOD1.png", ElementType::Wood},
        {"WATER", "WATER1.png", ElementType::Water},
        {"FIRE", "FIRE.png", ElementType::Fire},
        {"EARTH", "EARTH.png", ElementType::Earth}
    };

    /*����ÿ����ť��λ��*/ 
    float startX = 500;                                                                             //��ʼλ��x    
	float startY = 400;																			    //��ʼλ��y
    float spacing = 300;                                                                            // ��ť֮��ļ��

    /* ͼƬ�Ͱ�ť�Ĵ�С*/
    float buttonSize = 120.0f;                                                                      // ��ť�Ĵ�С
    float imageSize = 400.0f;                                                                       // ͼƬ�Ĵ�С

    for (size_t i = 0; i < elements.size(); ++i)
    {
        /*������ť*/ 
		auto button = ui::Button::create("UI/X.png", "UI/X.png");									// ������ť
		button->setPosition(Vec2(startX + i * spacing, startY + 75));								// ���ð�ťλ��
        button->setContentSize(Size(buttonSize, buttonSize));                                       // ���ð�ť��С

        /*��������ͼ��*/ 
		auto sprite = Sprite::create(std::get<1>(elements[i]));									    // ����ͼƬ
        sprite->setPosition(Vec2(startX + i * spacing, startY - 150));                              // ͼƬ��΢��һЩ
        sprite->setContentSize(Size(imageSize, imageSize));                                         // ����ͼƬ��С


        /*������ǩ*/ 
		auto elementLabel = Label::createWithSystemFont(std::get<0>(elements[i]), "Arial", 24);	    // ������ǩ
        elementLabel->setPosition(Vec2(startX + i * spacing, startY + 150));                        // ��ǩ�ڰ�ť�Ϸ�
		elementLabel->setColor(Color3B::BLACK);													    // ������ɫ

        /*��ť����¼�*/ 
        button->addClickEventListener([this, i, elements](Ref* sender) {
            player2->setPlayerElement(std::get<2>(elements[i]));                                    // ������ҵ�Ԫ������
            /*������������*/ 
            std::string imageName = std::get<1>(elements[i]);                                       // ��ȡ��Ӧ��Ԫ��ͼƬ
            player2->setCharacterImage(imageName);                                                  // ���������������������������
            /*�л�����*/ 
			auto nicknameLayer = NicknameLayer::create();											// �����ǳƲ�
            Director::getInstance()->getRunningScene()->addChild(nicknameLayer);                    // ��ӵ����㳡��
            });

        /*����ť��ͼ��ͱ�ǩ��ӵ�������*/ 
		this->addChild(button);                                                                     // ��Ӱ�ť
		this->addChild(sprite);     													            // ���ͼƬ                
		this->addChild(elementLabel);       									                    // ��ӱ�ǩ                      

        // Close the popup (remove this layer)
        this->removeFromParentAndCleanup(true);  // This will remove the layer from parent and clean up 
    }
}
