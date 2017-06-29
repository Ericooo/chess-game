#pragma once
#include "Interface.h"
#include "Echiquier.h"
#include "IA.h"
#include "Interaction.h"
#include "Humain.h"

enum Steps  
{
	MAINMENU,      
	SINGLEPLAYER, 
	MULTIPLAYER, 
	GAME_OVER   
};

class Jeu
{
	Steps game_step;
	Echiquier *echiquier;
	Interface *interface_;

	Humain humain;
	IA MinMax;
	int result;
	int tour;
	int position;
	int target;

private:
	const Jeu &Jeu::operator=(const Echiquier &jeu);
	Jeu(const Jeu &jeu);

public:
	Jeu();
	~Jeu();

	// Cette fonction gère le tour d'un joueur selon sa couleur
	void mainLoop();
};


