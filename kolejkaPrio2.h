#ifndef KOLEJKAPRIO_HH
#define KOLEJKAPRIO_HH

#include <iostream>
#include <cassert>

class node
{
    int unit; //element
    int unit1;
    int prio; //priorytet
    friend class prioQueue;
    public:
	void operator=(node data)
    {
		this->unit=data.unit;
		this->unit1=data.unit1;
		this->prio=data.prio;
	}
    friend std::ostream& operator << (std::ostream& out, const node& data)
	{
		out<<data.unit<<"->"<<data.unit1<<": "<<data.prio;
		return out;
	}
};

//kolejka priorytetowa na kopcu, korzen ma najmniejszy priorytet
class prioQueue
{
	int size; //rozmiar
	node* tab; //tablica do kopca

	public:
	prioQueue(int n){tab=new node[n]; size=0;}
	// wstawia element b o prorytecie c
	void push(int b, int d, int c)
	{
		node a;
		a.unit=b;
		a.unit1=d;
		a.prio=c;
		int v=a.prio;
		int i,j;
		i = size;
		j = (i - 1) / 2;
		size++;

		while(i > 0 && tab[j].prio < v)
		{
			tab[i] = tab[j];
			i = j;
			j = (i - 1) / 2;
		}

        tab[i] = a;
	}
	// usuwa z kopca korzen
	void pop()
	{
		int i,j,v;
		if(size)
		{
			size--;
			v = tab[size].prio;

			i = 0;
			j = 1;

			while(j < size)
			{
			if(j + 1 < size && tab[j + 1].prio > tab[j].prio) j++;
			if(v >= tab[j].prio) break;
			tab[i] = tab[j];
			i = j;
			j = 2 * j + 1;
			}
		tab[i] = tab[size];
		}
	}
	// usuwa wszystkie ele kopca
	void popAll()
	{
		this->size=0;
	}
	// zwraca korzen kopca bez priorytetu
	int indexPown()
	{
		return tab[0].unit;
	}
        // zwraca korzen kopca bez priorytetu
	int indexMove()
	{
		return tab[0].unit1;
	}
	// zwraca rozmiar kopca
	const int heapSize()
	{
		return this->size;
	}
	// zwraca wybrany element kopca
	const node operator()(int a)
	{
		return this->tab[a];
	}
};

#endif

