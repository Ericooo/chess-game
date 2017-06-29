#include "Pion.h"

Pion::Pion()
{}

Pion::Pion(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	: Piece(_couleur, _valeur, _position, _move_set, _attack_set, _controle)
{}

Pion::~Pion()
{}


void Pion::set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_)
{
		U64 empty_ = ~(occupation_noire_ | occupation_blanche_);
		switch (couleur)
		{
		case BLANC:
		{
			if (((position & row_selection(one_ << 8, -1)) == 0)) // Si le pion a bougé, on change ses bitmaps
				move_set = ((position << 8) & empty_);
			else
			{
				if (((position << 8) & empty_) == 0)
					move_set = 0;
				else
					move_set = ((position << 8) | (position << 16));
			}


			attack_set = (((position << 7) & notA) | ((position << 9) & notH)); // le pion est la seule pièce dont le move set et l'attack set diffèrent
			controle = (((position << 7) & notA) | ((position << 9) & notH)) & (~position);
			break;
		}
		case NOIR:
		{
			if (((position & row_selection(one_ << 48, -1)) == 0))
				move_set = (position >> 8) & empty_;
			else
			{
				if (((position >> 8) & empty_) == 0)
					move_set = 0;
				else
					move_set = ((position >> 8) | (position >> 16));
			}

			attack_set = (((position >> 7) & notH) | ((position >> 9) & notA));
			controle = (((position >> 7) & notH) | ((position >> 9) & notA)) & ~position;
			break;
		}
		}
		test_promotion();
		actualisation(occupation_noire_, occupation_blanche_);
	
}

void Pion::test_promotion()
{
	promotion = false;
	if ((position & (row_selection(one_ << 56, -1) | row_selection(one_ << 1, -1))) != 0)
		promotion = true;
}

void Pion::testRoc()
{
	roc_test_occupation_controle();
}

void Pion::init(Couleur couleur_, int cote_)
{
	defitivelyDestroyed = false;
	annulation_phase = false;
	type = PION;
	echec = false;
	grand_roc_noir = true;
	petit_roc_noir = true;
	grand_roc_blanc = true;
	petit_roc_blanc = true;

	couleur = couleur_;
	valeur = 1;
	priseEnPassant = false;
	promotion = false;
	destroyed = false;
	attack_set = 0;

	if (couleur_ == NOIR)
	{
		position = one_ << (56 - cote_);
		move_set = (one_ << (40 - cote_)) | (one_ << (48 - cote_));
		controle = ((one_ << (49 - cote_)) | (one_ << (47 - cote_))) & row_selection(one_ << 40,-1);
	}
	else
	{
		position = one_ << (16 - cote_);
		move_set = (one_ << (24 - cote_)) | (one_ << (32 - cote_));
		controle = ((one_ << (23 - cote_)) | (one_ << (25 - cote_))) & row_selection(one_ << 16, -1);
	}
}
	
