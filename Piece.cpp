#include "Piece.h"

const unsigned long long Piece::one_ = 1;

Piece::Piece(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	:couleur(_couleur), valeur(_valeur), position(_position), move_set(_move_set), attack_set(_attack_set), controle(_controle)
{}

Piece::Piece()
{}

bool Piece::getRocFichu()
{
	return roc_fichu;
}

bool Piece::getAroqueDef()
{
	return aRoqueDef;
}

void Piece::setAroqueDef(bool x)
{
	aRoqueDef = x;
}

bool Piece::getAroque()
{
	return aRoque;
}

void Piece::setAroque(bool x)
{
	aRoque = x;
}

Type Piece::getType()
{
	return type;
}

bool Piece::getGRN()
{
	return grand_roc_noir;
}

bool Piece::getGRB()
{
	return grand_roc_blanc;
}

bool Piece::getPRB()
{
	return petit_roc_blanc;
}

bool Piece::getPRN()
{
	return petit_roc_noir;
}

bool Piece::getPromotion()
{
	return promotion;
}

bool Piece::getAnnulation()
{
	return annulation_phase;
}

bool Piece::IsDestroyed()
{
	return destroyed;
}

bool Piece::getDestructionDefinitive()
{
	return defitivelyDestroyed;
}

void Piece::destructionDefinitive()
{
	defitivelyDestroyed = true;
}


void Piece::setGRB(bool b_)
{
	grand_roc_blanc = b_;
}

void Piece::setGRN(bool b_)
{
	grand_roc_noir = b_;
}

void Piece::setPRB(bool b_)
{
	petit_roc_blanc = b_;
}

void Piece::setPRN(bool b_)
{
	petit_roc_noir = b_;
}

void Piece::destruction(bool x_)
{
	destroyed = x_;
}

Couleur Piece::getCouleur()
{
	return couleur;
}

int Piece::getValeur()
{
	return valeur;
}

bool Piece::getEchec()
{
	return echec;
}

void Piece::setEchec(U64 position_roi)
{
	if ((controle & position_roi) != 0)
		echec = true;
	else
		echec = false;
}

void Piece::setEchecRoi(bool x_)
{
	echec = x_;
}

void Piece::setValeur(int _x)
{
	valeur = _x;
}

sf::Sprite Piece::getSprite()
{
	return sprite;
}

U64 Piece::get_attack_set()
{
	return attack_set;
}

U64 Piece::getPosition()
{
	return position;
}

U64 Piece::get_controle()
{
	return controle;
}

U64 Piece::get_move_set()
{
	return move_set;
}

void Piece::setAnnulation(bool x_)
{
	annulation_phase = x_;
}

void Piece::setAttackSet(U64 _x)
{
	attack_set = _x;
}

void Piece::setMoveSet(U64 _x)
{
	move_set = _x;
}

void Piece::setPosition(U64 x_)
{
	/*  63 62 61 60 59 58 57 56
	    55 54 53 52 51 50 49 48
		47 46 45 44 43 42 41 40
		39 38 37 36 35 34 33 32
		31 30 29 28 27 26 25 24
		23 22 21 20 19 18 17 16
		15 14 13 12 11 10 09 08
		07 06 05 04 03 02 01 00  */

	position = x_;
}

void Piece::setControle(U64 _x)
{
	controle = _x;
}

void Piece::setSprite(sf::Sprite sprite_)
{
	sprite = sprite_;
}

void Piece::positionning_sprite(unsigned int sprite_size_)
{
	int position_num = floor(log2(position));
	sprite.setPosition(((63 - position_num) % 8)*floor(sprite_size_*0.3), ((63 - position_num) / 8)*floor(sprite_size_*0.3));
}


U64 Piece::file_selection_south(U64 _position, U64 _empty)
{
	U64 result = _position;
	for (int i = 0; i < 7; i++)
	{
		if (((_position >> 8) & _empty) == 0)
			controle |= (_position >> 8);
		else
			result |= _position = _position >> 8;
	}
	return(result);
}

U64 Piece::file_selection_north(U64 _position, U64 _empty)
{
	U64 result = _position;
	for (int i = 0; i < 7; i++)
	{
		if (((_position << 8) & _empty) == 0)
			controle |= (_position << 8);
		else
			result |= _position = _position << 8;
	}
	return(result);
}

U64 Piece::file_selection(U64 _position, U64 _empty)
{
	return(file_selection_north(_position, _empty) | file_selection_south(_position, _empty));
}

// comparé à file_selection, il y a une petite subtilité pour row_selection : il ne faut pas sélectionner plus que le rang concerné
// En effet, pour file selection, la sélection bit par bit était contrainte par l'espace mémoire du U64. Ca n'est plus le cas pour row selection.
U64 Piece::row_selection_east(U64 _position, U64 _empty)
{
	U64 result = _position;
	U64 notA = ~file_selection(one_ << 7, -1); 
	for (int i = 0; i < 7; i++)
	{
		if (((_position >> 1) & _empty) == 0)
			controle |= ((_position >> 1) & notA);
		else
			result |= _position = ((_position >> 1) & notA);
	}
	return(result);
}

U64 Piece::row_selection_west(U64 _position, U64 _empty)
{
	U64 result = _position;
	U64 notH = ~file_selection(one_, -1);
	for (int i = 0; i < 7; i++)
	{
		if (((_position << 1) & _empty) == 0)
			controle |= ((_position << 1) & notH);
		else
			result |= _position = ((_position << 1) & notH);
	}
	return(result);
}

U64 Piece::row_selection(U64 _position, U64 _empty)
{
	return(row_selection_east(_position, _empty) | row_selection_west(_position, _empty));
}

U64 Piece::diagonale_selection_NO(U64 _position, U64 _empty)
{
	U64 result = _position;
	// sélection des cases nord ouest
	U64 notH = ~file_selection(one_, -1);
	for (int i = 0; i < 7; i++)
	{
		if (((_position << 9) & _empty) == 0)
			controle |= ((_position << 9) & notH);
		else
			result |= _position = ((_position << 9) & notH);
	}
	return(result);
}

U64 Piece::diagonale_selection_SE(U64 _position, U64 _empty)
{
	U64 result = _position;
	U64 notA = ~file_selection(one_ << 7, -1); // ici, on veut sélectionner toute la colonne A. Donc on onconsidère un argument _empty = -1 i.e. tout l'échiquier est considéré comme vide
	for (int i = 0; i < 7; i++)
	{
		if (((_position >> 9) & _empty) == 0)
			controle |= ((_position >> 9) & notA);
		else
			result |= _position = ((_position >> 9) & notA);
	}
	return(result);
}

U64 Piece::diagonale_selection(U64 _position, U64 _empty)
{
	return(diagonale_selection_NO(_position, _empty) | diagonale_selection_SE(_position, _empty));
}

U64 Piece::anti_diagonale_selection_SO(U64 _position, U64 _empty)
{
	U64 result = _position;
	U64 notH = ~file_selection(one_, -1); // ici, on veut sélectionner toute la colonne A. Donc on onconsidère un argument _empty = -1 i.e. tout l'échiquier est considéré comme vide
	for (int i = 0; i < 7; i++)
	{
		if (((_position >> 7) & _empty) == 0)
			controle |= ((_position >> 7) & notH);
		else
			result |= _position = ((_position >> 7) & notH);
	}
	return(result);
}

U64 Piece::anti_diagonale_selection_NE(U64 _position, U64 _empty)
{
	U64 result = _position;
	// sélection des cases nord est
	U64 notA = ~file_selection(one_ << 7, -1);
	for (int i = 0; i < 7; i++)
	{
		if (((_position << 7) & _empty) == 0)
			controle |= ((_position << 7) & notA);
		else
			result |= _position = ((_position << 7) & notA);
	}
	return(result);
}

U64 Piece::anti_diagonale_selection(U64 _position, U64 _empty)
{
	return(anti_diagonale_selection_NE(_position, _empty) | anti_diagonale_selection_SO(_position, _empty));
}

void Piece::actualisation(U64 occupation_noire_, U64 occupation_blanche_)
{
	attack_set = controle;
	controle |= move_set;
	move_set &= ~(occupation_blanche_ | occupation_noire_);

	if (couleur == BLANC)
		attack_set &= occupation_noire_;
	else
		attack_set &= occupation_blanche_;
}

void Piece::roc_possible()
{
	if (couleur == NOIR)
	{
		if (grand_roc_noir)
			move_set |= (one_ << 61);
		if (petit_roc_noir)
			move_set |= (one_ << 57);
	}
	else
	{
		if (grand_roc_blanc)
			move_set |= (one_ << 5);
		if (petit_roc_blanc)
			move_set |= (one_ << 1);
	}
}

void Piece::roc_test_occupation_controle()
{
		// test du roc sur les cases occupées
		grand_roc_noir = ((position & ((one_ << 62) | (one_ << 61) | (one_ << 60))) == 0);
		petit_roc_noir = ((position & ((one_ << 57) | (one_ << 58))) == 0);
		grand_roc_blanc = ((position & ((one_ << 4) | (one_ << 5) | (one_ << 6))) == 0);
		petit_roc_blanc = ((position & ((one_ << 1) | (one_ << 2))) == 0);

		// test du roc sur les cases controlees par l'adversaire
		if (couleur == BLANC)
		{
			grand_roc_noir = grand_roc_noir && ((controle & ((one_ << 62) | (one_ << 61) | (one_ << 60))) == 0);
			petit_roc_noir = petit_roc_noir && ((controle & ((one_ << 57) | (one_ << 58))) == 0);
		}
		if (couleur == NOIR)
		{
			grand_roc_blanc = grand_roc_blanc && ((controle & ((one_ << 4) | (one_ << 5) | (one_ << 6))) == 0);
			petit_roc_blanc = petit_roc_blanc && ((controle & ((one_ << 1) | (one_ << 2))) == 0);
		}
}

void Piece::console(U64 result)
{
	std::cout << "  " << "ABCDEFGH" << "\n";
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


