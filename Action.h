#pragma once
#include "Piece.h"
#include "Echiquier.h"
class Action
{
protected:
	U64 position;
	U64 target;
	float valeur;
public:
	Action(U64 position, U64 target, float valeur);
	Action();
	~Action();
	U64 getTarget();
	U64 getPosition();
	float getValeur();
	void setValeur(float);
};

