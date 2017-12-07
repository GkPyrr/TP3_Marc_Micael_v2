/*************************************************************************************
 *	File  : deplacement.h
 *	Author: Anthony Cote & Marc-Etienne Pepin
 *	Date  : 2017/11/01
 *	Goal  : Cet objet offre des accesseurs, mutateurs et des fonctions
 *			d’entrée/sortie naturelle. Comme il contient des coordonnées,
 *			il peut-être utilisé dans le labyrinthe comme position de départ et
 *			d’arrivée.
 ************************************************************************************/

#pragma once
#include <assert.h>
#include <iostream>
#include "matrice.hpp"
#include "entity.h"
///////////////////

using namespace std;

class deplacement
{
private:
	int _x;             // Position X de gauche a droite
	int _y;             // Position Y de haut en bas
	char _direction;    // Direction dans laquelle le robot regarde {'N','E','S','O'}

public:
	deplacement();                                              // constructeur
	deplacement(unsigned int x, unsigned int y, char direction);// construct params
	~deplacement();                                             // destructeur
	deplacement(const deplacement& d);                          // copieur


	void setDirection(char direction);                  // Change la direction
	void setPosition(unsigned int x, unsigned int y);   // Change la position

	char getDirection()const;                           // Retourne la direction du deplacement
	int getX()const;                                    // Retourne la position X
	int getY()const;                                    // Retourne la position Y

	ostream& print(ostream& os = cout)const;            // Affiche les coordonnees et la direction

	void avance(matrice<int>& carte, entity & who);						// va essayer d'avancer
	bool canAdvance(matrice<int>& carte, const int& y, const int& x, const char& direction, int cas);		// check si peu avancer
};

ostream& operator<<(ostream& os, deplacement& d);       // operateur <<