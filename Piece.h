#pragma once
using namespace std;
#include <vector>
#include <cmath>
#include <iterator>
#include <bitset>
#include <iostream>
#include <cstdint>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\RenderTexture.hpp>

enum Couleur {BLANC,NOIR};
enum Type{ROI,DAME,TOUR,FOU,CAVALIER,PION};
// Entier non sign� sur 64bits pour les bitmpas
typedef uint64_t U64;

class Piece
{
protected:

	// cote_ 1 = cot� dame, sinon c�t� roi. Pour les pions, cote va de 1 � 8.
	int cote;
	Couleur couleur;
	int valeur;
	Type type;

	// la position est un un bitmap pr�cisant la position de la pi�ce
	U64 position;
	// Bitmap pour repr�senter le champs des d�placements l�gaux (un bitmap = 64bits)
	U64 move_set;
	// exemple : move set du cavalier blanc cote dame
	/*  . . . . . . . .
	    . . . . . . . .
		. . . . . . . .
		. . . . . . . .
		. . . . . . . .
		x . x . . . . .
		. . . . . . . .
		. 1 . . . . . .   --> move_set = 2^23+2^21. Le bit le plus �lev� est en haut � gauche */

	// Bitmap repr�sentant les attaques potentielles de la pi�ce
	U64 attack_set;
	// Bitmap repr�sentant les cases contr�l�es par la pi�ce : attaques et d�placements potentiels + cases d�fendues
	U64 controle;

	// Deux Bitmaps utiles pour les classes filles
	U64 notA = ~file_selection(one_ << 7, -1);
	U64 notH = ~file_selection(one_, -1);

	bool grand_roc_blanc;
	bool petit_roc_blanc;
	bool grand_roc_noir;
	bool petit_roc_noir;
	
	bool echec;
	bool promotion;
	bool destroyed;

	// Booleen pour pouvoir anuler des mouvements
	// On a deux bool�ens pour la prise d'une piece : destroyed et defitivelyDestroyed. 
	// On passe par ces 2 bool�ens pour faire des annulations de mouvements lors du calcul d'un coup en avant. 
	// Par exemple, dans le min max, l'algorithme est amen� � calculer un demi coup en avance, et il est parfois amen� � calculer des prises
	// potentielles. Dans ce cas, l'algo prend "virtuellement" la pi�ce et destroyed = true. Cependant, lorsque l'on veut annuler la prise
	// de la pi�ce, il faut distinguer les pi�ces r�ellement prises et les pi�ces "virtuellement" prises pour le calcul. En g�n�ral, il n'y a pas
	// de probl�me d'identification de pi�ce. Mais il peut exister des ambiguit� du fait que parfois, on r�cup�re la pi�ce � partir de sa position. 
	// Et il n'ya pas de bijection entre position et pi�ce (pensez par exemple � une pi�ce r�ellement prise en e5 deux coups avant, et un calcul de 
	// prise (virtuelle) sur la m�me position e5 au coup d'apr�s -> 2 pi�ces partagent la m�me position.
	bool defitivelyDestroyed;
	// bool pour annuler un roc
	bool aRoque; 
	bool aRoqueDef;
	bool roc_fichu;
	// Ce bool�en permet de savoir si l'on peut annuler le coup (phase de calcul ou de test de l�galit�)
	bool annulation_phase;

	// J'ai conscience que la mani�re de g�rer une annulation de coup via les 2 bool�ens pr�c�dents n'est pas la mani�re la plus claire de faire.
	// Il s'agit fondamentalement d'un probl�me d'architecture du jeu. Il aurait fallu cr�er une classe "Action" � part enti�re pour g�rer 
	// les mouvements/annulations des coups


	// A encapsuler dans une classe DisplayPiece
	sf::Sprite sprite;

public:

	// Le bit unitaire U64 est l'entier de 64 bits �gal � 1;
	static const U64 one_;

	virtual void init(Couleur couleur_, int cote_) = 0;
	Piece(Couleur couleur, int valeur, U64 position, U64 move_set, U64 _attack_set, U64 _controle);
	Piece();

