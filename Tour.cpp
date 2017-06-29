#include "Tour.h"

Tour::Tour(Couleur _couleur, int _valeur, U64 _position, U64 _move_set, U64 _attack_set, U64 _controle)
	: Piece(_couleur, _valeur, _position, _move_set, _attack_set, _controle) 
{}

Tour::~Tour()
{}

Tour::Tour()
{}

void Tour::testRoc()
{
	if (cote == 1 && couleur == NOIR)
	{
		if ((position != (one_ << 63)))
		{
			if (!annulation_phase)
				roc_fichu = true;
			grand_roc_noir = false;
		}
	}
	if (cote == 0 && couleur == NOIR)
	{
		if ((position != (one_ << 56)))
		{
			if (!annulation_phase)
				roc_fichu = true;
			petit_roc_noir = false;
		}
	}
	if (cote == 1 && couleur == BLANC)
	{
		if ((position != (one_ << 7)))
		{
			if (!annulation_phase)
				roc_fichu = true;
			grand_roc_blanc = false;
		}
	}
	if (cote == 0 && couleur == BLANC)
	{
		if ((position != one_))
		{
			if (!annulation_phase)
				roc_fichu = true;
			petit_roc_blanc = false;
		}
	}
	if (!roc_fichu)
	{
		roc_test_occupation_controle();

		if (couleur == NOIR)
		{
			grand_roc_blanc = grand_roc_blanc && (position != ((one_ << 4) | (one_ << 5) | (one_ << 6)));
			petit_roc_blanc = petit_roc_blanc && (position != ((one_ << 1) | (one_ << 2)));
		}
		else
		{
			grand_roc_noir = grand_roc_noir && (position != ((one_ << 62) | (one_ << 61) | (one_ << 60)));
			petit_roc_noir = petit_roc_noir && (position != ((one_ << 57) | (one_ << 58)));
		}
	}
}

void Tour::set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_)
{
	U64 empty_ = ~(occupation_noire_ | occupation_blanche_);
	U64 pos = position;
	controle = 0;
	move_set = row_selection(pos, empty_) | file_selection(pos, empty_);
	actualisation(occupation_noire_, occupation_blanche_);
}

void Tour::init(Couleur couleur_, int cote_)
{
	defitivelyDestroyed = false;
	annulation_phase = false;
	type = TOUR;
	echec = false;
	roc_fichu = false;
	grand_roc_noir = true;
	petit_roc_noir = true;
	grand_roc_blanc = true;
	petit_roc_blanc = true;

	promotion = false;
	couleur = couleur_;
	valeur = 5;
	move_set = 0;
	attack_set = 0;
	destroyed = false;
	cote = cote_;

	if (couleur_ == NOIR)
	{
		if (cote_ == 1)
		{
			position = (one_ << 63);
			controle = (one_ << 55) | (one_ << 62);
		}
		else
		{
			position = (one_ << 56);
			controle = (one_ << 48) | (one_ << 57);
		}
	}
	else
	{
		if (cote_ == 1)
		{
			position = (one_ << 7);
			controle = (one_ << 6) | (one_ << 15);
		}
		else
		{
			position = (one_ << 0);
			controle = (one_ << 1) | (one_ << 8);
		}
	}
}