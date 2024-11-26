#pragma once
#ifndef TRIGGER_H
#define TRIGGER_H

#include "Interaction.h"

// ��ͨ����
class BasicTrigger 
{
public:
	virtual bool CheckTrigger(const Interactable& interactable) const = 0;
};

// ���ⴥ��
class SpecialTrigger : public BasicTrigger 
{
public:
	bool CheckTrigger(const Interactable& interactable) const override;
};

#endif // TRIGGER_H
