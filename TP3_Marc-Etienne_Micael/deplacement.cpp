/*************************************************************************************
 *	File  : deplacement.cpp
 *	Author: Anthony Cote & Marc-Etienne Pepin
 *	Date  : 2017/11/01
 *	Goal  : Fonctions qu'utilise la classe deplacement
 ************************************************************************************/

#include "deplacement.h"

 ////////////////////////////////////////////////////////
 // Constructeur
deplacement::deplacement()
{
	_x = 0;
	_y = 0;
	_direction = 'N';
}

// Constructeur parametree
deplacement::deplacement(unsigned int x, unsigned int y, char direction)
{
	assert(direction == 'N' || direction == 'E' || direction == 'S' || direction == 'O');

	_x = x;
	_y = y;
	_direction = direction;
}

//Destructeur
deplacement::~deplacement() {}

// Copieur
deplacement::deplacement(const deplacement & d)
{
	_x = d._x;
	_y = d._y;
	_direction = d._direction;
}

// Change la direction
void deplacement::setDirection(char direction)
{
	assert(direction == 'N' || direction == 'E' || direction == 'S' || direction == 'O');
	_direction = direction;
}

// Change la position
void deplacement::setPosition(unsigned int x, unsigned int y)
{
	_x = x;
	_y = y;
}

// Retourne la direction
char deplacement::getDirection()const
{
	return _direction;
}

// Retourne la position X
int deplacement::getX()const
{
	return _x;
}

// Retourne la position Y
int deplacement::getY()const
{
	return _y;
}

// Affiche la position et la direction
ostream& deplacement::print(ostream& os) const
{
	return os << "(" << _x << "," << _y << ")" << " " << _direction;
}


// Operateur <<
ostream& operator<<(ostream& os, deplacement& d)
{
	return d.print(os);
}

void deplacement::avance(matrice<int>& carte, entity& who) {

	char direction = who.getDirection();

	if (canAdvance(carte, who.getY(), who.getX(), direction, 0)) {
		carte[who.getX()][who.getY()] = 0;
		who.move();
		if (who.get_identity() == "player")
			carte[who.getX()][who.getY()] = 4;
		else
			carte[who.getX()][who.getY()] = 3;
		// placeholder (le 3 devra être remplacé par un zombie)
		/// mettre le son de mouvement
	}
	else if (canAdvance(carte, who.getY(), who.getX(), direction, 3)) {
		/// si who = player then die else do nothing
		/// z = zombie
		/// avec son de mort + lose ?
	}
	else if (canAdvance(carte, who.getY(), who.getX(), direction, 1)) {
		/// p = porte ou truc a acheter
		/// afficher le prix du truc ? 
	}
	else {
		/// bruit collision, do nothing
	}
}

bool deplacement::canAdvance(matrice<int>& carte, const int& y, const int& x, const char& direction, int cas) {

	if (y > 0)
		if (direction == 'N')
			if ((carte[x][y - 1] == cas))
				return true;

	if (x < carte.nbLine())
		if (direction == 'E')
			if ((carte[x + 1][y] == cas))
				return true;

	if (y < carte.nbCol())
		if (direction == 'S')
			if ((carte[x][y + 1] == cas))
				return true;

	if (x > 0)
		if (direction == 'O')
			if ((carte[x - 1][y] == cas))
				return true;

	return false;
}