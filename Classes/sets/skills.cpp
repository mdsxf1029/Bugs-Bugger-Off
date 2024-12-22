#include"skills.h" 
#include"BattleScene.h"
//������
class Skill;

Skill::Skill(const SkillInfo& info) :_info(info) {}                                      //���캯��
Skill::~Skill() {}      											                     //��������    

/*��ĳ����������Ч*/
float Skill::cast(cocos2d::Node* caster, const cocos2d::Vec2& targetPos) {
    if (!caster) return false;
	Vec2 _skillDirection = targetPos - caster->getPosition();                           // �������ҵ������λ�õķ�������
    _skillDirection.normalize();                                                        // ������������һ��
    float angle = std::atan2(_skillDirection.y, _skillDirection.x);                     // �������ҵ������λ�õĽǶȣ����ȣ�
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);                                // ������ת��Ϊ�Ƕ�

    return angleInDegrees;
}

/*�ж��Ƿ��ڹ�����Χ��*/
bool Skill::isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos, const cocos2d::Vec2& clickPos) const {
    float distance = casterPos.distance(targetPos);//�������
    Vec2 _skillDirection = clickPos - casterPos;                                        // �������ҵ������λ�õķ�������
    Vec2 _enemyDirection = targetPos - casterPos;										// �������ҵ����˵ķ�������

    _skillDirection.normalize();                                                        // ������������һ��
    _enemyDirection.normalize();                                                        // ������������һ��             
    /*�������ҵ������λ�õĽǶȣ����ȣ�*/ 
    float angle = std::atan2(_skillDirection.y, _skillDirection.x);                     // atan2���ص��ǻ���   ��ҵ����
    float enemyangle = std::atan2(_enemyDirection.y, _enemyDirection.x);                // atan2���ص��ǻ���   ��ҵ�����
    /*������ת��Ϊ�Ƕ�*/ 
    float angleInDegrees = CC_RADIANS_TO_DEGREES(angle);                                // ת��Ϊ�Ƕ�
    float enemyangleInDegrees = CC_RADIANS_TO_DEGREES(enemyangle);                      // ת��Ϊ�Ƕ�
   
	float degreegap = abs(angleInDegrees - enemyangleInDegrees);                        //���������ǶȲ�ֵ
	if (degreegap > 180)																//����ǶȲ�ֵ����180
		degreegap = 360 - degreegap;                                                    //����ĽǶȲ�ֵת��ΪС�ĽǶȲ�ֵ
	if (degreegap < _info.degreerange && distance <= _info.range)   		            //�ж��Ƿ��ڹ�����Χ�� 
        return true;
    else
        return false;
}
bool  Skill::isInRange(const cocos2d::Vec2& casterPos, const cocos2d::Vec2& targetPos) const  //���˹������
{
    float distance = casterPos.distance(targetPos);                                     //�������
	if (distance <= _info.range)														//�ж��Ƿ��ڹ�����Χ��
        return true;
    else
        return false;
}
void Skill::setColor(ElementType type)
{
    switch (type)
    {
        case ElementType::Gold:
            _effect->setStartColor(Color4F(1.0f, 0.84f, 0.0f, 1.0f));                   // �������Ľ�ɫ
            _effect->setEndColor(Color4F(0.85f, 0.65f, 0.13f, 0.7f));                   // ƫ���Ľ�ɫ����͸����
            _effect->setStartColorVar(Color4F(0.1f, 0.1f, 0.0f, 0.0f));                 // ��΢����ɫ�仯
            break;

        case ElementType::Wood:
            _effect->setStartColor(Color4F(0.0f, 0.8f, 0.2f, 1.0f));                    // ��Ȼ����ɫ
            _effect->setEndColor(Color4F(0.0f, 0.6f, 0.0f, 0.7f));                      // ����ɫ����͸����
			_effect->setStartColorVar(Color4F(0.0f, 0.1f, 0.1f, 0.0f));				    // ��΢����ɫ�仯
            break;

        case ElementType::Water:
            _effect->setStartColor(Color4F(0.0f, 0.5f, 1.0f, 1.0f));                    // ��������ɫ
            _effect->setEndColor(Color4F(0.0f, 0.3f, 0.8f, 0.7f));                      // ����ɫ����͸����
			_effect->setStartColorVar(Color4F(0.0f, 0.1f, 0.1f, 0.0f));                 // ��΢����ɫ�仯  
            break;

        case ElementType::Fire:
            _effect->setStartColor(Color4F(1.0f, 0.2f, 0.0f, 1.0f));                    // ƫ�ȵĺ�ɫ
            _effect->setEndColor(Color4F(1.0f, 0.0f, 0.0f, 0.7f));                      // ����ɫ����͸����
			_effect->setStartColorVar(Color4F(0.1f, 0.1f, 0.0f, 0.0f)); 			    // ��΢����ɫ�仯 
            break;

        case ElementType::Earth:
            _effect->setStartColor(Color4F(0.6f, 0.4f, 0.2f, 1.0f));                    // ����ɫ
            _effect->setEndColor(Color4F(0.4f, 0.3f, 0.1f, 0.7f));                      // ���ɫ����͸����
			_effect->setStartColorVar(Color4F(0.1f, 0.1f, 0.1f, 0.0f));                 // ��΢����ɫ�仯
            break;

        default:
            break;
    }
}