#include "IA.h"

IA::IA()
{}

IA::~IA()
{}

int IA::numberTypeColor(Echiquier* e, Type t, Couleur c)
{
	e->actualisation_occupations_controle();
	e->actualisation_pieces();
	e->actualisation_occupations_controle();
	int result = 0;
	for (int i = 0; i < 32; i++)
		if (!(e->get_piece_from_list_pieces(i)->IsDestroyed()) && (e->get_piece_from_list_pieces(i)->getType() == t) && e->get_piece_from_list_pieces(i)->getCouleur() == c)
			result++;
	return result;
}

int IA::evaluation(Echiquier* e, Couleur c)
{
	// matériel
	int fou;
	int cavalier;
	int tour;
	int roi;
	int pion;
	int dame;

	if (c == BLANC)
	{
		tour = numberTypeColor(e, TOUR, BLANC) - numberTypeColor(e, TOUR, NOIR);
		fou = numberTypeColor(e, FOU, BLANC) - numberTypeColor(e, FOU, NOIR);
		cavalier = numberTypeColor(e, CAVALIER, BLANC) - numberTypeColor(e, CAVALIER, NOIR);
		roi = numberTypeColor(e, ROI, BLANC) - numberTypeColor(e, ROI, NOIR);
		pion = numberTypeColor(e, PION, BLANC) - numberTypeColor(e, PION, NOIR);
		dame = numberTypeColor(e, DAME, BLANC) - numberTypeColor(e, DAME, NOIR);
	}
	else
	{
		tour = -numberTypeColor(e, TOUR, BLANC) + numberTypeColor(e, TOUR, NOIR);
		fou = -numberTypeColor(e, FOU, BLANC) + numberTypeColor(e, FOU, NOIR);
		cavalier = -numberTypeColor(e, CAVALIER, BLANC) + numberTypeColor(e, CAVALIER, NOIR);
		roi = -numberTypeColor(e, ROI, BLANC) + numberTypeColor(e, ROI, NOIR);
		pion = -numberTypeColor(e, PION, BLANC) + numberTypeColor(e, PION, NOIR);
		dame = -numberTypeColor(e, DAME, BLANC) + numberTypeColor(e, DAME, NOIR);
	}

	// mobilité
	std::vector<Action> possibleMove = mobilite(e, c);
	int numberOfPossibleMove = possibleMove.size();

	int result = 300*fou + 300*cavalier + 1000*roi + 100*pion + 500*dame + numberOfPossibleMove;
	return result;
}



std::array<int, 2> IA::random(Echiquier* e, Couleur c)
{
	std::vector<Action> possibleMove = mobilite(e, c);
	std::array<int, 2> result;
	meilleurCandidat = 0;
	int numberOfPossibleMove = possibleMove.size();

	if (numberOfPossibleMove == 0)
	{
		cout << "Echec et mat";
		result[0] = 100;
		result[1] = 100;
	}
	else
	{
		meilleurCandidat = rand() % numberOfPossibleMove;
		result[0] = log2(possibleMove[meilleurCandidat].getPosition());
		result[1] = log2(possibleMove[meilleurCandidat].getTarget());
	}
	return result;
}

// minmax sur un demi coup
std::array<int, 2> IA::minMax(Echiquier* e, Couleur c)
{
	std::vector<Action> possibleMove = mobilite(e, c);
	std::array<int, 2> result;
	result[0] = 100;
	result[1] = 100;
	meilleurCandidat = 0;
	int numberOfPossibleMove = possibleMove.size();
	if (numberOfPossibleMove == 0)
		cout << "Echec et mat";
	else
	{
		for (int i = 0; i < numberOfPossibleMove; i++)
		{
			e->get_piece_from_list_pieces(4)->setAnnulation(true);
			e->get_piece_from_list_pieces(20)->setAnnulation(true);
			e->get_piece_from_list_pieces(7)->setAnnulation(true);
			e->get_piece_from_list_pieces(0)->setAnnulation(true);
			e->get_piece_from_list_pieces(16)->setAnnulation(true);
			e->get_piece_from_list_pieces(23)->setAnnulation(true);
			//execution du candidat
			e->actualiseur(log2(possibleMove[i].getPosition()), log2(possibleMove[i].getTarget()), c);
			//evaluation du candidat
			possibleMove[i].setValeur(evaluation(e, c));
			//annulation du candidat
			e->annulation(possibleMove[i].getPosition(), possibleMove[i].getTarget(),c);
			//actualisation du meilleur candidat
			if (possibleMove[i].getValeur()>possibleMove[meilleurCandidat].getValeur())
				meilleurCandidat = i;
		}
		result[0] = log2(possibleMove[meilleurCandidat].getPosition());
		result[1] = log2(possibleMove[meilleurCandidat].getTarget());
	}

	return result;
}

