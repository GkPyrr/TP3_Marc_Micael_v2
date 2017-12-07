/*************************************************************************************
 *	File  : entity.h
 *	Author: Anthony Cote & Marc-Etienne Pepin
 *	Date  : 2017/11/01
 *	Goal  : L’objet robot offre les mécanismes suivants :
 *			s’initialiser, s’afficher, avancer ds le labyrinthe en empilant les
 *			déplacements, changer de direction. Initialiser le robot consiste à
 *			empiler la position de départ. La pile sera une pile de déplacement.
 ************************************************************************************/

#pragma once
///////////////////
#include <assert.h>
#include <iostream>
///#include <SFML/Graphics.hpp>
///////////////////
using namespace std;
///using namespace sf;


class entity {
private:
	///Texture _texEnt;
	string _identity;			// c'est qui (zombie , player , etc ...)
	int _x;                     // position x du robot
	int _y;                     // position y du robot
	char _direction;            // direction dans laquel le robot regarde
public:
	///entity(unsigned int x, unsigned int y, char direction, Texture tex);
	entity(unsigned int x, unsigned int y, char direction);  // constructeur param
	entity(const entity & d);     // copieur
	void move();                // le robot avance de 1 dans la direction
	void turnLeft();            // change la direction anticlockwise
	void turnRight();           // change la direction clockwise
	void setDirection(char direction);                  // choisi la direction
	void setPosition(unsigned int x, unsigned int y);   // change la position
	char getDirection()const;   // retourne la direction du robot
	int getX()const;            // Retourne la position X
	int getY()const;            // Retourne la position Y
	string get_identity()const;	// retourne l'identité
	string set_identity(string ele); // set l'identité
};