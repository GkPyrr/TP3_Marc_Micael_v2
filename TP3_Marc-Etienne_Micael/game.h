/*************************************************************************************
*	Auteur:		Marc-Etienne Pepin et Micael Gaumond-Roy
*	Date:		01/12/2017
*	Fichier:	game.h
*	But:			## A CHANGER PLUS TARD ##
************************************************************************************/
#pragma once
#include <SFML\Graphics.hpp>
#include "matrice.hpp"	///changer le nom de map pour enlever gen
#include "vecteur.hpp"
#include <fstream>
#include <string>
#include "deplacement.h"
#include "entity.h"
#include <Windows.h>

using namespace sf;

class game
{
private:
	vecteur<Texture> _texRen;
	matrice<int> _gameMap;
	RenderWindow _window;

public:
	game();
	~game();

	bool init();

	void event(entity& player, vecteur<Texture>& _Rotate, int i, char tableauimage[]);
};