int IA::minMax_best_value(Echiquier* e, Couleur c, int depth)
{
	int result = -99999;
	std::vector<Action> possibleMove = mobilite(e, c);
	int numberOfPossibleMove = possibleMove.size();
	if (numberOfPossibleMove == 0)
		cout << "Echec et mat";
	else
	{
		for (int i = 0; i < numberOfPossibleMove; i++)
		{
			e->get_piece_from_list_pieces(4)->setAnnulation(true);
			e->get_piece_from_list_pieces(20)->setAnnulation(true);
			e->get_piece_from_list_pieces(7)->setAnnulation(true);
			e->get_piece_from_list_pieces(0)->setAnnulation(true);
			e->get_piece_from_list_pieces(16)->setAnnulation(true);
			e->get_piece_from_list_pieces(23)->setAnnulation(true);
			//execution du candidat
			e->actualiseur(log2(possibleMove[i].getPosition()), log2(possibleMove[i].getTarget()), c);
			//evaluation du candidat -> meilleur coup pour la couleur c
			if (depth == 0)
				possibleMove[i].setValeur(evaluation(e,c));
			else
			{
				if (c==BLANC)
					possibleMove[i].setValeur(minMax_best_value(e, NOIR, depth - 1));
				else
					possibleMove[i].setValeur(minMax_best_value(e, BLANC, depth - 1));
			}
			//annulation du candidat
			e->annulation(possibleMove[i].getPosition(), possibleMove[i].getTarget(),c);
			
		}

		//calcul du meilleur candidat
		meilleurCandidat = 0;
		for (int i = 0; i < numberOfPossibleMove; i++)
		{
			if (depth % 2 == 0) // Un camp maximise son coup en réponse...
			{
				if (possibleMove[i].getValeur() > possibleMove[meilleurCandidat].getValeur())
					meilleurCandidat = i;
			}
			else               // Puis le camp opposé, sachant le calcul effectué par l'autre, va choisir son coup qui minimise l'état de l'autre
			{
				if (possibleMove[i].getValeur() < possibleMove[meilleurCandidat].getValeur())
					meilleurCandidat = i;
			}
		}
		result = possibleMove[meilleurCandidat].getValeur();
	}
	
	return result;
}

std::array<int, 2> IA::playerTurn(Echiquier* e, Couleur c)
{
	std::vector<Action> possibleMove = mobilite(e, c);
	int bestvalue = minMax_best_value(e, c, 1);
	std::array<int, 2> result;
	result[0] = 100;
	result[1] = 100;

	if (bestvalue != -99999)
	{
		result[0] = log2(possibleMove[meilleurCandidat].getPosition());
		cout << "pos" << "\n" << result[0] << "\n";
		result[1] = log2(possibleMove[meilleurCandidat].getTarget());
		cout << "target" << "\n" << result[1] << "\n";
	}

	if (result[0] != 100)
	{
		e->get_piece_from_list_pieces(4)->setAnnulation(false);
		e->get_piece_from_list_pieces(20)->setAnnulation(false);
		e->get_piece_from_list_pieces(7)->setAnnulation(false);
		e->get_piece_from_list_pieces(0)->setAnnulation(false);
		e->get_piece_from_list_pieces(16)->setAnnulation(false);
		e->get_piece_from_list_pieces(23)->setAnnulation(false);
		e->actualiseur(result[0], result[1], c);
	}
	return result;
}