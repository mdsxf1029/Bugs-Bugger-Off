#pragma once
#ifndef InteractionManager_H
#define InteractionManager_H


#include <vector>
#include "Interaction.h"
#include "cocos2d.h"

class InteractionManager {
private:
	vector<std::shared_ptr<Interactable>> interactable;  // // �洢���пɽ����Ķ���

public:
	void AddInteractable(shared_ptr<Interactable> interactable)
	{
		interactables.push_back(interactable);
	}
};

#endif // InteractionManager_H