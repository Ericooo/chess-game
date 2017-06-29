#include "Fou.h"

Fou::Fou(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	: Piece(_couleur, _valeur, _position, _move_set, _attack_set, _controle)
{}

Fou::~Fou()
{}

Fou::Fou()
{}

void Fou::testRoc()
{
	roc_test_occupation_controle();
}

void Fou::set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_)
{
		U64 empty_ = ~(occupation_noire_ | occupation_blanche_);
		U64 pos = position;
		controle = 0;
		move_set = diagonale_selection(pos, empty_) | anti_diagonale_selection(pos, empty_);
		actualisation(occupation_noire_, occupation_blanche_);
}


void Fou::init(Couleur couleur_, int cote_)
{
	defitivelyDestroyed = false;
	annulation_phase = false;
	type = FOU;
	echec = false;
	promotion = false;
	couleur = couleur_;
	valeur = 3;
	move_set = 0;
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
			position = (one_ << 61);
			controle = (one_ << 54) | (one_ << 52);
		}
		else
		{
			grand_roc_noir = true;
			petit_roc_noir = false;
			position = (one_ << 58);
			controle = (one_ << 51) | (one_ << 49);
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
			position = (one_ << 5);
			controle = (one_ << 12) | (one_ << 14);
		}
		else
		{
			grand_roc_blanc = true;
			petit_roc_blanc = false;
			position = (one_ << 2);
			controle = (one_ << 9) | (one_ << 11);
		}
	}
}