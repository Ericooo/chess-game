#include "Roi.h"

Roi::Roi()
{}

Roi::Roi(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	: Piece(_couleur, _valeur, _position, _move_set, _attack_set, _controle)
{}

Roi::~Roi()
{}


void Roi::testRoc()
{
	if (couleur == NOIR)
	{
		if ((position != (one_ << 59)) && !annulation_phase)
		{
			roc_fichu = true;
			grand_roc_noir = false;
			petit_roc_noir = false;
		}
		if (!(roc_fichu))
		{
			roc_test_occupation_controle();
			grand_roc_blanc = ((position & ((one_ << 4) | (one_ << 5) | (one_ << 6))) == 0);
			petit_roc_blanc = ((position & ((one_ << 1) | (one_ << 2))) == 0);
		}
	}
	else
	{
		if ((position != (one_ << 3)) && !annulation_phase)
		{
			roc_fichu = true;
			grand_roc_blanc = false;
			petit_roc_blanc = false;
		}
		if (!(roc_fichu))
		{
			roc_test_occupation_controle();
			petit_roc_noir = ((position & ((one_ << 57) | (one_ << 58))) == 0);
			grand_roc_noir = ((position & ((one_ << 62) | (one_ << 61) | (one_ << 60))) == 0);
		}
	}
}

void Roi::set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_)
{
		U64 empty_ = ~(occupation_noire_ | occupation_blanche_);
		controle = 0;
		move_set = (((position >> 1) & notA) | ((position << 1) & notH) | (position << 8) | (position >> 8) | ((position << 9) & notH) | ((position >> 9) & notA) | ((position << 7) & notA) | ((position >> 7) & notH));
		controle = move_set;
		actualisation(occupation_noire_, occupation_blanche_);
}


void Roi::test_echec(U64 zone_de_controle_blanche_, U64 zone_de_controle_noire_)
{
	// les rois  ne peuvent pas bouger dans les cases controlées par l'adversaire
	if (couleur == NOIR)
		move_set &= ~zone_de_controle_blanche_;
	else
		move_set &= ~zone_de_controle_noire_;

	if (((position & zone_de_controle_blanche_) != 0) & (couleur == NOIR))
		echec = 1;
	else
		echec = 0;

	if (((position & zone_de_controle_noire_) != 0) & (couleur == BLANC))
		echec = 1;
	else
		echec = 0;
}

void Roi::init(Couleur couleur_, int cote_)
{
	aRoqueDef = false;
	defitivelyDestroyed = false;
	annulation_phase = false;
	type = ROI;
	echec = false;
	roc_fichu = false;
	grand_roc_noir = true;
	petit_roc_noir = true;
	grand_roc_blanc = true;
	petit_roc_blanc = true;

	promotion = false;
	couleur = couleur_;
	valeur = 1000;
	move_set = 0;
	attack_set = 0;
	destroyed = false;

	if (couleur_ == NOIR)
	{
		position = (one_ << 59);
		controle = (one_ << 60) | (one_ << 58) | (one_ << 52) | (one_ << 51) | (one_ << 50);
	}
	else
	{
		position = (one_ << 3);
		controle = (one_ << 2) | (one_ << 4) | (one_ << 10) | (one_ << 11) | (one_ << 12);
	}
}
