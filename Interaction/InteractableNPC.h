#pragma once
#ifndef INTERACTABLE_NPC_H
#define INTERACTABLE_NPC_H

#include "Interaction.h"

// NPC������
class InteractableNPC : public Interactable 
{
private:
    string type;
    string name;
public:
    InteractableNPC(const string& name) : name(name) {}
    void Interact() override;                // ʵ�ֽ����߼�
    bool IsInteractable() const override { return true; }
    string GetType() const override { return "NPC"; }
    string GetName() const override { return name; }
};

#endif // INTERACTABLE_NPC_H
