#pragma once

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <string.h>

//����
//���� 

const string  MAGIC_RING = "MAGIC_RING";//      ħ����ָ - Magic Ring
const string MAGIC_CRYSTAL = "MAGIC_CRYSTAL";// ħ��ˮ�� - Magic Crystal
const string MAGIC_SCROLL = "MAGIC_SCROLL";//   ħ������ - Magic Scroll

//����
const string HELMET = "HELMET";//ͷ��
const string ARMOR = "ARMOR";//����
const string SHOES = "SHOES";//Ь��
 
//ʳƷ������
const string FISH = "FISH";//��
const string FRUIT = "FRUIT";//ˮ��
const string VEGETABLE = "VEGETABLE";//�߲�
const string HERB = "HERB";//��ҩ
const string MEAT = "MEAT";//��

const string TREE = "TREE";//��
const string STONE = "STONE";//ʯͷ

//������Ʒ
const string KEY = "KEY";//Կ�� 
const string LETTER = "LETTER";//�ż�  ������һ�����ŵ�������Ʒ


//��ֵ
const int ATTACK = 10;//��ʼ��������
const int PROTECT = 5;//��ʼ��������
const int UPGRADE_ATTACK = 5;//�������ӵĹ�����
const int UPGRADE_PROTECT = 5;//�������ӵķ�����

class Item {
public: 

	Item() :in_bag(false), num(0) {};//���캯�� Ĭ�ϲ��ڱ�����,����Ϊ0
	virtual ~Item() {};//����������

	//������ڱ�����
	virtual void pick() = 0 ;//ʰȡ
	virtual void drop() = 0; //����
	//����ڱ�����
	virtual void discard() = 0;//����
	virtual void equip() = 0; //װ��
	virtual void unequip() = 0; //ж��
	virtual void upgrade() = 0; //����
	virtual void use() = 0;//ʹ��
	int getNum() { return num; } const ;//�õ�����
	void setNum(int n) { num = n; };//��������
	getTppe() { return type; };//�õ�����

protected:
	
	bool inBag;//�Ƿ��ڱ�����
	int num;//����
private: 

};

//������
class Weapon : public Item {
public:
	Weapon(const std::string& name):name(name),attack(ATTACK),level(0),is_equiped(false) {};
	~Weapon() {};
	virtual void upgrade() override ;//����
	virtual void equip() override;//װ��

protected: 

	
private:
	string name;
	int attack;
	int level;
	bool is_equiped;

};

//������
class Armor : public Item {
public:
	Armor(const std::string& name) :name(name), protect(PROTECT), level(0), is_equiped(false) {};
	virtual ~Armor() override {} ;
	virtual void upgrade() override;//����
protected:

private:

	string name;//����
	int protect;//������
	int level;//�ȼ�
	bool is_equiped;//�Ƿ�װ��
};

//ʳƷ��
class Food : public Item {
public:
	Food(const std::string& name) :name(name), healHp(0), num(0), isEquiped(false), isCooked(false), isEaten(false) {};
	virtual ~Food() override {};
	virtual void cook() = 0;//���
	virtual void eat() = 0;//�ظ�

protected:

private:
	string name;//����
	int healHp;//�ظ���Ѫ��
	bool isEquiped;//�Ƿ�װ��
	bool isCooked;//�Ƿ����
	bool isEaten;//�Ƿ�Թ�

};



//������ �� ��ʯͷ��
class Material : public Item {
public:
	Material(const std::string& name) :name(name), is_used(false), num(0) {};
	virtual ~Material() override {};
	virtual void use() = 0;//ʹ��
protected:

private:
	string name;//����
	bool is_used;//�Ƿ�ʹ��
};

//������Ʒ��
class TaskItem : public Item {
public:
	TaskItem() {};
	virtual ~TaskItem() {};
	vitrual bool isFinished() = 0;//�Ƿ����
protected:

private:
	string name;//���� 
};



//���� ����
Weapon  magicRing(MAGIC_RING);
Weapon  magicCrystal(MAGIC_CRYSTAL);
Weapon  magicScroll(MAGIC_SCROLL);

//���� ����
Armor helmet(HELMET);
Armor armor(ARMOR);
Armor shoes(SHOES);

//ʳƷ ����
Food fish(FISH);
Food fruit(FRUIT);
Food vegetable(VEGETABLE);
Food herb(HERB);
Food meat(MEAT);

//���� ����
Material tree(TREE);
Material stone(STONE);

//������Ʒ ����
TaskItem key(KEY);

#endif
