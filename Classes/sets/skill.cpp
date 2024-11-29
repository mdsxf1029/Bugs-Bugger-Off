#include"skills.h"

//������
Skill::Skill(std::string& name) :name(name) {};
Skill::~Skill() {};

//�ͼ�����
LowLevelSkill::LowLevelSkill(std::string& name) :Skill(name) 
{
	attack = 10;
};
LowLevelSkill::~LowLevelSkill() {};

//�м�����
MidLevelSkill::MidLevelSkill(std::string& name) :Skill(name)
{
	attack = 20;
};
MidLevelSkill::~MidLevelSkill() {};

//�߼�����
HighLevelSkill::HighLevelSkill(std::string& name) :Skill(name)
{
	attack = 30;
};
HighLevelSkill::~HighLevelSkill() {};
