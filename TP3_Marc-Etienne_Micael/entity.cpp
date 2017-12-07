/*************************************************************************************
 *	File  : entity.cpp
 *	Author: Anthony Cote & Marc-Etienne Pepin
 *	Date  : 2017/11/01
 *	Goal  : L’objet robot offre les mécanismes suivants :
 *			s’initialiser, s’afficher, avancer ds le labyrinthe en empilant les
 *			déplacements, changer de direction. Initialiser le robot consiste à
 *			empiler la position de départ. La pile sera une pile de déplacement.
 ************************************************************************************/

#include "entity.h"

 ////////////////////////////////////////////////////////
 //Constructeur
entity::entity(unsigned int x, unsigned int y, char direction)
{
	assert(direction == 'N' || direction == 'E' || direction == 'S' || direction == 'O');

	_x = x;
	_y = y;
	_direction = direction;

}

//Copieur
entity::entity(const entity & d)
{
	_x = d._x;
	_y = d._y;
	_direction = d._direction;
}

//Change sa position de 1 dans la direction
void entity::move()
{
	switch (_direction)
	{
	case 'N':
		setPosition(_x, _y - 1);
		break;
	case 'E':
		setPosition(_x + 1, _y);
		break;
	case 'S':
		setPosition(_x, _y + 1);
		break;
	case 'O':
		setPosition(_x - 1, _y);
		break;
	}
}

// Change la direction de 90 degree anti-clockwise
void entity::turnLeft()			// ======================================================= a suprimer si il n'y a pas utiliser
{
	switch (_direction)
	{
	case 'N':
		_direction = 'O';
		break;
	case 'E':
		_direction = 'N';
		break;
	case 'S':
		_direction = 'E';
		break;
	case 'O':
		_direction = 'S';
		break;
	}
}

// Change la direction de 90 degree clockwise
void entity::turnRight()			// ======================================================= a suprimer si il n'y a pas utiliser
{
	switch (_direction)
	{
	case 'N':
		_direction = 'E';
		break;
	case 'E':
		_direction = 'S';
		break;
	case 'S':
		_direction = 'O';
		break;
	case 'O':
		_direction = 'N';
		break;
	}
}

// Change la direction
void entity::setDirection(char direction)
{
	assert(direction == 'N' || direction == 'E' || direction == 'S' || direction == 'O');
	_direction = direction;
}

//Change la position
void entity::setPosition(unsigned int x, unsigned int y)
{
	_x = x;
	_y = y;
}

// Retourne la direction
char entity::getDirection()const
{
	return _direction;
}

// Retourne la position X
int entity::getX()const
{
	return _x;
}

// Retourne la position Y
int entity::getY()const
{
	return _y;
}

// Retourne la position Y
string entity::get_identity()const
{
	return _identity;
}

string entity::set_identity(string ele)
{
	return _identity = ele;
}