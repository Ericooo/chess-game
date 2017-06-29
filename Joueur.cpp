#include "Joueur.h"


Joueur::Joueur()
{
}

Joueur::~Joueur()
{
}


std::vector<Action> Joueur::mobilite(Echiquier* e, Couleur c)
{
	std::vector<Action> possibleMove;
	e->actualisation_occupations_controle();
	e->actualisation_pieces();
	e->actualisation_occupations_controle();
	int k = 0;
	if (c == BLANC)
		k = 16;
	for (int r = k; r < k + 16; r++)
	{
		U64 l = e->get_piece_from_list_pieces(r)->getPosition();
		if (!(e->get_piece_from_list_pieces(r)->getDestructionDefinitive()))
		{
			for (int j = 0; j < 64; j++)
			{
				e->actualisation_occupations_controle();
				e->actualisation_pieces();
				e->actualisation_occupations_controle();
				if (!(e->get_piece_from_occupation(l, c) == 32))
				{
					if (((Piece::one_ << j) & (e->get_piece_from_list_pieces(e->get_piece_from_occupation(l, c))->get_attack_set() | e->get_piece_from_list_pieces(e->get_piece_from_occupation(l, c))->get_move_set())) != 0)
					{
						e->get_piece_from_list_pieces(4)->setAnnulation(true);
						e->get_piece_from_list_pieces(20)->setAnnulation(true);
						e->get_piece_from_list_pieces(7)->setAnnulation(true);
						e->get_piece_from_list_pieces(0)->setAnnulation(true);
						e->get_piece_from_list_pieces(16)->setAnnulation(true);
						e->get_piece_from_list_pieces(23)->setAnnulation(true);
						if (e->actualiseur(log2(l), j, c))
						{
							e->annulation(l, Piece::one_ << j, c);
							possibleMove.push_back(Action(e->get_piece_from_list_pieces(r)->getPosition(), Piece::one_ << j, 0)); // Remqarue: il faudrait generaliser l'utilisation de la classe Action dans toutes les autres classes
							e->actualisation_occupations_controle();
							e->actualisation_pieces();
							e->actualisation_occupations_controle();
						}
					}
				}
			}
		}
	}
	return possibleMove;
}