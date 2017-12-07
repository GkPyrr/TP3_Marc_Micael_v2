/*************************************************************************************
 *	Auteur:		Marc-Etienne Pepin et Micael Gaumond-Roy
 *	Date:		05/12/2017
 *	Fichier:	main.cpp
 *	But:			## A CHANGER PLUS TARD ##
 ************************************************************************************/

//directive au preprocesseur
#include <fstream>
#include <iostream>
#include "game.h"
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

//programme principale
int main(int argc, const char **argv)
{
	game gamee;

	gamee.init();

	return EXIT_SUCCESS;
}