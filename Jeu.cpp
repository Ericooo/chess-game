#include "Jeu.h"

Jeu::Jeu()
{
	echiquier = new Echiquier();
	interface_ = new Interface();
	echiquier->init();
	echiquier->setSpriteDames(interface_->getSpriteDameBlanche(),interface_->getSpriteDameNoire());
	echiquier->setSpriteSize(interface_->getSpriteSize());
	interface_->init();
	interface_->load(echiquier);
	game_step = SINGLEPLAYER;
}

Jeu::~Jeu()
{
	delete echiquier;
	delete interface_;
}

void Jeu::mainLoop()
{
	while (game_step != GAME_OVER)
	{	
		tour += 1;
		interface_->draw(echiquier);
		array<int, 2> coup;
		if (tour % 2 != 0)
		{
			std::cout << "Tour des blancs" << "\n" << tour << "\n";
			coup =  humain.playerTurn(echiquier, BLANC, interface_);
		}
		else
		{
			std::cout << "Tour des noirs" << "\n" << tour << "\n";
			if (game_step == MULTIPLAYER)
				coup = humain.playerTurn(echiquier, NOIR, interface_); //joueur humain
			
			if (game_step == SINGLEPLAYER)
			{
				//coup = MinMax.random(echiquier, NOIR); //joueur random
				//coup = MinMax.minMax(echiquier, NOIR); //joueur minMax sur 1 demi coup
				coup = MinMax.playerTurn(echiquier, NOIR);
			}
		}
		if (coup[0] == 100)
		{
			int p = 0;
			cin >> p;
			game_step = GAME_OVER;
		}
		
		echiquier->gestionDestruction();
		echiquier->actualisation_occupations_controle();
		echiquier->actualisation_pieces();
		echiquier->actualisation_occupations_controle();
		interface_->draw(echiquier);
	}
}
