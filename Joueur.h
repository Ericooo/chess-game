#pragma once
#include "Piece.h"
#include "Echiquier.h"
#include <array>
#include "Action.h"
#include <vector>

class Joueur
{
public:

	// fonction qui determine l'ensemble des actions légales 
	std::vector<Action> mobilite(Echiquier*, Couleur);
	Joueur();
	~Joueur();
};

