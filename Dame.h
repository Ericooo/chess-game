#pragma once
#include "Piece.h"
class Dame :
	public Piece
{
public:
	Dame();
	Dame(Couleur couleur, int valeur, U64 position, U64 move_set, U64 _attack_set, U64 _controle);
	~Dame();
	
	void init(Couleur couleur_, int cote_);
	void testRoc();
	void testEchec();
	void set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_);
};

