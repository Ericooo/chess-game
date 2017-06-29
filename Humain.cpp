#include "Humain.h"



Humain::Humain()
{
}


Humain::~Humain()
{
}


std::array<int, 2> Humain::playerTurn(Echiquier* e, Couleur c, Interface* interface_)
{
	std::vector<Action> possibleMove = mobilite(e, c);
	std::array<int, 2> result;
	
	bool moving = false;
	bool fin = false;
	while (!fin)
	{	
		moving = interaction.sfml_interact(interface_->getRenderWindow(), 0.3*interface_->getSpriteSize());
		position = interaction.getSelectedCell(); 
		target = interaction.getTargetedCell(); 
		if (moving)
		{
			fin = e->actualiseur(position, target, c);
			if (!fin)
			{
				moving = false;
				interaction.restart();
			}
		}
	}
	interaction.restart();
	if (possibleMove.size() == 0)
	{
		result[0] = 100;
		result[1] = 100;
		return result;
	}
	else
		return result;
}


std::array<int, 2> Humain::console(Echiquier* echiquier, Couleur c)
{
	std::array<int, 2> result;
	result[0] = 99;
	result[1] = 99;
	int p = 0;
	std::cout << "Quelle piece a deplacer? (entrez num de case)" << "\n";
	std::cout << "pour le roc:" << "\n";
	std::cout << "petit = 64" << "\n";
	std::cout << "grand = 65" << "\n";
	cin >> p;

	if (p == 64 || p == 65)
	{
		result[0] = p;
		result[1] = 66;
	}
	else
	{
		int k = echiquier->get_piece_from_occupation(Piece::one_ << p,c);
		if (k == 32)
			std::cout << "la piece n'existe pas, veuillez ressaisir une position valide888" << "\n";
		else if (echiquier->get_piece_from_list_pieces(k)->getCouleur() != c)
			std::cout << "cette piece ne vous appartient pas!" << "\n";
		else
		{
			if (echiquier->get_piece_from_list_pieces(k)->IsDestroyed())
				std::cout << "la piece n'existe pas, veuillez ressaisir une position valide999" << "\n";
			else
			{
				// std::cout des info sur la pièces p sélectionnées
				std::cout << "couleur" << "\n" << echiquier->get_piece_from_list_pieces(k)->getCouleur() << "\n";
				std::cout << "Valeur" << "\n" << echiquier->get_piece_from_list_pieces(k)->getValeur() << "\n";
				std::cout << "move set" << "\n";
				echiquier->console(echiquier->get_piece_from_list_pieces(k)->get_move_set());
				std::cout << "attack set" << "\n";
				echiquier->console(echiquier->get_piece_from_list_pieces(k)->get_attack_set());
				std::cout << "zone controlee" << "\n";
				echiquier->console(echiquier->get_piece_from_list_pieces(k)->get_controle());
				int t = 0;
				std::cout << "Target? (entrez num de case)" << "\n";
				cin >> t;
				result[0] = p;
				result[1] = t;
			}
		}
	}
	return result;
}