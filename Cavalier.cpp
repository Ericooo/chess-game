#include "Cavalier.h"

Cavalier::Cavalier()
{}

Cavalier::Cavalier(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	: Piece(_couleur, _valeur, _position, _move_set, _attack_set, _controle)
{}

Cavalier::~Cavalier()
{}

void Cavalier::testRoc()
{
	roc_test_occupation_controle();
}

void Cavalier::set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_)
{
		U64 empty_ = ~(occupation_noire_ | occupation_blanche_);

		move_set = 0;
		move_set |= (position & notA) << 17;
		move_set |= (position & notAB) << 10;
		move_set |= (position & notAB) >> 6;
		move_set |= (position & notA) >> 15;
		move_set |= (position & notH) << 15;
		move_set |= (position & notGH) << 6;
		move_set |= (position & notGH) >> 10;
		move_set |= (position & notH) >> 17;

		controle = move_set;
		actualisation(occupation_noire_, occupation_blanche_);

}


void Cavalier::init(Couleur couleur_, int cote_)
{
	defitivelyDestroyed = false;
	annulation_phase = false;
	type = CAVALIER;
	echec = false;
	promotion = false;
	couleur = couleur_;
	valeur = 3;
	attack_set = 0;
	destroyed = false;

	if (couleur_ == NOIR)
	{
		grand_roc_blanc = true;
		petit_roc_blanc = true;
		if (cote_ == 1)
		{
			grand_roc_noir = false;
			petit_roc_noir = true;
			move_set = (one_ << 47) | (one_ << 45);
			position = (one_ << 62);
			controle = move_set | (one_ << 52);
		}
		else
		{
			grand_roc_noir = true;
			petit_roc_noir = false;
			move_set = (one_ << 42) | (one_ << 40);
			position = (one_ << 57);
			controle = move_set | (one_ << 51);
		}
	}
	else
	{
		grand_roc_noir = true;
		petit_roc_noir = true;
		if (cote_ == 1)
		{
			grand_roc_blanc = false;
			petit_roc_blanc = true;
			move_set = (one_ << 21) | (one_ << 23);
			position = (one_ << 6);
			controle = move_set | (one_ << 12);
		}
		else
		{
			grand_roc_blanc = true;
			petit_roc_blanc = false;
			move_set = (one_ << 16) | (one_ << 18);
			position = (one_ << 1);
			controle = move_set | (one_ << 11);
		}
	}
}
