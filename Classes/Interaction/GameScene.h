#pragma once
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include <functional>
#include "sets\tasks.h"



struct NPCData {
    cocos2d::Sprite* npcSprite;
    std::string npcFunction;  // "chat" �� "quest"
    std::shared_ptr<Task> ppp;
    int index;
    std::string targetScene;  // Ŀ�곡������NPC��������ת�ĳ�����

    NPCData(cocos2d::Sprite* sprite, const std::string& function, std::shared_ptr<Task> ppp, int index,const std::string& target)
        : npcSprite(sprite), npcFunction(function), ppp(ppp),index(index),targetScene(target) {}
};



class GameScene : public cocos2d::Scene
{
public:
    GameScene();
    virtual ~GameScene();

    static cocos2d::Scene* createScene();
    virtual bool init();                      // ��ʼ������
    void update(float delta) override;        // �����߼�
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onMouseUp(cocos2d::Event* event);

    CREATE_FUNC(GameScene);

private:
    cocos2d::TMXTiledMap* _tileMap;           // TMX ��ͼ
                   // ��ҽ�ɫ
    cocos2d::Sprite* _currentDialogueBox; 
    cocos2d::Sprite* _currentChoiceBox;    // ��ǰ��ʾ�ĶԻ���
    std::vector<NPCData> _npcList; // NPC �б�

    // ��ǰ��������
        struct Quest {
        std::string title;
        std::string description;
        int reward;
        bool isCompleted;
    } _currentQuest;
    int _playerGold = 0;

    void displayTaskOptions(NPCData& npcData); // ��ʾ����ѡ�񵯴�
    void displayTaskPro(NPCData& npcData); // �ᷢ����ת
    void displayTaskStatus(NPCData& npcData);  // ��ʾ����״̬����
    void displayRewardOptions(NPCData& npcData); // ��ʾ������ȡ����
    void handleQuestAcceptance(NPCData& npcData); // �����������
    void handleQuestCompletion(NPCData& npcData); // ����������ɽ���

    const float playerSpeed = 100.0f;         // ����ƶ��ٶ�

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
    cocos2d::Scene* getSceneByName(const std::string& sceneName);
};

#endif // __GAME_SCENE_H__
