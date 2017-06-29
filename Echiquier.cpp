#include "Echiquier.h"

Echiquier::Echiquier()
{}

Echiquier::~Echiquier()
{
	cout << "destruction";
	for (int i = 0; i < 32; i++)
		delete liste_pieces[i];
}

void Echiquier::init()
{
	liste_pieces[0] = new Tour();
	liste_pieces[0]->init(NOIR, 1);
	liste_pieces[1] = new Cavalier();
	liste_pieces[1]->init(NOIR, 1);
	liste_pieces[2] = new Fou();
	liste_pieces[2]->init(NOIR, 1);
	liste_pieces[3] = new Dame();
	liste_pieces[3]->init(NOIR, 0);
	liste_pieces[4] = new Roi();
	liste_pieces[4]->init(NOIR, 0);
	liste_pieces[5] = new Fou();
	liste_pieces[5]->init(NOIR, 0);
	liste_pieces[6] = new Cavalier();
	liste_pieces[6]->init(NOIR, 0);
	liste_pieces[7] = new Tour();
	liste_pieces[7]->init(NOIR, 0);

	liste_pieces[8] = new Pion();
	liste_pieces[8]->init(NOIR, 1);
	liste_pieces[9] = new Pion();
	liste_pieces[9]->init(NOIR, 2);
	liste_pieces[10] = new Pion();
	liste_pieces[10]->init(NOIR, 3);
	liste_pieces[11] = new Pion();
	liste_pieces[11]->init(NOIR, 4);
	liste_pieces[12] = new Pion();
	liste_pieces[12]->init(NOIR, 5);
	liste_pieces[13] = new Pion();
	liste_pieces[13]->init(NOIR, 6);
	liste_pieces[14] = new Pion();
	liste_pieces[14]->init(NOIR, 7);
	liste_pieces[15] = new Pion();
	liste_pieces[15]->init(NOIR, 8);

	liste_pieces[16] = new Tour();
	liste_pieces[16]->init(BLANC, 1);
	liste_pieces[17] = new Cavalier();
	liste_pieces[17]->init(BLANC, 1);
	liste_pieces[18] = new Fou();
	liste_pieces[18]->init(BLANC, 1);
	liste_pieces[19] = new Dame();
	liste_pieces[19]->init(BLANC, 0);
	liste_pieces[20] = new Roi();
	liste_pieces[20]->init(BLANC, 0);
	liste_pieces[21] = new Fou();
	liste_pieces[21]->init(BLANC, 0);
	liste_pieces[22] = new Cavalier();
	liste_pieces[22]->init(BLANC, 0);
	liste_pieces[23] = new Tour();
	liste_pieces[23]->init(BLANC, 0);

	liste_pieces[24] = new Pion();
	liste_pieces[24]->init(BLANC, 1);
	liste_pieces[25] = new Pion();
	liste_pieces[25]->init(BLANC, 2);
	liste_pieces[26] = new Pion();
	liste_pieces[26]->init(BLANC, 3);
	liste_pieces[27] = new Pion();
	liste_pieces[27]->init(BLANC, 4);
	liste_pieces[28] = new Pion();
	liste_pieces[28]->init(BLANC, 5);
	liste_pieces[29] = new Pion();
	liste_pieces[29]->init(BLANC, 6);
	liste_pieces[30] = new Pion();
	liste_pieces[30]->init(BLANC, 7);
	liste_pieces[31] = new Pion();
	liste_pieces[31]->init(BLANC, 8);

	zone_de_controle_blanche = liste_pieces[0]->row_selection(Piece::one_ << 16, -1) | liste_pieces[0]->row_selection(Piece::one_ << 8, -1) | liste_pieces[0]->row_selection(Piece::one_ << 0, -1);
	zone_de_controle_noire = liste_pieces[0]->row_selection(Piece::one_ << 56, -1) | liste_pieces[0]->row_selection(Piece::one_ << 48, -1) | liste_pieces[0]->row_selection(Piece::one_ << 40, -1);
	occupation_noir = liste_pieces[0]->row_selection(Piece::one_ << 48, -1) | liste_pieces[0]->row_selection(Piece::one_ << 56, -1);
	occupation_blanc = liste_pieces[0]->row_selection(Piece::one_ << 0, -1) | liste_pieces[0]->row_selection(Piece::one_ << 8, -1);
	
}

Piece* Echiquier::get_piece_from_list_pieces(int index_)
{
	return liste_pieces[index_];
}

U64 Echiquier::get_occupation_blanc(void)
{
	return occupation_blanc;
}

