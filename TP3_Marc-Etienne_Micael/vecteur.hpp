/*************************************************************************************
*	Auteur:		Micael Gaumond-Roy
*	Date:		20/09/2017
*	Fichier:	vecteur.h
*	But:		Manipulation d'un conteneur d'objet ou de variable en memoire
*				dynamique.
*				Permet de construire et de detruire le conteneur.
*				D'acceder et de modifier ses elements et sa taille.
*				D'effacer son contenue et reinitialiser ses parametres.
*				D'afficher et de comparer different conteneur.
************************************************************************************/
#pragma once
#include <iostream>
#include <assert.h>

using namespace std;

template <class TYPE>	//classe de tout type
class vecteur
{
protected:
	TYPE *_tab;	//pointeur sur le vecteur TYPE
	int _dim;	//dimension du vecteur
public:
	vecteur(void);						//constructeur par defaut
	vecteur(int dim);					//construit le vecteur a la dimension dim
	vecteur(const vecteur <TYPE>&v);	//copieur de vecteur
	~vecteur();							//destruit le vecteur et desalloue la memoire

	void push_back(const TYPE &element);	//ajoute un element a la fin du vecteur

	int size()const;		//retourne la taille du vecteur
	void resize(int dim);	//modifie la taille du vecteur

	TYPE& front()const;					//retourne le premier element du vecteur
	TYPE& back()const;					//retourne le dernier element du vecteur
	TYPE& at(int pos)const;				//retourne l'element a la position
	TYPE& operator[](int pos)const;		//retourne la position

	void insert(const TYPE &element, int pos);	/*ajoute un element
												a la position*/
	void erase(int pos, int toPos);	/*efface les elements
									d'une position a une autre*/

	void shift(int nbShift);	/*decale les elements du vecteur selon un nombre
								entier*/

	void inverse();					//inverse les elements du vecteur
	void inverseRecursive(int pos);	/*inverse les elements du vecteur
									recursivement*/

	void print(ostream &output)const;	//affiche le contenu du vecteur

	void clear();	/*efface l'adresse memoire du vecteur
					et remet sa taille a 0*/

	vecteur<TYPE> operator+(const vecteur <TYPE>&v)const;	/*ajoute le contenu d'un
														vecteur dans un autre
														vecteur*/
	const vecteur<TYPE>& operator+=(const vecteur <TYPE>&v);	//concatene 2 vecteur

	const vecteur<TYPE>& operator=(const vecteur <TYPE>&v);		/*affecte le contenue
																d'un vecteur a un
																autre vecteur*/

	bool operator==(const vecteur <TYPE>&v)const;	//compare le contenue de 2 vecteur
	bool isSymetric(const vecteur <TYPE>&v)const;	//compare la symetrie de 2 vecteur
	bool isSymetricRecursive(const vecteur <TYPE>&v, int pos)const;	/*compare la
																	symetrie de
																	2 vecteur
																	recursivement*/

	friend void swap(vecteur <TYPE>&v1, vecteur <TYPE>&v2);	/*permute le contenu
															de 2 vecteur*/
};
//surcharge l'operateur de flux de sortie
template <class TYPE>
ostream &operator<<(ostream &output, const vecteur <TYPE>&v);

//constructeur par defaut
template <class TYPE>
vecteur<TYPE>::vecteur(void)
{
	_dim = 0;
	_tab = nullptr;
}

//constructeur avec la dimension en parametre
template <class TYPE>
vecteur<TYPE>::vecteur(int dim)
{
	assert(dim >= 0);
	_dim = dim;
	_tab = nullptr;

	if (_dim != 0)	//construit le vecteur seulement si dim != 0
		_tab = new TYPE[_dim];
}

//copieur de vecteur
template <class TYPE>
vecteur<TYPE>::vecteur(const vecteur <TYPE>&v)
{
	_dim = v._dim;

	if (_dim == 0)	//si la taille est de 0
		_tab = nullptr;	//on vide la tab
	else
	{
		_tab = new TYPE[_dim];

		assert(_tab != nullptr);

		for (int i = 0; i < _dim; i++)	//sinon le vecteur est copier
			*(_tab + i) = *(v._tab + i);
	}
}

//destruit le vecteur et efface son adresse en memoire dynamique
template <class TYPE>
vecteur<TYPE>::~vecteur()
{
	clear();
}

//ajoute un entier a la fin du vecteur
template <class TYPE>
void vecteur<TYPE>::push_back(const TYPE &element)
{
	TYPE *newTab = new TYPE[_dim + 1];	//declare une nouvelle tab 
										//avec la taille actuelle + 1

	for (int i = 0; i < _dim; i++)		//ajoute les elements de la tab
		*(newTab + i) = *(_tab + i);	//original dans la nouvelle tab

	*(newTab + _dim) = element;			//ajoute le nouvelle element

	delete[] _tab;						//suprime la tab original et
	_dim++;								//incremente la taille de 1
	_tab = newTab;						//assigne l'adresse de la nouvelle tab
}

