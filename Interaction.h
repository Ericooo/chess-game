#pragma once
#include <iostream>
#include <array>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <random>

class Interaction
{
protected:
	sf::Mouse mouse;
	sf::Vector2f target;
	sf::Event event;

	bool isselected;
	bool istargeted;
	int selectedCell;
	int targetedCell;

public:
	Interaction();
	~Interaction();

	int getSelectedCell();
	int getTargetedCell();

	bool sfml_interact(sf::RenderWindow*, const int sprite_size);
	int sfmlSelect(const sf::RenderWindow *window, int sprite_size, sf::Mouse);
	void restart();
};





