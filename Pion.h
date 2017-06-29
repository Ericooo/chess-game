#pragma once
#include "Piece.h"
class Pion :
	public Piece
{
protected:
	bool priseEnPassant;
public:
	Pion();
	Pion(Couleur couleur, int valeur, U64 position, U64 move_set, U64 _attack_set, U64 _controle);
	~Pion();
	
	void init(Couleur couleur_, int cote_);
	void testEchec();
	void test_promotion(void);
	void testRoc();
	void set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_);
};

