#ifndef EQUILIBRADOSIMBOLOS_H
#define EQUILIBRADOSIMBOLOS_H

#include "Pila.cpp"
#include <string>

class EquilibradoSimbolos {
public:
	EquilibradoSimbolos();
	void equilibrarSimbolos(std::string cadena);
private:
	Pila<char> *caracteres;
	
	void digitarCadena();
	void mostrarPantalla();
};

#endif