	// Pour l'interface graphique SFML. Pas encore r�ussi � encapsuler dans une classe DisplayPiece.
	sf::Sprite getSprite();
	void setSprite(sf::Sprite);
	void positionning_sprite(unsigned int sprite_size);

	// Fonctions get et set des attributs
	bool getRocFichu();

	bool getGRN();
	bool getPRN();
	bool getGRB();
	bool getPRB();
	Couleur getCouleur();
	int getValeur();
	U64 getPosition();
	U64 get_move_set();
	U64 get_attack_set();
	U64 get_controle();
	bool IsDestroyed();
	bool getPromotion();
	bool getAnnulation();
	bool getEchec();
	Type getType();
	bool getDestructionDefinitive();
	bool getAroque();
	bool getAroqueDef();

	void setAroqueDef(bool);
	void setAroque(bool);
	void setAnnulation(bool);
	void setGRN(bool);
	void setPRN(bool);
	void setGRB(bool);
	void setPRB(bool);
	void setControle(U64);
	void setAttackSet(U64);
	void setMoveSet(U64);
	void setValeur(int);
	void setPosition(U64);
	void destruction(bool);
	void setEchec(U64 position_roi);
	void setEchecRoi(bool);
	void destructionDefinitive();
	// les m�thodes "selections" suivantes permettent de s�lectionner la colonne, le rang, la diagonale ou l'anti diagonale d'une position donn�e. 
	// Ci dessous la rose des vents des bitmaps
	/*
				 NO    N   NE
				 +9   +8   +7
				   \   |   /
		O +1    <-     0     ->  -1 E
				   /   |   \
				 -7   -8   -9
				 SO    S   SE				 */

	// | est l' op�rateur bit par bit "or". Quand on �crit a |= x, on veut dire a = a|x.
	// & est l' op�rateur bit par bit "and". 
	// >> est l'op�rateur bit par bit "d�calage vers la droite". Ainsi, x >> 8 supprime les 8 derniers bits de x. Si l'on enl�ve tous les
	// bits (ou plus) d'un U64, on obtient 0.
	// << est l'op�rateur bit par bit "d�calage vers la gauche". Ainsi, x << 8 ajoute 8 bits 0 � x. Si l'on ajoute plus de
	// 64 bits � un U64, on obtient 0.
	// l'argument empty permet de s�lectionner uniquement les cases vides de la colonne

	U64 row_selection_east(U64 position_, U64 empty);
	U64 row_selection_west(U64 position_, U64 empty);
	U64 row_selection(U64 position_, U64 empty);

	U64 file_selection_north(U64 position_, U64 empty);
	U64 file_selection_south(U64 position_, U64 empty);
	U64 file_selection(U64 position_, U64 empty);

	U64 diagonale_selection_NO(U64 position_, U64 empty);
	U64 diagonale_selection_SE(U64 position_, U64 empty);
	U64 diagonale_selection(U64 position_, U64 empty);

	U64 anti_diagonale_selection_NE(U64 position_, U64 empty);
	U64 anti_diagonale_selection_SO(U64 position_, U64 empty);
	U64 anti_diagonale_selection(U64 position_, U64 empty);

	// Deux methodes qui actualisent l'attack set, le move set et le controle set d'une piece par rapport � l'occupation du board
	// Cette methode regroupe des lignes de code commune � toutes les pieces
	void actualisation(U64 occupation_noire_, U64 occupation_blanche_);
	// Cette deuxi�me methode regroupe les lignes de code sp�cifique � la piece fille
	virtual void set_move_attack_contole_set(U64 occupation_noire_, U64 occupation_blanche_) = 0;

	// M�thode g�rant le roc
	virtual void testRoc() = 0;
	void roc_test_occupation_controle();
	void roc_possible();

	// Cette fonction propose une interface graphique tr�s spartiate dans la console de visual studio pour aider au debug
	void console(U64 result);
};
