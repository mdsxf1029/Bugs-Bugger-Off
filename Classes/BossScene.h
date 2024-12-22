#pragma once

#pragma once

#ifndef __BOSS_SCENE_H__
#define __BOSS_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include "sets/manager.h"
#include "Map/MiniMap.h"
struct bossDATA {
    cocos2d::Sprite* bossSprite;  // NPC ����
    std::string bossFunction;     // "chat" �� "quest"
    std::string targetScene;      // Ŀ�곡������NPC��������ת�ĳ�����
    std::shared_ptr<Task> ppp;																							// ����												
    int index;
    int taskid;// NPC ����	
    bossDATA() : bossSprite(nullptr), bossFunction(""), targetScene(""),index(0),ppp(nullptr) {}  // Ĭ�Ϲ��캯��

    bossDATA(cocos2d::Sprite* sprite, const std::string& function, int index, std::shared_ptr<Task> ppp, int taskid, const std::string& target)
        : bossSprite(sprite), bossFunction(function), index(index), ppp(ppp), taskid(taskid), targetScene(target) {
    }
};

class BossScene : public cocos2d::Scene
{
public:
    BossScene() ;
    virtual ~BossScene() ;

    static cocos2d::Scene* createScene();
    virtual bool init();                                                                                // ��ʼ������
    void update(float delta) override;
    bool IsColliding(cocos2d::Vec2 position);
    void displayChoice1(cocos2d::Sprite* npc, const std::string& question,
        const std::vector<std::pair<std::string, std::function<void()>>>& choices);
    void displayChoice2(cocos2d::Sprite* npc, const std::string& question,
        const std::vector<std::pair<std::string, std::function<void()>>>& choices);
    void handleChatNPC(cocos2d::Sprite* npc);

    void displayDialogue(cocos2d::Sprite* npc, const std::string& text);
    void displayTownInfo(cocos2d::Sprite* npc);
    void displayTownDetails(cocos2d::Sprite* npc);
    void displayQuestInfo(cocos2d::Sprite* npc);
    void displayQuestDetails(cocos2d::Sprite* npc);
    void displayGoodbye(cocos2d::Sprite* npc);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void displayTaskPro(bossDATA& npcData);

    cocos2d::Sprite* boss;
    cocos2d::Sprite* _currentDialogueBox;																		// ��ǰ��ʾ�ĶԻ���
    cocos2d::Sprite* _currentChoiceBox;																			// ��ǰ��ʾ�ĶԻ���
    CREATE_FUNC(BossScene);

    
private:
    cocos2d::TMXTiledMap* _tileMap;		      // ��ͼ
    std::shared_ptr<EnemyNpc> rawEnemy;  
    bossDATA Boss;
};

#endif // __BOSS_SCENE_H__