U64 Echiquier::get_occupation_noir(void)
{
	return occupation_noir;
}

U64 Echiquier::get_zone_de_controle_blanche(void)
{
	return zone_de_controle_blanche;
}

U64 Echiquier::get_zone_de_controle_noire(void)
{
	return zone_de_controle_noire;
}

int Echiquier::get_piece_from_occupation(U64 _position, Couleur c)
{
	int i = 0;
	bool fin = false;
	while (!(fin) && (i < 32))
	{
		if ((!liste_pieces[i]->IsDestroyed()) && (liste_pieces[i]->getPosition() == _position) && !(liste_pieces[i]->getDestructionDefinitive()) && liste_pieces[i]->getCouleur()==c)
			fin = true;
		else
			i++;
	}
	return i;
}


void Echiquier::actualisation_occupations_controle()
{
	occupation_blanc = 0;
	occupation_noir = 0;
	zone_de_controle_blanche = 0;
	zone_de_controle_noire = 0;
	for (int i = 16; i < 32; i++)
	{
		if (!liste_pieces[i]->getDestructionDefinitive())
		{
			occupation_blanc |= liste_pieces[i]->getPosition();
			zone_de_controle_blanche |= liste_pieces[i]->get_controle();
		}
			
	}
	for (int i = 0; i < 16; i++)
	{
		if (!liste_pieces[i]->getDestructionDefinitive())
		{
			occupation_noir |= liste_pieces[i]->getPosition();
			zone_de_controle_noire |= liste_pieces[i]->get_controle();
		}
	}
	test_roc();
}

void Echiquier::test_roc()
{
	bool temp = true;
	bool temp1 = true;
	bool temp2 = true;
	bool temp3 = true;

	for (int i = 0; i < 32; i++)
	{
		if (!liste_pieces[i]->IsDestroyed())
		{
			liste_pieces[i]->testRoc();
			temp = temp && liste_pieces[i]->getPRB();
			temp1 = temp1 && liste_pieces[i]->getGRB();
			temp2 = temp2 && liste_pieces[i]->getPRN();
			temp3 = temp3 && liste_pieces[i]->getGRN();
		}
	}
	//roi blanc
	liste_pieces[20]->setPRB(temp);
	liste_pieces[20]->setGRB(temp1);
	liste_pieces[20]->roc_possible();

	//roi noir
	liste_pieces[4]->setPRN(temp2);
	liste_pieces[4]->setGRN(temp3);
	liste_pieces[4]->roc_possible();
}

void Echiquier::test_echec()
{
	actualisation_occupations_controle();
	bool temp = false;
	bool temp2 = false;

	for (int i = 0; i < 16; i++)
	{
		if (!liste_pieces[i]->IsDestroyed() && !liste_pieces[i]->getDestructionDefinitive())
		{
			liste_pieces[i]->setEchec(liste_pieces[20]->getPosition());
			temp = temp || liste_pieces[i]->getEchec();
		}
	}
	for (int i = 16; i < 32; i++)
	{
		if (!liste_pieces[i]->IsDestroyed() && !liste_pieces[i]->getDestructionDefinitive())
		{
			liste_pieces[i]->setEchec(liste_pieces[4]->getPosition());
			temp2 = temp2 || liste_pieces[i]->getEchec();
		}
	}
	liste_pieces[20]->setEchecRoi(temp);
	liste_pieces[4]->setEchecRoi(temp2);
}

bool Echiquier::gestionEchec(Couleur c, U64 position_, U64 target_)
{
	actualisation_occupations_controle();
	actualisation_pieces();
	actualisation_occupations_controle();
	test_echec();
	bool echecApresMove;
	if (c == BLANC)
		echecApresMove = get_piece_from_list_pieces(20)->getEchec();
	else
		echecApresMove = get_piece_from_list_pieces(4)->getEchec();

	if (echecApresMove) // On teste la résolution de l'echec
	{
		//std::cout << "mouvement illegal : vous etes toujours en echec" << "\n";
		annulation(position_, target_, c);		
		return false;
	}
	else
		return true;
}



