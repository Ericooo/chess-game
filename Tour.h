#pragma once
#include "Piece.h"
class Tour :
	public Piece
{
protected:
	bool roc_fichu;
public:
	Tour();
	Tour(Couleur couleur, int valeur, U64 position, U64 move_set, U64 _attack_set, U64 _controle);
	~Tour();

	void init(Couleur couleur_, int cote_);
	void testEchec();
	void testRoc();
	void set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_);
};

