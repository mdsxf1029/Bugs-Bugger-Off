/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h" 
#include "SimpleAudioEngine.h"  
#include <ChooseElement.h>
#include <Map/SettingScene.h>
#include "Map/MiniMap.h"
#include <ui/UITextField.h>


USING_NS_CC;
// ����ǳ�

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// ��ӡ���õĴ�����Ϣ�����������ļ�������ʱ�����δ���  
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    // 1. super init first  
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////  
    // 2. ���һ������ "X" ͼ��Ĳ˵������������˳�����  
    //    �����������޸ġ�  

    // �رհ�ť  
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' �� 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // �����˵�������һ�� autorelease ����  
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. �ڴ˴���Ӹ������...  

    // ��ʼ����  
    Sprite* startSpriteNormal = Sprite::create("play-up.png");
    Sprite* startSpriteSelected = Sprite::create("play-down.png");

    if (startSpriteNormal == nullptr || startSpriteSelected == nullptr)
    {
        problemLoading("'play-up.png' �� 'play-down.png'");
    }
    else
    {
        auto startMenuItem = MenuItemSprite::create(startSpriteNormal, startSpriteSelected, CC_CALLBACK_1(HelloWorld::menuItem1Callback1, this));
        float x = origin.x + visibleSize.width - startMenuItem->getContentSize().width / 2 - 100;           // ����λ���Ա�����رհ�ť�ص�  
        float y = origin.y + startMenuItem->getContentSize().height / 2 + 50;
        startMenuItem->setPosition(Vec2(x, y));
        Menu* mu = Menu::create(startMenuItem, NULL);
        mu->setPosition(Vec2::ZERO);
        this->addChild(mu);
    }

    // �ȹ����ı���  
    auto label = Label::createWithTTF("Save the Princess", "fonts/Marker Felt.ttf", 36);                    // �����С����Ϊ����Χ  
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // ����ǩ��������Ļ��������  
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));
        // ��ӱ�ǩΪ�ӽڵ�  
        this->addChild(label, 1);
    }

    // �ȹ���ͼƬ  
    auto sprite = Sprite::create("SavePrincess.png");
    if (sprite == nullptr)
    {
        problemLoading("'SavePrincess.png'");
    }
    else
    {
        // ������������Ļ������ƫ�Ϸ�  
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x - 20, visibleSize.height / 2 + origin.y + 100));
        // ��Ӿ���Ϊ�ӽڵ�  
        this->addChild(sprite, 0);
    }

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // �ر� cocos2d-x ��Ϸ�������˳�Ӧ�ó���  
    Director::getInstance()->end();

    /* �����Ҫ�ڲ��˳�Ӧ�ó��������£�������ԭ�� iOS ��Ļ��������ڣ����벻Ҫʹ������� Director::getInstance()->end()�����Ǵ����� RootViewController.mm �д������Զ����¼���������ʾ */

    // EventCustom customEndEvent("game_scene_close_event");  
    // _eventDispatcher->dispatchEvent(&customEndEvent);  
}

// ��ʼ������ play �����Ӧ  
void HelloWorld::menuItem1Callback1(Ref* pSender)
{
    MenuItem* item = dynamic_cast<MenuItem*>(pSender);
    if (item)
    {
        log("Touch Help Menu Item %p", item);

        // �ڵ�� Play �󵯳��ǳ����뵯��
        auto ChooseElementLayer = ChooseElementLayer::create();

        Director::getInstance()->getRunningScene()->addChild(ChooseElementLayer);  // ��ӵ����㳡��         
    }
}
