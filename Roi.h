#pragma once
#include "Piece.h"
class Roi :
	public Piece
{
protected:
	bool echec;
	//bool roc_fichu;
public:
	Roi();
	Roi(Couleur couleur, int valeur, U64 position, U64 move_set, U64 _attack_set, U64 _controle);
	~Roi();

	void init(Couleur couleur_, int cote_);
	bool getEchec();
	
	void testEchec();
	void testRoc();
	void test_echec(U64 zone_de_controle_blanche, U64 zone_de_controle_noire);
	void set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_);
	
};

