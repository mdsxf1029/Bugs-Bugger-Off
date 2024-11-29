#pragma once

#ifndef SKILLS_H
#define SKILLS_H

#include <string>
//һЩ���� ����gpt
/*
Ԫ�س�� (Elemental Surge)
�������ͷ�Ԫ�ص���������Ŀ������˺���

�������� (Arcane Blast)
������ʩ��һ��ǿ��İ�����������ɷ�Χ�˺���

�������� (Energy Vortex)
�������ٻ�һ���������У����������и����ĵ��ˡ�
����֮�� (Chaos Light)
�������ͷŻ����������������Ԫ���˺���

Ԫ�غ��� (Elemental Torrent)
�������ͷ�һ��ǿ���Ԫ�غ��������Ŀ�ꡣ */
//������

//��������  ���и�
const std::string ELEMENT_SURGE = "ELEMENT SURGE";//Ԫ�س��
const std::string Elemental_Torrent = "Elemental Torrent";//Ԫ�غ���
const std::string Energy_Vortex = "Energy Vortex";//��������
//��ϼ�  �Ⱥ������ǰ��������
const std::string Arcane_Blast = "Arcane Blast";//��������


class Skill {
public:
	Skill(std::string& name);
	virtual ~Skill(); 
protected:

private:
	std::string name;//�������� 
};

class LowLevelSkill : public Skill {
public:
	LowLevelSkill(std::string& name);
	virtual ~LowLevelSkill();
private:
	int attack;//�˺�
};

class MidLevelSkill : public Skill {
public:
	MidLevelSkill(std::string& name);
	~MidLevelSkill();

private:
	int attack;//�˺�
}
class HighLevelSkill : public Skill {
public:
	HighLevelSkill(std::string& name);
	~HighLevelSkill();
private:
	int attack;//�˺�
};

LowLevelSkill elementSurge(ELEMENT_SURGE);//Ԫ�س��
MidLevelSkill elementalTorrent(Elemental_Torrent);//Ԫ�غ���
HighLevelSkill energyVortex(Energy_Vortex);//��������

HighLevelSkill arcaneBlast(Arcane_Blast);//��������

#endif
