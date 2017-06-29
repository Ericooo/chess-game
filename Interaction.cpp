#include "Interaction.h"
#include <iostream>


Interaction::Interaction()
{
	isselected = false;
	istargeted = false;
}


Interaction::~Interaction()
{}

int Interaction::sfmlSelect(const sf::RenderWindow *window, int sprite_size, sf::Mouse mouse)
{		
	int a = floor(mouse.getPosition(*window).x);
	int b = floor(mouse.getPosition(*window).y);
	int c = floor(sprite_size);
	if ((a/c)>7)
		return(8 * (b / c) + 7);
	else
		return(8 * (b / c) + (a / c));
}

bool Interaction::sfml_interact(sf::RenderWindow *window, int sprite_size)
{	
	while (window->pollEvent(event) && !(isselected && istargeted))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			isselected = true;
			selectedCell = 63-sfmlSelect(window, sprite_size, mouse);
		}
		sf::Vector2i cursor(event.mouseButton.x, event.mouseButton.y);
		if (isselected && (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right))
		{
			targetedCell = 63-sfmlSelect(window, sprite_size, mouse);
			istargeted = true;
		}

	}
	return(isselected && istargeted);
}

void Interaction::restart()
{
	isselected = false;
	istargeted = false;
}

int Interaction::getTargetedCell()
{
	return targetedCell;
}

int Interaction::getSelectedCell()
{
	return selectedCell;
}

