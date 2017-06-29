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
	
	// bitmaps pour représenter les cases occupées par les blancs ou les noirs 
	// occupation = ensemble des positions occupées
	U64 occupation_blanc;
	U64 occupation_noir;

	// bitmaps pour représenter les zones controlees par les blancs ou les noirs 
	// zone de controle = ensemble des positions ou peut etre effectue un move, une attaque et les positions defendues
	U64 zone_de_controle_blanche;
	U64 zone_de_controle_noire;
	
	// Pour la promotion du pion
	sf::Sprite dame_blanche;
	sf::Sprite dame_noire;
	unsigned int spriteSize;

private:
	// Le destructeur devant gérer la destruction des pointeurs, on s'interdit d'expliciter le code du constructeur copie et de l'operateur = dont on aura besoin par la suite.
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

	// Cette fonction permet de récupérer une pièce de la liste à partir de son index
	Piece* get_piece_from_list_pieces(int index_);
	// Cette fonction permet de récupérer l'index pièce de la liste_piece de l'échiquier à partir de la position.
	int get_piece_from_occupation(U64 position_, Couleur);
	U64 get_occupation_blanc(void);
	U64 get_occupation_noir(void);
	U64 get_zone_de_controle_blanche(void);
	U64 get_zone_de_controle_noire(void);

	// Cette fonction annule un mouvement
	void annulation(U64 position_, U64 target_, Couleur);
	// Cette fonction résout les cas de mise en échec en testant la légalité d'un mouvement pris en argument dans un cas d'échec
	bool gestionEchec(Couleur, U64 position_, U64 target_);
	// Cette fonction réalise les rocs
	bool roc(int cas_, Couleur couleur_);
	// Cette fonction interroge chaque piece pour tester si un roc est possible
	void test_roc();
	// Cette fonction interroge chaque piece pour tester s'il mette le roi adverse en echec
	void test_echec();
	// cette fonction actualise l'occupation et la zone de controle de chaque camp ie l'ensemble des cases contôlés par chaque camp. La fonction actualise également les états d'échec au roi
	void actualisation_occupations_controle(void);
	// cette fonction actualise les positions/controle/move set/ attack set/promotion/roc/echec des pièces de l'échiquier
	void actualisation_pieces(void);
	// Cette fonction permet de déplacer une pièce selon sa position de départ vers une position d'arrivée légale. Elle pocède à l'attaque si besoin
	bool move_execution(U64 position_, U64 target_, Couleur couleur_);
	// Cette fonction prend en entrée la position d'une pièce, sa couleur et une case cible, et elle demande à l'échiquier de s'actualiser en effectuant le mouvement (si licite)
	bool actualiseur(int position, int target, Couleur couleur);
	// Cette fonction propose une interface graphique très spartiate dans la console de visual studio pour aider au debug
	void console(U64 result);

	void gestionDestruction();
};