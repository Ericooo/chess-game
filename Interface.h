#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include "Piece.h"
#include "Echiquier.h"
#include "Interaction.h"

// Remarque : Il faudrait atomiser la classe interface en créant des classes PieceDiplay avec en attribut le sprite. 
// PieceDisplay aurait une méthode display() et une méthode update(U64 position). 
// Une instance de PieceDisplay serait en attribut de Piece dont la methode setPosition(U64 position) appèlerait update(U64 position). 
// Pour afficher les zones de controles, on peut avoir une methode dans PieceDisplay update(U64 controle) avec en argument le controle et en attribut sprite_controle

class Interface
{
protected:
	// Elements SFML
	sf::RenderWindow renderWindow;
	sf::Event event;
	sf::Texture texture;
	sf::Texture background;

	// Sprite des elements du jeu
	sf::Sprite board;
	sf::Sprite sprite_roi_noir;
	sf::Sprite sprite_dame_noir;
	sf::Sprite sprite_tour_noir;
	sf::Sprite sprite_fou_noir;
	sf::Sprite sprite_cavalier_noir;
	sf::Sprite sprite_pion_noir;
	sf::Sprite sprite_roi_blanc;
	sf::Sprite sprite_dame_blanc;
	sf::Sprite sprite_tour_blanc;
	sf::Sprite sprite_fou_blanc;
	sf::Sprite sprite_cavalier_blanc;
	sf::Sprite sprite_pion_blanc;
	unsigned int sprite_size;

public:
	Interface();
	~Interface();
	// Construction des sprites à partir de la texture SFML
	void init();
	
	// Get
	sf::Sprite getSpriteDameBlanche();
	sf::Sprite getSpriteDameNoire();
	unsigned int getSpriteSize();
	sf::RenderWindow *getRenderWindow();
	sf::Event getEvent();

	// Chargement des sprites de l'interface dans chaque piece et board
	void load(Echiquier*);
	// Display de l'échiquier et des pieces
	void draw(Echiquier*); 
};

