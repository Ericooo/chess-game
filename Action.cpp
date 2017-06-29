#include "Action.h"

Action::Action()
{}

Action::Action(U64 position_, U64 target_, float valeur_)
	:position(position_), target(target_), valeur(valeur_)
{}

Action::~Action()
{}

U64 Action::getPosition()
{
	return position;
}

U64 Action::getTarget()
{
	return target;
}

float Action::getValeur()
{
	return valeur;
}

void Action::setValeur(float x_)
{
	valeur = x_;
}