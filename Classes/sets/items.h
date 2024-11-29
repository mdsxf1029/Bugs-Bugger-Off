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
const string TREE = "TREE";//��
const string STONE = "STONE";//ʯͷ

const string FISH = "FISH";//��
const string FRUIT = "FRUIT";//ˮ��
const string VEGETABLE = "VEGETABLE";//�߲�
const string HERB = "HERB";//��ҩ

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
	int getNum() { return num; };//�õ�����
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
	virtual void equip() override;//ʰȡ

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
	~Armor() {};
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


protected:

private:
	string name;//����
	int healHp;//�ظ���Ѫ��
	int num;//����
	bool isEquiped;//�Ƿ�װ��
	bool isCooked;//�Ƿ����
	bool isEaten;//�Ƿ�Թ�

};



//������ �� ��ʯͷ��
class Material : public Item {
public:

protected:

private:
	string name;//����
	bool is_used;//�Ƿ�ʹ��
	int num;//��¼����
};

//������Ʒ��
class TaskItem : public Item {
public:
	TaskItem() {};
	virtual ~TaskItem() {};

protected:

private:
	string name;//���� 
	int num;//����
};


#endif
