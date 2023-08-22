#include "EquilibradoSimbolos.h"
#include "Pila.h"
#include <iostream>

EquilibradoSimbolos::EquilibradoSimbolos() {
	this -> caracteres = new Pila<char>;
	digitarCadena();
}

void EquilibradoSimbolos::digitarCadena() {
	std::string cadenaIngresar;
	
	std::cout<<"Bienvenido al verificador de sintáxtis. Por favor escriba la cadena a evaluar. \nEj. ([4+2]+4)\n\n";
	std::cin >> cadenaIngresar;
	system("cls");
	EquilibradoSimbolos::equilibrarSimbolos(cadenaIngresar);
}

void EquilibradoSimbolos::equilibrarSimbolos(std::string cadena) {
	char caracter;
	bool syntaxError = false;
	
	for(unsigned int i = 0; i < cadena.size(); i++) {
		std::cout<<cadena.substr(0, i)<<"\n";
		caracter = cadena[i];
			
		bool opcion1[3] = {
			caracter == '(', 
			caracter == '[', 
			caracter == '{'
		};
		
		bool opcion2[3] = {
			caracter == ')',
			caracter == ']',
			caracter == '}',
		};
		
		bool opcion3[3] = {
			caracteres -> top() == '(',
			caracteres -> top() == '[',
			caracteres -> top() == '{',
		};
	
		if(opcion1[0] || opcion1[1] || opcion1[2]) {
			caracteres -> push(caracter);
			EquilibradoSimbolos::mostrarPantalla();
		}
		
		if(opcion2[0] || opcion2[1] || opcion2[2]) {
			if((opcion3[0] && opcion2[0]) || (opcion3[1] && opcion2[1]) || (opcion3[2] && opcion2[2])) {
				caracteres -> pop();
				EquilibradoSimbolos::mostrarPantalla();
			} 
			else { 
				std::cout<<"\nError de sintáxtis.\n";
				syntaxError = true;
				break;
			}
		}
	}
	
	if(!caracteres -> isEmpty())	{ std::cout<<"Error: Cola no vacía.\n\n"; syntaxError = true; }
	if(syntaxError == false)		{ std::cout<<"La expresión "<<cadena<<" es válida.\n\n"; }
	system("pause");
}

void EquilibradoSimbolos::mostrarPantalla() {
	std::cout<<"\n"<<caracteres -> toString()<<"\n";
	system("pause");
	system("Cls");
}