//retourne la taille du vecteur
template <class TYPE>
int vecteur<TYPE>::size()const
{
	return _dim;
}

//modifie la taille du vecteur
template <class TYPE>
void vecteur<TYPE>::resize(int newDim)
{
	TYPE *newTab = nullptr;

	if (newDim != 0)
	{
		newTab = new TYPE[newDim];

		for (int i = 0; i < _dim && i < newDim; i++)
			*(newTab + i) = *(_tab + i);
	}

	delete[] _tab;
	_dim = newDim;
	_tab = newTab;
}

//retourne le premier element du vecteur
template <class TYPE>
TYPE& vecteur<TYPE>::front()const
{
	assert(_tab != nullptr);
	return *_tab;
}

//retourne le dernier element du vecteur
template <class TYPE>
TYPE& vecteur<TYPE>::back()const
{
	assert(_tab != nullptr);
	return *(_tab + _dim - 1);
}

//retourne l'entier a la position
template <class TYPE>
TYPE& vecteur<TYPE>::at(int pos)const
{
	assert(_tab != nullptr);
	assert(pos >= 0);	
	assert(pos <= _dim);
	return *(_tab + pos);
}

//accede a un element du vecteur
template <class TYPE>
TYPE& vecteur<TYPE>::operator[](int pos)const
{
	return at(pos);
}

//ajoute un element a la position
template <class TYPE>
void vecteur<TYPE>::insert(const TYPE &element, int pos)
{
	assert(pos < _dim);

	TYPE *newTab = new TYPE[_dim + 1];

	for (int i = 0; i < pos; i++)		//copie les elements du vecteur
		*(newTab + i) = *(_tab + i);	//jusqu'a la position

	*(newTab + pos) = element;			//insert l'element

	for (int i = pos; i < _dim; i++)	//copie le reste des elements
		*(newTab + i + 1) = *(_tab + i);//jusqu'a la fin du vecteur

	delete[] _tab;
	_dim++;
	_tab = newTab;
}

//efface les elements d'une position a une autre
template <class TYPE>
void vecteur<TYPE>::erase(int pos, int toPos)
{
	assert(pos <= toPos);	assert(toPos < _dim);

	int nbElement = toPos + 1 - pos;	//nombre d'element retirer du vecteur
	int newDim = _dim - nbElement;		//nouvelle taille du vecteur

	if (newDim == 0) //si on vide le vecteur en supprimant du 1er au dernier élément
	{
		clear();
	}

	TYPE *newTab = new TYPE[newDim];	//declare une nouvelle tab

	for (int i = 0; i < pos; i++)		//copie les elements du vecteur
		*(newTab + i) = *(_tab + i);	//jusqu'a la position

	for (int i = toPos + 1; i < _dim; i++)			//copie les elements du vecteur
		*(newTab + i - nbElement) = *(_tab + i);	//d'une position plus grande 
													//que la derniere position efface

	delete[] _tab;
	_dim = newDim;
	_tab = newTab;
}

//envoie un nombre d'element de la fin
template <class TYPE>
void vecteur<TYPE>::shift(int nbShift)
{
	if (_dim != 0)	//si la tab n'est pas vide
	{
		if (nbShift < 0)	//convertie un nombre de decalage negatif en positif
		{
			int nb = abs(nbShift) % _dim;
			nbShift = _dim - nb;
		}

		if (nbShift > _dim)		/*convertie un nombre de decalage plus
								grand que la taille*/
			nbShift = nbShift % _dim;	/*au nombre de decalage egal a
										celui qui serait de taille
										inferieur a la taille*/

		if (nbShift != 0)	//si le nombre de decalage n'egale pas 0,
		{					//on decale les elements du vecteur
			TYPE *tabTemp = new TYPE[nbShift];

			for (int i = 0; i < nbShift; i++)
				*(tabTemp + i) = *(_tab + (_dim - nbShift) + i);

			for (int i = _dim - 1; i > nbShift - 1; i--)
				*(_tab + i) = *(_tab + (i - nbShift));

			for (int i = 0; i < nbShift; i++)
				*(_tab + i) = *(tabTemp + i);

			delete[] tabTemp;
		}
	}
}

//inverse les elements du vecteur
template <class TYPE>
void vecteur<TYPE>::inverse()
{
	for (int i = 0; i < _dim / 2; i++)
		swap(*(_tab + i), *(_tab + _dim - 1 - i));
}

//inverse les elements du vecteur recursivement
template<class TYPE>
void vecteur<TYPE>::inverseRecursive(int pos)
{
	assert(pos < _dim && pos >= 0);

	//if(pos == _dim / 2)
	swap(*(_tab + pos), *(_tab + (_dim - 1) - pos));	/*permute les elements
														a cette position*/

	if (pos + 1 < _dim / 2)			//si la position + 1 est inferieur
		inverseRecursive(pos + 1);	//a moitier de la taille du vecteur
									//la methode se rappele
}

