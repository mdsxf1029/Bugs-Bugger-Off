#pragma once

#define SKILLS_H

#include <string>
#include"cocos2d.h"
#include "elements.h"

//������
 //����
const std::string ELEMENT_SURGE = "ELEMENT SURGE";													//Ԫ�س��
const std::string Elemental_Torrent = "Elemental Torrent";											//Ԫ�غ���
const std::string Energy_Vortex = "Energy Vortex";													//�������� 
// ǰ������
class SkillEffect;  

//���ܵĻ�����Ϣ
struct SkillInfo {
	std::string name;																				//����
	int attack;																						//������
	float degreerange;																				//�����Ƕȷ�Χ	
	float range;																					//������Χ
	std::string particleFile;																		// ��Ч�ļ�·�� 
};

class Skill {
public:

	Skill(const SkillInfo& info);
	virtual ~Skill();
	/*set*/
	void setColor(ElementType type);																// ���ü�����ɫ 
	/*get*/
	const std::string& getName() const { return _info.name; }                                       //�õ�����
	int getAttack() const { return _info.attack; }												    //�õ�������  
	SkillInfo getInfo() { return _info; }															//�õ�������Ϣ
	virtual float cast(cocos2d::Node* caster, const cocos2d::Vec2& targetPos);                      //�õ��ͷż��ܵĶ��� 
	
	bool isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos, const cocos2d::Vec2& clickPos) const; // ���Ŀ���Ƿ��ڹ�����Χ��
	bool isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos) const;								 // ���Ŀ���Ƿ��ڹ�����Χ��						
	 
	SkillInfo _info;    																            //������Ϣ                                    
	cocos2d::ParticleSystemQuad* _effect;                                                           //��Ч   

};



