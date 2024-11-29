 
#include "elements.h"


// ���캯��
Element::Element(ElementType type) :element(type) {};
//

// ��ȡԪ������
static std::string Element::getElementName(ElementType type) {
	switch (type) {
		case Gold: return "Gold";   // ��
		case Wood: return "Wood";   // ľ
		case Water: return "Water"; // ˮ
		case Fire: return "Fire";   // ��
		case Earth: return "Earth"; // ��
		default: return "Unknown";
	}
}



// ��ӡԪ����Ϣ  �е㲻ȷ�� ���ܻ�������ĺ��������ͬЧ��������������ô����
void Element::printElement() const {
    std::cout << "Element: " << getElementName(type) << std::endl;
}

// �Ƚ�Ԫ�ش�С   ���������
// ��>ľ>��>ˮ>��>��
// eΪ�з�Ԫ��
bool Element::operator>(const Element& e) const {
	if (type == Gold && e.type == Wood) return true;
	else if (type == Wood && e.type == Earth) return true;
	else if (type == Earth && e.type == Water) return true;
	else if (type == Water && e.type == Fire) return true;
	else if (type == Fire && e.type == Gold) return true;
	return false;
}
