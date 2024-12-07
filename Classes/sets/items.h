#pragma once

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <string.h>
#include "cocos2d.h" // ���� Cocos2d-x �����л�����ʩ
#include "math/Vec2.h" // ֱ�Ӱ��� Vec2 �Ķ���

USING_NS_CC;
//����
//���� 

const std::string  MAGIC_RING = "MAGIC_RING";//      ħ����ָ - Magic Ring
const std::string MAGIC_CRYSTAL = "MAGIC_CRYSTAL";// ħ��ˮ�� - Magic Crystal
const std::string MAGIC_SCROLL = "MAGIC_SCROLL";//   ħ������ - Magic Scroll

//����
const std::string HELMET = "HELMET";//ͷ��
const std::string ARMOR = "ARMOR";//����
const std::string SHOES = "SHOES";//Ь��

//ʳƷ������
const std::string FISH = "FISH";//��
const std::string FRUIT = "FRUIT";//ˮ��
const std::string VEGETABLE = "VEGETABLE";//�߲�
const std::string HERB = "HERB";//��ҩ
const std::string MEAT = "MEAT";//��
const std::string MUSHROOM = "MUSHROOM";//Ģ��
const std::string TREE = "TREE";//��
const std::string STONE = "STONE";//ʯͷ

//������Ʒ
const std::string KEY = "KEY";//Կ�� 
const std::string LETTER = "LETTER";//�ż�  ������һ�����ŵ�������Ʒ


//��ֵ
constexpr int SIDE_ATTACK = 10;//��ʼ�������� SIDEָ�������ܷ���
constexpr int SIDE_PROTECT = 5;//��ʼ��������
constexpr int SIDE_UPGRADE_ATTACK = 5;//�������ӵĹ�����
constexpr int SIDE_UPGRADE_PROTECT = 5;//�������ӵķ�����

class Item : public Sprite {
public:

	Item()noexcept :inBag(false), isEquiped(false), num(0), id(0) {};//���캯�� Ĭ�ϲ��ڱ�����,����Ϊ0
	virtual ~Item() {};//����������

	//������ڱ�����
	virtual void pick();//ʰȡ
	virtual void drop(); //����
	//����ڱ�����
	virtual	void equip();//װ��
	virtual void unequip();//ж��
	virtual void upgrade();//����

	virtual void discard();//����
	virtual void cook();//���
	virtual void eat();//ʳ��
	virtual void use();//ʹ��
	int getNum() { return num; };//�õ�����
	void setNum(int n) { num = n; };//��������
	//auto getTppe() { return type; };//�õ�����
	virtual const std::string& getItemName() const { return "Item"; }

	virtual void setPosition(Vec2& position)
	{
		this->position = position;
	};//����λ��

	virtual const Vec2& getPosition() const
	{
		return position;
	}

protected:
	int id;
	bool inBag;//�Ƿ��ڱ�����
	bool isEquiped;//�Ƿ�װ��
	int num;//����
	Vec2 position;//λ��
private:

};

//������
class Weapon : public Item {
public:
	Weapon() :name("Weapon"), attack(0), level(0), isEquiped(false), id(0) {};
	Weapon(const std::string& name) :name(name), attack(SIDE_ATTACK), level(0), isEquiped(false), id(0) {};
	~Weapon() {};

	void equip() override;//װ��
	void unequip() override;//ж��
	void upgrade() override;//����

	const std::string& getItemName() const override { return "Weapon"; }

protected:


private:
	int id;
	std::string name;
	int attack;
	int level;
	bool isEquiped;

};

//������
class Armor : public Item {
public:
	Armor(const std::string& name) :name(name), protect(SIDE_PROTECT), level(0), isEquiped(false), id(0) {};
	~Armor() override {};

	void equip() override;//װ��
	void unequip() override;//ж��
	void upgrade() override;//����
	const std::string& getItemName() const override { return "Armor"; };//�õ�����

protected:

private:
	int id;
	std::string name;//����
	int protect;//������
	int level;//�ȼ�
	bool isEquiped;//�Ƿ�װ��
};

//ʳƷ��
class Food : public Item {
public:
	Food(const std::string& name) :name(name), healHp(0), num(0), isEquiped(false), isCooked(false), isEaten(false), id(0) {};
	~Food() override {};
	void cook();//���
	void eat();//ʳ��
	const std::string& getItemName() const { return "Food"; };//�õ�����

protected:

private:
	std::string name;//����
	int healHp;//�ظ���Ѫ��
	bool isEquiped;//�Ƿ�װ��
	bool isCooked;//�Ƿ����
	bool isEaten;//�Ƿ�Թ�
	int num;//����
	int id;
};



//������ �� ��ʯͷ��
class GameMaterial : public Item {
public:
	GameMaterial(const std::string& name) :name(name), is_used(false), num(0), id(0) {};
	~GameMaterial() override {};
	void use();//ʹ��
	const std::string& getItemName() const { return "GameMaterial"; };//�õ�����

protected:

private:
	std::string name;//����
	bool is_used;//�Ƿ�ʹ��
	int num;//����
	int id;
};

//������Ʒ��
class TaskItem : public Item {
public:
	TaskItem(const std::string& name) :name(name), id(0), isFinished(false) {};
	~TaskItem() {};
	void Finish();//���
	const std::string& getItemName() const { return "TaskItem"; };//�õ�����

protected:

private:
	std::string name;//���� 
	bool isFinished;//�Ƿ����
	int id;
};


#endif
