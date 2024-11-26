#pragma once
#include <iostream>
#include <vector>
using namespace std;

// �����ṹ��
struct special_point
{
	int x;
	int y;
	int type; // ��������ͣ�������0������1���Թ�2������3����ҩ4��С����5
};

// ���µ�ͼ����ƣ����ֻ������࣬��ͬ��ͼΪ��ͼ��Ĳ�ͬ����
class Map
{
public:
	// �벹���С��ͼ֮���л��ĺ���

	/*��������SwitchBetweenSmallMaps
	  �������ܣ�С��ͼ֮��ê����л�
	  �����б�
		  role_coord_x��role_coord_y�����ﵱǰ�������꣬ͨ������ϵͳ��ȡ���������ͼ����ʱ��Ҫ�õ���
		  object_map����Ҫ��ת�Ķ���ͨ������ϵͳ��ȡ��������ת���ĸ���ͼȥ��
	  ����ֵ���Ƿ�ɹ���ת���ɹ���Ϊtrue
	*/
	bool SwitchBetweenSmallMaps(const int& role_coord_x, const int& role_coord_y, const int& object_map);

	/*��������PanM
	  �������ܣ���ͼչʾʱ��ƽ��
	  �����б�
		  role_coord_x��role_coord_y�����ﵱǰ�������꣬ͨ������ϵͳ��ȡ��
	  ����ֵ����
	*/
	void Pan(const int& role_coord_x, const int& role_coord_y);

	// �벹���ͼ���ź���

private:
	vector<int> before_jump_point; // ������ת֮ǰ����������
	bool fog; // �Ƿ��������������Ϊtrue
	vector<special_point> special_points; // �ṹ�����飬�洢��������꣬���ͣ�������0������1���Թ�2������3����ҩ4��С����5
};
