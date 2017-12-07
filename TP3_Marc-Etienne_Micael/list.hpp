/*************************************************************************************
 *	Auteur:		Micaël Gaumond-Roy
 *	Date:		15/11/2017
 *	Fichier:	list.hpp
 *	But:		Liste dynamique, utilisant un chainage de cellule
 *				accede au element a l'aide d'un iterateur,
 *				retourne le debut et la fin,
 *				verifie si la liste est vide, la vide,
 *				insert et efface des eleements a n'importequel position,
 *				recheche des elements et les retourne,
 *				compare les elements pointer par l'iterateur
 ************************************************************************************/
#pragma once
#include <assert.h>

template <typename TYPE> class list;

//classe cellule
template <typename TYPE>
class cell
{
	friend class list<TYPE>;	/*classe ayant acces a la
								representation de la cellule*/
	TYPE element;				//contenu de la cellule
	cell<TYPE>	*next;			//pointeur vers la cellule suivante
	cell<TYPE>	*prev;			//pointeur vers la cellule precedent

	cell(const TYPE &e, cell<TYPE> *n = nullptr, cell<TYPE> *p = nullptr)
	{
		element = e;
		next = n;
		prev = p;
	}
};

//classe liste
template <typename TYPE>
class list
{
private:
	cell<TYPE> *_first;			//adresse du premier element

	list(const list<TYPE>& l);	//copieur de liste desactive
public:

	//classe iterateur
	class iterator
	{
		friend class list<TYPE>;
	private:
		cell<TYPE>		 *_current;		//adresse de la cellule
		const list<TYPE> *_list;		//adresse de la liste

	public:
		iterator();		//constructeurs
		~iterator();	//destructeur

		const iterator& operator=(const iterator& it);	//affectateur

		bool operator==(const iterator& it)const;	//comparateur positif
		bool operator!=(const iterator& it)const;	//comparateur negatif

		iterator operator++(int i);		//post-incrementeur
		const iterator& operator++();	//pre-incrementeur

		iterator operator--(int i);		//post-decrementeur
		const iterator& operator--();	//pre-decrementeur

		TYPE& operator*();				//dereferenceur mutateur
		const TYPE& operator*()const;	//dereferenceur accesseur
	};

	list(void);		//constructeurs
	~list(void);	//destructeur

	void clear();			//efface tout les elements
	bool empty()const;		//verifie si la liste est vide

	iterator begin()const;		//retourne le premier
	iterator end()const;		//retourne NULL

	iterator insert(iterator it, const TYPE& e);	//insert un element
	iterator erase(iterator it);					//efface un element
	iterator erase(iterator first, iterator last);	/*effece un element d'une
													position a une autre*/

	TYPE& operator[](iterator it);	//retourne ou modifie l'element a la position
	const TYPE& operator[](iterator it)const;	//retourne l'element a la position

	/*cherche dans la liste l'element recu en parametre
	et a partir de l'itetateur recu pour la version 2
	la methode retoune un iterateur sur l'element trouve
	s'il est innexistant l'iterateur est a la fin*/
	iterator operator()(const TYPE&)const;
	iterator operator()(const TYPE&, iterator)const;

	const list<TYPE>& operator=(const list<TYPE>& l);
};
/*	methodes de l'iterateur
****************************/

//constructeurs
template<typename TYPE>
list<TYPE>::iterator::iterator()
{
	_current = nullptr;
	_list = nullptr;
}

//destructeur
template<typename TYPE>
list<TYPE>::iterator::~iterator()
{
	_current = nullptr;
	_list = nullptr;
}

//affectateur
template<typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator=(const iterator& it)
{
	//copie l'explicite dans l'implicite
	_current = it._current;
	_list = it._list;

	return *this;
}

//comparateur positif
template<typename TYPE>
bool list<TYPE>::iterator::operator==(const iterator& it)const
{
	/*verifie que le pointeur compare est dans la meme liste
	puis compare l'element pointe*/
	assert(_list == it._list);

	return _current == it._current;
}

//comparateur negatif
template<typename TYPE>
bool list<TYPE>::iterator::operator!=(const iterator& it)const
{
	return !(operator==(it));
}

//post-incrementeur
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator++(int i)
{
	/*cree un iterateur temporaire pour retourner la
	cellule ou l'iterateur de la liste est actuellement
	appel l'operateur++ pour le deplacer sans affecter
	la cellule retournee*/
	iterator it(*this);
	operator++();
	return it;
}

//pre-incrementeur
template<typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator++()
{
	/*verifie que la liste n'est pas vide
	et que l'iterateur est initialise*/
	assert(_list != nullptr);
	assert(_current != nullptr);
	assert(!_list->empty());
	
	/*si la prochaine cellule est la fin, l'iterateur est deplace a la fin
	sinon il est deplace vers la cellule suivante*/
	if (_current->next == _list->_first)
		_current = nullptr;
	else
		_current = _current->next;

	return *this;
}

//post-decrementeur
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::iterator::operator--(int i)
{
	/*cree un iterateur temporaire pour retourner la
	cellule ou l'iterateur de la liste est actuellement
	appel l'operateur-- pour le deplacer sans affecter
	la cellule retourne*/
	iterator it(*this);
	operator--();
	return it;
}

