#pragma once
#ifndef NPC_H
#define NPC_H

#include <string>
#include <string.h>


const string PRINCESS = "PRINCESS";//����
const string KING = "KING";//����
const string MINISTER = "MINISTER";//��

const stirng HIGH_LEVEL_MONSTER = "HIGH_LEVEL_MONSTER";
const stirng LOW_LEVEL_MONSTER = "LOW_LEVEL_MONSTER";

class NPC
{
public:
	NPC(const string& name) :name{ name } {};
	virtual ~NPC() {};

protected:

private:
	string name;

};

#endif