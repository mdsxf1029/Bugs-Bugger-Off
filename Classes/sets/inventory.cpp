//2353924 �뿡��
//inverntory Ϊ��ҵı��� �ĺ���ʵ��

//Inventory(int size) :size(size), items(0) {};
Inventory::~Inventory() {};

//����
//չʾ����
void Inventory::showInventory()
{
	//��������
	//��ʾ�����е���Ʒ png
	//��ʾ��Ʒ�����֣������֮���ԱߵĽ��棩
	//��ʾ��Ʒ��������ͬ�ϣ�
	//��ʾ��Ʒ�����ԣ�ͬ�ϣ�  ���� Ч��֮��
	//��ʾ��Ʒ�ĵȼ���ͬ�ϣ�
	//��ʾ��Ʒ���Ƿ�װ����ͬ�ϣ� 
}
//����
//�����Ʒ
bool Inventory::addItem(Item* item)
{
	if (items.size() < size)
	{
		items.push_back(item);
		item_num++;
		return true;
	}
	else
	{
		//��������
		return false;
	}
} 

//�Ƴ���Ʒ
void Inventory::removeItem(Item* item) 
{
	for (int i=0;i<BAG_SIZE;i++)
	{
		if (items[i] == item)
		{
			items.erase(items.begin() + i);
			item_num--;
			break;
		}
	}

}

//ʹ����Ʒ
void Inventory::useItem(Item* item)
{
	//ʹ����Ʒ
	//������Ʒ�����࣬���ò�ͬ�ĺ���
	//��������������ù�������
	//����ǻ��ߣ����÷�������
	//�����ʳƷ�����ûظ�����
	//����ǲ��ϣ����úϳɺ���
	//�����������Ʒ������������
} 

//�õ���С
int Inventory::getSize() 
{}

//�Ƿ�����
bool Inventory::isFull() 
{}
