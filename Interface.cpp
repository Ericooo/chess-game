#include "Interface.h"

Interface::Interface()
{}

Interface::~Interface()
{}

sf::Event Interface::getEvent()
{
	return event;
}

sf::Sprite Interface::getSpriteDameBlanche()
{
	return sprite_dame_blanc;
}

sf::Sprite Interface::getSpriteDameNoire()
{
	return sprite_dame_noir;
}

sf::RenderWindow *Interface::getRenderWindow()
{
	return &renderWindow;
}

unsigned int Interface::getSpriteSize()
{
	return sprite_size;
}

void Interface::init()
{
	renderWindow.create(sf::VideoMode(800, 800), "Chess Game");
	texture.loadFromFile("pieces.png");
	background.loadFromFile("chessboard.png");
	sprite_size = texture.getSize().x / 6;

	board.setTexture(background);
	board.setScale(sf::Vector2f(1.99f, 1.99f));

	sprite_roi_noir.setTexture(texture);
	sprite_dame_noir.setTexture(texture);
	sprite_fou_noir.setTexture(texture);
	sprite_cavalier_noir.setTexture(texture);
	sprite_tour_noir.setTexture(texture);
	sprite_pion_noir.setTexture(texture);

	sprite_roi_noir.setTextureRect(sf::IntRect(0, sprite_size, sprite_size, sprite_size));
	sprite_dame_noir.setTextureRect(sf::IntRect(sprite_size, sprite_size, sprite_size, sprite_size));
	sprite_fou_noir.setTextureRect(sf::IntRect(sprite_size*2, sprite_size, sprite_size, sprite_size));
	sprite_cavalier_noir.setTextureRect(sf::IntRect(sprite_size*3, sprite_size, sprite_size, sprite_size));
	sprite_tour_noir.setTextureRect(sf::IntRect(sprite_size*4, sprite_size, sprite_size, sprite_size));
	sprite_pion_noir.setTextureRect(sf::IntRect(sprite_size*5, sprite_size, sprite_size, sprite_size));

	sprite_roi_blanc.setTexture(texture);
	sprite_dame_blanc.setTexture(texture);
	sprite_fou_blanc.setTexture(texture);
	sprite_cavalier_blanc.setTexture(texture);
	sprite_tour_blanc.setTexture(texture);
	sprite_pion_blanc.setTexture(texture);

	sprite_roi_blanc.setTextureRect(sf::IntRect(0, 0, sprite_size, sprite_size));
	sprite_dame_blanc.setTextureRect(sf::IntRect(sprite_size, 0, sprite_size, sprite_size));
	sprite_fou_blanc.setTextureRect(sf::IntRect(sprite_size * 2, 0, sprite_size, sprite_size));
	sprite_cavalier_blanc.setTextureRect(sf::IntRect(sprite_size * 3, 0, sprite_size, sprite_size));
	sprite_tour_blanc.setTextureRect(sf::IntRect(sprite_size * 4, 0, sprite_size, sprite_size));
	sprite_pion_blanc.setTextureRect(sf::IntRect(sprite_size * 5, 0, sprite_size, sprite_size));

	sprite_roi_blanc.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_dame_blanc.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_fou_blanc.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_cavalier_blanc.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_tour_blanc.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_pion_blanc.setScale(sf::Vector2f(0.3f, 0.3f));

	sprite_roi_noir.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_dame_noir.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_fou_noir.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_cavalier_noir.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_tour_noir.setScale(sf::Vector2f(0.3f, 0.3f));
	sprite_pion_noir.setScale(sf::Vector2f(0.3f, 0.3f));
}

void Interface::load(Echiquier* echiquier_)
{
	echiquier_->get_piece_from_list_pieces(0)->setSprite(sprite_tour_noir);
	echiquier_->get_piece_from_list_pieces(1)->setSprite(sprite_cavalier_noir);
	echiquier_->get_piece_from_list_pieces(2)->setSprite(sprite_fou_noir);
	echiquier_->get_piece_from_list_pieces(3)->setSprite(sprite_dame_noir);
	echiquier_->get_piece_from_list_pieces(4)->setSprite(sprite_roi_noir);
	echiquier_->get_piece_from_list_pieces(5)->setSprite(sprite_fou_noir);
	echiquier_->get_piece_from_list_pieces(6)->setSprite(sprite_cavalier_noir);
	echiquier_->get_piece_from_list_pieces(7)->setSprite(sprite_tour_noir);

	echiquier_->get_piece_from_list_pieces(16)->setSprite(sprite_tour_blanc);
	echiquier_->get_piece_from_list_pieces(17)->setSprite(sprite_cavalier_blanc);
	echiquier_->get_piece_from_list_pieces(18)->setSprite(sprite_fou_blanc);
	echiquier_->get_piece_from_list_pieces(19)->setSprite(sprite_dame_blanc);
	echiquier_->get_piece_from_list_pieces(20)->setSprite(sprite_roi_blanc);
	echiquier_->get_piece_from_list_pieces(21)->setSprite(sprite_fou_blanc);
	echiquier_->get_piece_from_list_pieces(22)->setSprite(sprite_cavalier_blanc);
	echiquier_->get_piece_from_list_pieces(23)->setSprite(sprite_tour_blanc);

	for (int i = 0; i < 8; i++)
	{
		echiquier_->get_piece_from_list_pieces(8+i)->setSprite(sprite_pion_noir);
		echiquier_->get_piece_from_list_pieces(24+i)->setSprite(sprite_pion_blanc);
	}
}

void Interface::draw(Echiquier* echiquier_)
{
	for (int i = 0; i < 32; i++)
		echiquier_->get_piece_from_list_pieces(i)->positionning_sprite(sprite_size);

	renderWindow.clear();
	renderWindow.draw(board);

	for (int i = 0; i < 32; i++)
		if (!(echiquier_->get_piece_from_list_pieces(i)->getDestructionDefinitive()))
			renderWindow.draw(echiquier_->get_piece_from_list_pieces(i)->getSprite());

	renderWindow.display();
}