//affiche le contenu du vecteur
template <class TYPE>
void vecteur<TYPE>::print(ostream &output)const
{
	for (int i = 0; i < _dim; i++)
		output << *(_tab + i);
}

//efface l'adresse memoire du vecteur et remet sa taille a 0
template <class TYPE>
void vecteur<TYPE>::clear()
{
	_dim = 0;
	_tab = nullptr;
	delete[] _tab;
}

//ajoute le contenu d'un vecteur dans un autre vecteur
template <class TYPE>
vecteur<TYPE> vecteur<TYPE>::operator+(const vecteur <TYPE>&v)const
{
	vecteur<TYPE> newVec(_dim + v._dim);	//declare un nouveau vecteur

	if (newVec._dim == 0)	//si la taille des 2 vecteur est de 0
		return newVec;

	for (int i = 0; i < _dim; i++)			//insert le contenu 1er du vecteur 
		*(newVec._tab + i) = *(_tab + i);	//au debut du nouveau vecteur

	for (int i = 0; i < v._dim; i++)				//insert le contenu du 2em vecteur
		*(newVec._tab + i + _dim) = *(v._tab + i);	//a la suite du nouveau vecteur

	return newVec;
}

//concatene 2 vecteur
template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator+=(const vecteur <TYPE>&v)
{
	if (_dim + v._dim == 0)	//si la taille des 2 vecteur est de 0
		return *this;

	int oldDim = _dim;				//stock l'ancien taille
	resize(oldDim + v._dim);		//redimensionne l'implicite

	for (int i = 0; i < v._dim; i++)	//copie la tab de v dans l'implicite
		*(_tab + i + oldDim) = *(v._tab + i);

	return *this;
}

//affecte le contenue d'un vecteur a un autre vecteur
template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator=(const vecteur <TYPE>&v)
{
	if (this == &v)		//si le vecteur a la meme adresse memoire
		return *this;	//retourne lui meme

	clear();

	if (v._dim != 0)	//reconstruire l'implicite si v est non-vide
	{
		_dim = v._dim;
		_tab = new TYPE[_dim];

		for (int i = 0; i < _dim; i++)
			*(_tab + i) = *(v._tab + i);
	}

	return *this;
}

//compare le contenue de 2 vecteur
template <class TYPE>
bool vecteur<TYPE>::operator==(const vecteur <TYPE>&v)const
{
	if (_dim != v._dim)	//si la dimension des 2 vecteur n'est pas egale
		return false;
	else
		for (int i = 0; i < _dim; i++)
			if (*(_tab + i) != *(v._tab + i))	//si l'un des elements des 2 vecteurs
				return false;					//n'est pas egale
	return true;
}

//compare la symetrie de 2 vecteur
template <class TYPE>
bool vecteur<TYPE>::isSymetric(const vecteur <TYPE>&v)const
{
	if (_dim != v._dim)	//si la taille des 2 vecteur n'est pas egale
		return false;
	else
		for (int i = 0; i < _dim; i++)	//sinon, si l'un des element
										//en symetrie n'est pas le même
			if (*(_tab + i) != *(v._tab + (v._dim - 1) - i))
				return false;

	return true;
}

//compare la symetrie de 2 vecteur recursivement
template<class TYPE>
bool vecteur<TYPE>::isSymetricRecursive(const vecteur<TYPE>&v, int pos)const
{
	if (_dim != v._dim)	//si la taille des 2 vecteur n'est pas egale
		return false;
	else
		for (int i = 0; i < _dim; i++)	//sinon, si l'un des element en symetrie
										//n'est pas le même
			return *(_tab + pos) != *(v._tab + (v._dim - 1) - pos) && isSymetricRecursive(v, pos + 1) ? 0 : 1;
}

//permute le contenu de 2 vecteur
template <class TYPE>
void swap(vecteur <TYPE>&v1, vecteur <TYPE>&v2)
{
	if (&v1 != &v2)	//si l'adresse du premier vecteur n'est pas la meme
	{				//que celle du deuxieme vecteur

		int dimTemp = v1._dim;	/*taille temporaire pour echanger le contenu
								des 2 vecteur*/

		int *tabTemp = v1._tab;	/*tab temporaire pour echanger le contenu
								des 2 vecteur*/

		v1._dim = v2._dim;
		v2._dim = dimTemp;

		v1._tab = v2._tab;
		v2._tab = tabTemp;
	}
}

//surcharge l'operateur de flux de sortie
template <class TYPE>
ostream &operator<<(ostream &output, const vecteur <TYPE>&v)
{
	v.print(output);
	return output;
}