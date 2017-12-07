/*************************************************************************************
*	Auteur:		Marc-Etienne Pepin et Micael Gaumond-Roy
*	Date:		01/12/2017
*	Fichier:	game.cpp
*	But:			## A CHANGER PLUS TARD ##
************************************************************************************/
#include "game.h"

game::game()
{
}

game::~game()
{
}

bool game::init()
{
	Texture text;
	Sprite pos;
	ifstream input;

	///nombre de i a checker si ajout d'image
	char nomImage[6][20] = { "floor.png" ,"wall_n.png", "corner.png", "box.png", "player_e.png", "menu.png" };

	//cree la fenetre principale
	_window.create(VideoMode(1280, 720, 32), ("Game"));

	//limite le FPS a 60
	_window.setFramerateLimit(60);

	input.open("map02.txt");

	//carte du jeu
	_gameMap.resize(18, 32);
	_gameMap.read(input);
	input.close();

	//loader les images
	for (int i = 0; i < 6; i++)	///nombre de i a checker si ajout d'image
	{
		_texRen.push_back(text);
		if (!_texRen.at(i).loadFromFile(nomImage[i]))
			return EXIT_FAILURE;
	}

	//Texture texPlayer;
	//texPlayer.loadFromImage("player_e.png");
	//Sprite playerS;
	//playerS.setTexture()

	// initialisation du player & zombie 
	entity player(14, 14, 'N');
	player.set_identity("player");

	//boucle de l'execution principale
	while (true)
	{
		//boucle d'evenement
		event(player, _texRen, 4, nomImage[4]);

		for (int line = 0; line < 18; line++)
			for (int col = 0; col < 32; col++)
			{
				pos.setPosition(Vector2f(col * 40, line * 40));
				pos.setTexture(_texRen[_gameMap[line][col]]);
				_window.draw(pos);
			}

		//mise a jour de la fenetre
		_window.display();
		
	}
	return 0;
}

//gestionnaire d'event
void game::event(entity& player, vecteur<Texture>& _Rotate, int i, char tableauimage[])
{
	//evenement de processus
	Event event;

	deplacement mouvement;

	Image newimage;

	while (_window.pollEvent(event))
	{
		if (GetAsyncKeyState(VK_LEFT)) {
			if (player.getDirection() == 'N')
				mouvement.avance(_gameMap, player);
			else {
				player.setDirection('N');
				newimage.loadFromFile(tableauimage);
				newimage.flipHorizontally();
				_texRen.at(i).loadFromImage(newimage);
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			if (player.getDirection() == 'S')
				mouvement.avance(_gameMap, player);
			else {
				player.setDirection('S');
				newimage.loadFromFile(tableauimage);
				_texRen.at(i).loadFromImage(newimage);
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			if (player.getDirection() == 'E')
				mouvement.avance(_gameMap, player);
			else {
				player.setDirection('E');
				newimage.loadFromFile(tableauimage);
				string nomfichier = tableauimage;
				nomfichier = (nomfichier + "_n.png").c_str();
				newimage.loadFromFile(nomfichier);
				newimage.flipVertically();
				_texRen.at(i).loadFromImage(newimage);
			}
		}
		else if (GetAsyncKeyState(VK_UP)) {
			if (player.getDirection() == 'O')
				mouvement.avance(_gameMap, player);
			else {
				player.setDirection('O');
				string nomfichier = tableauimage;
				nomfichier = (nomfichier + "_n.png");//.c_str();
				newimage.loadFromFile(nomfichier);
				_texRen.at(i).loadFromImage(newimage);
			}
		}

		//ferme la fenetre
		if (event.type == Event::Closed)
			_window.close();
	}
}