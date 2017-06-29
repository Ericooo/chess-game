#pragma once
#include "Piece.h"
class Cavalier :
	public Piece
{
protected:
	U64 notAB = ~(file_selection(one_ << 7, -1) | file_selection(one_ << 6, -1));
	U64 notGH = ~(file_selection(one_ << 1, -1) | file_selection(one_, -1));

public:
	Cavalier(Couleur couleur, int valeur, U64 position, U64 move_set, U64 _attack_set, U64 _controle);
	Cavalier();
	~Cavalier();
	void testRoc();
	void init(Couleur couleur_, int cote_);
	void set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_);
	// Rose des vents du cavalier
	//              NNO NNE
	//	            +17 +15
	//	              | |
	//	  NOO +10 __  | |  __ +6  NEE
	//	              \ /
	//		          >0<
	//	  SOO -6  __  / \  __ -10 SEE
	//	              | | 
	//				  | |
	//				-15 -17
	//			    SSO SSE
};

