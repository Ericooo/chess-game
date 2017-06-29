#pragma once
#include "Joueur.h"
#include "Echiquier.h"
#include "Interaction.h"
#include "Interface.h"
class Humain :
	public Joueur
{
protected:
	Interaction interaction;
	int position;
	int target;
public:
	Humain();
	~Humain();
	std::array<int, 2> playerTurn(Echiquier* e, Couleur c, Interface* interface_);

	// pour le debug de la classe humain 
	std::array<int, 2> console(Echiquier* echiquier, Couleur c);
};

