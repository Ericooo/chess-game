#pragma once
#include "Pion.h"
#include "Fou.h"
#include "Piece.h"
#include "Roi.h"
#include "Cavalier.h"
#include "Dame.h"
#include "Tour.h"
#include <iterator>
#include <array>

class Echiquier
{
protected:
	std::array<Piece*, 32> liste_pieces;
	
	// bitmaps pour repr�senter les cases occup�es par les blancs ou les noirs 
	// occupation = ensemble des positions occup�es
	U64 occupation_blanc;
	U64 occupation_noir;

	// bitmaps pour repr�senter les zones controlees par les blancs ou les noirs 
	// zone de controle = ensemble des positions ou peut etre effectue un move, une attaque et les positions defendues
	U64 zone_de_controle_blanche;
	U64 zone_de_controle_noire;
	
	// Pour la promotion du pion
	sf::Sprite dame_blanche;
	sf::Sprite dame_noire;
	unsigned int spriteSize;

private:
	// Le destructeur devant g�rer la destruction des pointeurs, on s'interdit d'expliciter le code du constructeur copie et de l'operateur = dont on aura besoin par la suite.
	const Echiquier &Echiquier::operator=(const Echiquier &echiquier);
	Echiquier(const Echiquier &echiquier);
public:
	Echiquier();
	~Echiquier();

	void init();

	// Pour la promotion du pion
	void setSpriteDames(sf::Sprite, sf::Sprite);
	void setSpriteSize(unsigned int);
	void promotion(U64, Couleur, int);

	// Cette fonction permet de r�cup�rer une pi�ce de la liste � partir de son index
	Piece* get_piece_from_list_pieces(int index_);
	// Cette fonction permet de r�cup�rer l'index pi�ce de la liste_piece de l'�chiquier � partir de la position.
	int get_piece_from_occupation(U64 position_, Couleur);
	U64 get_occupation_blanc(void);
	U64 get_occupation_noir(void);
	U64 get_zone_de_controle_blanche(void);
	U64 get_zone_de_controle_noire(void);

	// Cette fonction annule un mouvement
	void annulation(U64 position_, U64 target_, Couleur);
	// Cette fonction r�sout les cas de mise en �chec en testant la l�galit� d'un mouvement pris en argument dans un cas d'�chec
	bool gestionEchec(Couleur, U64 position_, U64 target_);
	// Cette fonction r�alise les rocs
	bool roc(int cas_, Couleur couleur_);
	// Cette fonction interroge chaque piece pour tester si un roc est possible
	void test_roc();
	// Cette fonction interroge chaque piece pour tester s'il mette le roi adverse en echec
	void test_echec();
	// cette fonction actualise l'occupation et la zone de controle de chaque camp ie l'ensemble des cases cont�l�s par chaque camp. La fonction actualise �galement les �tats d'�chec au roi
	void actualisation_occupations_controle(void);
	// cette fonction actualise les positions/controle/move set/ attack set/promotion/roc/echec des pi�ces de l'�chiquier
	void actualisation_pieces(void);
	// Cette fonction permet de d�placer une pi�ce selon sa position de d�part vers une position d'arriv�e l�gale. Elle poc�de � l'attaque si besoin
	bool move_execution(U64 position_, U64 target_, Couleur couleur_);
	// Cette fonction prend en entr�e la position d'une pi�ce, sa couleur et une case cible, et elle demande � l'�chiquier de s'actualiser en effectuant le mouvement (si licite)
	bool actualiseur(int position, int target, Couleur couleur);
	// Cette fonction propose une interface graphique tr�s spartiate dans la console de visual studio pour aider au debug
	void console(U64 result);

	void gestionDestruction();
};