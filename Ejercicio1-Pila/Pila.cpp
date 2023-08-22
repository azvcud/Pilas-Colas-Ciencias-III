#include "Pila.h"
#include <string>

template<class T>
Pila<T>::Pila() {
	this -> head = nullptr;
	this -> tail = nullptr;
	this -> length = 0;
}

template<class T>
Pila<T>::~Pila() {
	
}

template<class T>
T Pila<T>::top() {
	if(tail != nullptr) { return tail -> value; }
	else				{ return 0; }
}

template<class T>
void Pila<T>::pop() {
	if(length == 1) {
		delete tail;
		delete head;
		tail = nullptr;
		head = nullptr;
		length--;
	}
	else if (length > 1) {
		node<T> *aux = new node<T>;
		aux = tail -> previous;
		
		delete tail;
		tail = aux;
		length--;
	}
}

template<class T>
void Pila<T>::push(T value) {
	node<T> *aux = new node<T>;
	aux -> value = value;
	aux -> previous = nullptr;
	aux -> next = nullptr;
	
	if(!length) { head = tail = aux; length++; }
	else
	{
		if(length == 1)	{ head -> next = aux; aux -> previous = head; }
		else			{ tail -> next = aux; aux -> previous = tail; }
		
		tail = aux;
		length++;
	}
}

template<class T>
bool Pila<T>::isEmpty() {
	return (tail == nullptr) && (head == nullptr);
}

template<class T>
int Pila<T>::size() {
	return length;
}

template<class T>
std::string Pila<T>::toString() {
	node<T> *aux = new node<T>;
	aux = tail;
	std::string text = "";
	
	while(aux != head) {
		text = text + "[" + aux -> value + "]\n";
		aux = aux -> previous;
	}
	if(!(tail == nullptr)) { text = text + "[" + aux -> value + "]"; }
	
	return text;
}