bool Echiquier::roc(int cas_, Couleur couleur_) // cas_ = petit ou grand roc
{
	switch (cas_)
	{
	case 1: //petit roc
	{
		if (couleur_ == NOIR)
		{
			liste_pieces[4]->setPosition(Piece::one_ << 57);
			liste_pieces[7]->setPosition(Piece::one_ << 58);
		}
		else
		{
			liste_pieces[20]->setPosition(Piece::one_ << 1);
			liste_pieces[23]->setPosition(Piece::one_ << 2);
		}
		break;
	}
	case 2: //grand roc
	{
		if (couleur_ == NOIR)
		{
			liste_pieces[4]->setPosition(Piece::one_ << 61);
			liste_pieces[0]->setPosition(Piece::one_ << 60);
		}
		else
		{
			liste_pieces[20]->setPosition(Piece::one_ << 5);
			liste_pieces[16]->setPosition(Piece::one_ << 4);
		}
		break;
	}
	}
	return true;
}

void Echiquier::promotion(U64 position_, Couleur c_,int i)
{
	std::cout << "Promotion du pion en dame" << "\n"; // pouvoir prendre le cavalier?
	U64 position = liste_pieces[i]->getPosition();
	delete liste_pieces[i];
	liste_pieces[i] = new Dame();
	liste_pieces[i]->init(c_,0);
	liste_pieces[i]->setPosition(position_);
	if (c_==NOIR)
		liste_pieces[i]->setSprite(dame_noire);
	else
		liste_pieces[i]->setSprite(dame_blanche);
}

void Echiquier::actualisation_pieces()
{
	for (int i = 0; i < 32; i++)
		if (!liste_pieces[i]->getDestructionDefinitive())
			liste_pieces[i]->set_move_attack_contole_set(occupation_noir, occupation_blanc);

	for (int i = 8; i < 16; i++)
		if (liste_pieces[i]->getPromotion() && !liste_pieces[i]->getAnnulation())
			promotion(liste_pieces[i]->getPosition(),liste_pieces[i]->getCouleur(),i);

	for (int i = 24; i < 32; i++)
		if (liste_pieces[i]->getPromotion() && !liste_pieces[i]->getAnnulation())
			promotion(liste_pieces[i]->getPosition(), liste_pieces[i]->getCouleur(), i);
}


void Echiquier::annulation(U64 position_, U64 target_, Couleur c_)
{
	//annulation roque
	if (c_ == BLANC)
	{
		if (liste_pieces[20]->getAroque() && liste_pieces[20]->getAnnulation() && !liste_pieces[20]->getAroqueDef())
		{
			if (log2(liste_pieces[23]->getPosition()) == 2)
				liste_pieces[23]->setPosition(Piece::one_ << 0);
			if (log2(liste_pieces[16]->getPosition()) == 4)
				liste_pieces[16]->setPosition(Piece::one_ << 7);
			liste_pieces[23]->setGRB(true);
			liste_pieces[23]->setPRB(true);
		}
	}
	else
	{
		if (liste_pieces[4]->getAroque() && liste_pieces[4]->getAnnulation() && !liste_pieces[20]->getAroqueDef())
		{
			if (log2(liste_pieces[0]->getPosition()) == 58)
				liste_pieces[0]->setPosition(Piece::one_ << 56);
			if (log2(liste_pieces[7]->getPosition()) == 60)
				liste_pieces[7]->setPosition(Piece::one_ << 63);
			liste_pieces[0]->setGRN(true);
			liste_pieces[7]->setPRN(true);
		}
	}
	// on revient à la position initiale
	if (get_piece_from_occupation(target_, c_) == 32)
	{
		//cout << "annulation impossible, la piece nexiste pas" << "\n";
	}
	else
	{
		get_piece_from_list_pieces(get_piece_from_occupation(target_, c_))->setPosition(position_);
		actualisation_occupations_controle();
		get_piece_from_list_pieces(get_piece_from_occupation(position_, c_))->set_move_attack_contole_set(occupation_noir, occupation_blanc);
	}
	// Dans le cas où une piece a ete detruite, on annule sa destruction
	int i = 0;
	bool fin = false;
	while ((i < 32) && !fin)
	{
		if (!((liste_pieces[i]->getPosition() == target_) && !(liste_pieces[i]->getDestructionDefinitive())))
			i++;
		else
			fin = true;
	}
	if (!(i == 32) && get_piece_from_list_pieces(i)->IsDestroyed())
		get_piece_from_list_pieces(i)->destruction(false);
	actualisation_occupations_controle();
	actualisation_pieces();
	actualisation_occupations_controle();
}

