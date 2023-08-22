#ifndef PILA_H
#define PILA_H
#include <string>

template<class T>
struct node {
	T value;
	node<T> *previous;
	node<T> *next;
};

template<class T>
class Pila {
public:
	Pila();
	~Pila();
	
	T top();
	void pop();
	void push(T value);
	bool isEmpty();
	int size();
	std::string toString();
private:
	node<T> *head;
	node<T> *tail;
	int length;
};


#endif
