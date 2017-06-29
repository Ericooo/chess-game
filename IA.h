#pragma once
#include "Joueur.h"


class IA :
	public Joueur
{
protected:
	int meilleurCandidat;
public:
	IA();
	~IA();

	// A encapsuler dans différentes classes filles IA
	std::array<int, 2> random(Echiquier*, Couleur);
	std::array<int, 2> minMax(Echiquier*, Couleur);
	
	// fonctions qui calculent heuristiquement une valeur de position
	int evaluation(Echiquier*, Couleur);
	int numberTypeColor(Echiquier*, Type, Couleur);

	//fonction qui determine le meilleur candidat de l'ensemble de move attribut possibleMove selon le critere evaluation (retourne l'indice du meilleur dans l'array possibleMove)
	int minMax_best_value(Echiquier* e, Couleur c,int depth);
	std::array<int, 2> playerTurn(Echiquier*, Couleur);
};

