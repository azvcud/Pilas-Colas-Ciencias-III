#include <iostream>
#include <cstdlib>
#include "Pila.cpp"

using namespace std;


void equilibrarSimbolos(std::string);


int main (int argc, char *argv[]) {
	std::string cadena = "{[4+((3*3)-2)+(2-5)]}";
	
	equilibrarSimbolos(cadena);
	return 0;
}

void equilibrarSimbolos(std::string cadena) {
	Pila<char> caracteres;
	
	for(unsigned int i = 0; i < cadena.size(); i++) {
		char caracter = cadena[i];
		
		if(caracter == '(' || caracter == '[' || caracter == '{') {
			caracteres.push(caracter);
			cout<<caracteres.toString()<<endl;
			system("pause");
			system("Cls");
		}
		
		if(caracter == ')' && caracteres.top() == '(') {
			caracteres.pop();
			cout<<caracteres.toString()<<endl;
			system("pause");
			system("Cls");
		}
		else if(caracter == ']' && caracteres.top() == '[') {
			caracteres.pop();
			cout<<caracteres.toString()<<endl;
			system("pause");
			system("Cls");
		}
		else if(caracter == '}' && caracteres.top() == '{') {
			caracteres.pop();
			cout<<caracteres.toString()<<endl;
			system("pause");
			system("Cls");
		}
		else if(caracteres.isEmpty()){
			cout<<"Error de sintáxtis."<<endl;
		}
	}
	
	cout<<"Sintáxis correcta."<<endl;
}
