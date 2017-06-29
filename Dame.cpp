#include "Dame.h"

Dame::Dame()
{}

Dame::Dame(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	: Piece(_couleur, _valeur, _position, _move_set, _attack_set, _controle)
{}

Dame::~Dame()
{}

void Dame::testRoc()
{
	roc_test_occupation_controle();
}

void Dame::set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_)
{
		U64 empty_ = ~(occupation_noire_ | occupation_blanche_);
		U64 pos = position;
		controle = 0;
		move_set = diagonale_selection(pos, empty_) | anti_diagonale_selection(pos, empty_) | row_selection(pos, empty_) | file_selection(pos, empty_);
		actualisation(occupation_noire_, occupation_blanche_);
}

void Dame::init(Couleur couleur_, int cote_)
{
	defitivelyDestroyed = false;
	annulation_phase = false;
	type = DAME;
	echec = false;
	petit_roc_blanc = true;
	petit_roc_noir = true;
	promotion = false;
	destroyed = false;
	couleur = couleur_;
	valeur = 10;
	move_set = 0;
	attack_set = 0;

	if (couleur_ == NOIR)
	{
		grand_roc_blanc = true;
		grand_roc_noir = false;
		position = (one_ << 60);
		controle = (one_ << 61) | (one_ << 59) | (one_ << 53) | (one_ << 52) | (one_ << 51);
	}
	else
	{
		grand_roc_blanc = false;
		grand_roc_noir = true;
		position = (one_ << 4);
		controle = (one_ << 3) | (one_ << 5) | (one_ << 11) | (one_ << 12) | (one_ << 13);
	}
}