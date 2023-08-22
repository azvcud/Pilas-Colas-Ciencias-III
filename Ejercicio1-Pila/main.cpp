#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "EquilibradoSimbolos.h"

using namespace std;


void equilibrarSimbolos(std::string);


int main (int argc, char *argv[]) {
	//Inicializar configuración de teclado en Español - Latinoamérica
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	EquilibradoSimbolos *cadenaEvaluar = new EquilibradoSimbolos();
	return 0;
}