bool Echiquier::move_execution(U64 _position, U64 _target, Couleur c_)
{
	
	
	int i = get_piece_from_occupation(_position, c_);
	if (i == 32) //tester l'existence de la pièce
	{
		//std::cout << "La pièce n'existe pas" << "\n";
		return false;
	}

	else if (get_piece_from_list_pieces(i)->getCouleur() != c_) // tester l'appartenance de la piece
	{
		//std::cout << "cette piece ne vous appartient pas!" << "\n";
		return  false;
	}
	
	else
	{
		liste_pieces[i]->setAroque(false);
		if ((i == 20) && !(liste_pieces[i]->getRocFichu()))
		{
			
			if ((((Piece::one_ << 1) & liste_pieces[i]->get_move_set()) !=0) && (_target == (Piece::one_ << 1)))
			{
				roc(1, BLANC);
				liste_pieces[i]->setAroque(true);
				return true;
			}

			if ((((Piece::one_ << 5) & liste_pieces[i]->get_move_set()) != 0) && (_target == (Piece::one_ << 5)))
			{
				roc(2, BLANC);
				liste_pieces[i]->setAroque(true);
				return true;
			}
		}
		if ((i == 4) && !(liste_pieces[i]->getRocFichu()))
		{
			if ((((Piece::one_ << 57) & liste_pieces[i]->get_move_set()) != 0) && (_target == (Piece::one_ << 57)))
			{
				roc(1, NOIR);
				liste_pieces[i]->setAroque(true);
				return true;
			}
			if ((((Piece::one_ << 61) & liste_pieces[i]->get_move_set()) != 0) && (_target == (Piece::one_ << 61)))
			{
				roc(2, NOIR);
				liste_pieces[i]->setAroque(true);
				return true;
			}
		}
		actualisation_occupations_controle();
		

		if ((liste_pieces[i]->get_move_set() & _target) != 0) //tester l'occupation de la case cible pour déplacement
			liste_pieces[i]->setPosition(_target);
		

		else if ((liste_pieces[i]->get_attack_set() & _target) != 0) //tester l'occupation de la case cible pour attaque
		{
			int j = 0;
			if (c_==BLANC)
				j = get_piece_from_occupation(_target, NOIR); // tester l'existence de la cible
			else
				j = get_piece_from_occupation(_target, BLANC);
			if (j == 32)
			{
				//std::cout << "La pièce n'existe pas" << "\n";
				return false;
			}
			else // destruction de la cible
			{
				liste_pieces[j]->destruction(true); 
				liste_pieces[i]->setPosition(_target);
				actualisation_occupations_controle();
		
			}
		}
		else
		{
			//std::cout << "mouvement illegal" << "\n";
			return false;
		}
	}
	return true;
}



bool Echiquier::actualiseur(int position_, int target_, Couleur c)
{
	bool result = (move_execution(Piece::one_ << position_, Piece::one_ << target_, c) && (gestionEchec(c, Piece::one_ << position_, Piece::one_ << target_)));
	actualisation_occupations_controle();
	actualisation_pieces();
	actualisation_occupations_controle();
	return result;
}

void Echiquier::gestionDestruction()
{
	for (int i = 0; i < 32; i++)
		if (get_piece_from_list_pieces(i)->IsDestroyed())
			get_piece_from_list_pieces(i)->destructionDefinitive();
	if (get_piece_from_list_pieces(4)->getAroque())
		get_piece_from_list_pieces(4)->setAroqueDef(true);
	if (get_piece_from_list_pieces(20)->getAroque())
		get_piece_from_list_pieces(20)->setAroqueDef(true);
}

void Echiquier::setSpriteDames(sf::Sprite blanche_, sf::Sprite noire_)
{
	dame_blanche = blanche_;
	dame_noire = noire_;
}

void Echiquier::setSpriteSize(unsigned int x_)
{
	spriteSize = x_;
}

void Echiquier::console(U64 result)
{
	std::cout << "  " <<"ABCDEFGH" << "\n";
	std::bitset<8> b1(result >> 56);
	std::cout << 8 << " " << b1 << "\n";
	std::bitset<8> b2(result >> 48);
	std::cout << 7 << " " << b2 << "\n";
	std::bitset<8> b3(result >> 40);
	std::cout << 6 << " " << b3 << "\n";
	std::bitset<8> b4(result >> 32);
	std::cout << 5 << " " << b4 << "\n";
	std::bitset<8> b5(result >> 24);
	std::cout << 4 << " " << b5 << "\n";
	std::bitset<8> b6(result >> 16);
	std::cout << 3 << " " << b6 << "\n";
	std::bitset<8> b7(result >> 8);
	std::cout << 2 << " " << b7 << "\n";
	std::bitset<8> b8(result);
	std::cout << 1 << " " << b8 << "\n";
}