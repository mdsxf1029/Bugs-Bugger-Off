#pragma once
#ifndef INTERACTION_H
#define INTERACTION_H

#include <string>
#include <memory>
using namespace std;

// ���󽻻���
class Interactable 
{
public:
    virtual ~Interactable() = default;        // ����������
    virtual void Interact() = 0;              // ���彻���ӿ�
    virtual bool IsInteractable() const = 0;  // �ж��Ƿ���Խ���
    virtual string GetType() const = 0;       // ��ȡ����
    virtual string GetName() const = 0;       // ��ȡ��������
};

#endif // INTERACTION_H