//pre-decrementeur
template<typename TYPE>
typename const list<TYPE>::iterator& list<TYPE>::iterator::operator--()
{
	/*verifie que la liste n'est pas vide
	et que l'iterateur est initialise*/
	assert(_list != nullptr);
	assert(_current != _list->_first);
	assert(!_list->empty());
	
	/*si l'iterateur est a la fin, il est deplacer vers la derniere cellule
	sinon il est deplacer a la cellule precedente*/
	if (_current == nullptr)
		_current = _list->_first->prev;
	else
		_current = _current->prev;

	return *this;
}

//dereferenceur mutateur
template<typename TYPE>
TYPE& list<TYPE>::iterator::operator*()
{
	assert(!_list->empty());
	assert(_current != nullptr);
	return _current->element;
	///ne fonctionne pas
	//return operator*();
}

//dereferenceur accesseur
template<typename TYPE>
const TYPE& list<TYPE>::iterator::operator*()const
{
	assert(_list != nullptr);
	assert(!_list->empty());
	assert(_current != nullptr);
	return _current->element;
}

/*	methodes de la liste
 ****************************/

//constructeurs
template<typename TYPE>
list<TYPE>::list(void)
{
	_first = nullptr;
}

//destructeur
template<typename TYPE>
list<TYPE>::~list(void)
{
	clear();
}

//efface tout les elements
template<typename TYPE>
void list<TYPE>::clear()
{
	list<TYPE>::iterator it = begin();
	//efface du premier au dernier element
	while (it != end())
		erase(it++);
}

//verifie si la liste est vide
template<typename TYPE>
bool list<TYPE>::empty()const
{
	return _first == nullptr;
}

//retourne le premier
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin()const
{
	list<TYPE>::iterator it;	//iterateur

	//place l'iterateur sur la premiere cellule
	it._current = _first;
	it._list = this;

	return it;
}

//retourne NULL
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end()const
{
	list<TYPE>::iterator it;

	it._current = nullptr;
	it._list = this;

	return it;
}

//insert un element
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(iterator it, const TYPE& e)
{
	//verifie que l'iterateur est dans la bonne liste
	assert(it._list == this);

	//cree la premiere cellule avec le chainage approprie
	if (empty())
		_first->next = _first->prev = _first = new cell<TYPE>(e);
	//cree la deuxieme cellule avec le chainage approprie
	else if (it._current == nullptr)
		_first->prev = _first->prev->next = new cell<TYPE>(e, _first, _first->prev);
	else 
	{
		it._current->prev = it._current->prev->next = new cell<TYPE>(e, it._current, it._current->prev);

		//modifie le pointeur du premier element
		if (it._current == _first)
			_first = _first->prev;
	}

	//recule l'iterateur
	if (it._current == nullptr)
		it._current = _first->prev;
	else
		it._current = it._current->prev;

	return it;
}

//effece un element
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator it)
{
	/*verifie que l'iterateur est dans la bonne list
	qu'il positione et que la liste n'est pas vide*/
	assert(it._list == this);
	assert(it._current != nullptr);
	assert(!empty());

	cell<TYPE> *trash = it._current;

	//s'il ne reste qu'une seule cellule et que l'iterateur est dessus
	if (_first->next == _first)
	{
		_first = nullptr;
		it._current = nullptr;
	}
	else
	{
		//sinon on reorganise les pointeurs de cellule suivant et precedent
		it._current->prev->next = it._current->next;
		it._current->next->prev = it._current->prev;

		//si on efface la premiere cellule
		if (trash == _first)
			_first = _first->next;
		
		/*si on pointe sur la derniere cellule
		on recule l'iterateur sinon on l'avance*/
		if (trash == _first->prev)
			it--;
		else
			it++;
	}

	//supprime la cellule
	delete trash;
	trash = nullptr;

	return it;
}

//effece un element d'une position a une autre
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator first, iterator last)
{
	assert(last._list == this);

	if (first == begin() && last == end())
		clear();
	else
		while (first != last)
			first = erase(first);

	return first;
}

//retourne ou modifie l'element a la position
template<typename TYPE>
TYPE& list<TYPE>::operator[](iterator it)
{
	assert(it._list == this);
	return *it;
}

//retourne l'element a la position
template<typename TYPE>
const TYPE& list<TYPE>::operator[](iterator it)const
{
	assert(it._list == this);
	return *it;
}

//operateur de recherche
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& e)const
{
	return operator()(e, begin());
}

//operateur de recherche
template<typename TYPE>
typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& e, iterator it)const
{
	assert(it._list == this);

	for (it; it != end(); it++)
		if (*it == e)
			return it;

	return it;
}

//affectateur
template<typename TYPE>
const list<TYPE>& list<TYPE>::operator=(const list<TYPE>& l)
{
	//si l'adresse de l'implicite est la meme que celle de l'explicite
	if (this == &l)
		return *this;

	clear();

	list<TYPE>::iterator itExp = l.begin();

	//copie l'explicite dans l'implicite
	while (itExp != l.end())
		insert(end(), *itExp++);
	
	return *this;
}