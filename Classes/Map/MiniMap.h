#ifndef __MINI_MAP_H__
#define __MINI_MAP_H__

#include "cocos2d.h"
#include <string>

// ��ͼ��
/* ����ʾ����
	auto miniMapScene = MiniMap::createWithMap("gold1.tmx", true);
	cocos2d::Director::getInstance()->replaceScene(miniMapScene);
*/
class MiniMap : public cocos2d::Scene
{
public:
	// ���캯��
	MiniMap(const std::string& mapFile = "village.tmx", bool fly = true) :mapName(mapFile), isFly(fly), tiledMap(nullptr), player(nullptr), keyboardListener(nullptr) {}
	MiniMap(const std::string& map, bool fly);

	// ��������
	static cocos2d::Scene* createWithMap(const std::string&mapName,bool fly);

	// ���ó�ʼ��
	bool initWithMap(const std::string&mapName);

	// ��������
	 ~MiniMap()
	 {
		 StopListening();
	 }

	// ���ü�����
	void StartListening();

	// �������µĻص�����
	void OnKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// �����ͷŵĻص�����
	void OnKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	// ���������
	void StopListening();
	
	// ����ȥ���ڵ�ͼ����ľˮ������ׯ
    void BoatingToMap(const std::string& objectMap);

	// ����ȥ���ڵ�ͼ����ת��ǰ���Թ�/����������Թ�/�������˳�
	void FlyToMap(const std::string& objectMap);
	
	// ��������λ��
	void UpdatePlayerPosition(const cocos2d::EventKeyboard::KeyCode keyCode);

	// �������ڵ�ͼ
	void GetNeighborMap(std::string& map1, std::string& map2);

	// ��ť�ص�����
	void ButtonCallback(Ref* sender);


private:
	std::string mapName; // ��ǰ��ͼ������
	bool isFly; // �Ƿ���
	cocos2d::TMXTiledMap* tiledMap; // ��ǰ��ͼ����Ƭ��ͼ
	cocos2d::Sprite* player; // ��Ҿ���
	cocos2d::EventListenerKeyboard* keyboardListener; // ���̼�����
};

#endif // __MINI_MAP_H__