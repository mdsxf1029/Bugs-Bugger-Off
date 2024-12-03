#pragma once

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <string.h>

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

class Item {
public:

	Item()noexcept :inBag(false), num(0) {};//���캯�� Ĭ�ϲ��ڱ�����,����Ϊ0
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
	virtual std::string getName() const { return "Item"; }
protected:

	bool inBag;//�Ƿ��ڱ�����
	bool isEquiped;//�Ƿ�װ��
	int num;//����

private:

};

//������
class Weapon : public Item {
public:
	Weapon() :name("Weapon"), attack(0), level(0), isEquiped(false) {};
	Weapon(const std::string& name) :name(name), attack(SIDE_ATTACK), level(0), isEquiped(false) {};
	~Weapon() {};

	void equip() override;//װ��
	void unequip() override;//ж��
	void upgrade() override;//����

	std::string getName() const { return "Weapon"; };//�õ�����

protected:


private:
	std::string name;
	int attack;
	int level;
	bool isEquiped;

};

//������
class Armor : public Item {
public:
	Armor(const std::string& name) :name(name), protect(SIDE_PROTECT), level(0), isEquiped(false) {};
	~Armor() override {};

	void equip() override;//װ��
	void unequip() override;//ж��
	void upgrade() override;//����
	std::string getName() const { return "Armor"; };//�õ�����

protected:

private:

	std::string name;//����
	int protect;//������
	int level;//�ȼ�
	bool isEquiped;//�Ƿ�װ��
};

//ʳƷ��
class Food : public Item {
public:
	Food(const std::string& name) :name(name), healHp(0), num(0), isEquiped(false), isCooked(false), isEaten(false) {};
	~Food() override {};
	void cook();//���
	void eat();//ʳ��
	std::string getName() const { return "Food"; };//�õ�����

protected:

private:
	std::string name;//����
	int healHp;//�ظ���Ѫ��
	bool isEquiped;//�Ƿ�װ��
	bool isCooked;//�Ƿ����
	bool isEaten;//�Ƿ�Թ�
	int num;//����

};



//������ �� ��ʯͷ��
class Material : public Item {
public:
	Material(const std::string& name) :name(name), is_used(false), num(0) {};
	~Material() override {};
	void use();//ʹ��
	std::string getName() const { return "Material"; };//�õ�����

protected:

private:
	std::string name;//����
	bool is_used;//�Ƿ�ʹ��
	int num;//����
};

//������Ʒ��
class TaskItem : public Item {
public:
	TaskItem(const std::string& name) :name(name) {};
	~TaskItem() {};
	void Finish();//���
	std::string getName() const { return "TaskItem"; };//�õ�����

protected:

private:
	std::string name;//���� 
	bool isFinished;//�Ƿ����
};





#endif
