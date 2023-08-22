#ifndef LISTA_H
#define LISTA_H

template <class T>
class nodoList {
	public:
		T dato;
		nodoList<T> *sig;
		
		nodoList(T dato);
};

template <class T>
nodoList<T>::nodoList(T dato) {
	this->dato = dato;
	sig = NULL;
}

template <class T>
class Lista {

	private:
		nodoList <T> *cab;
		nodoList <T> *col;
		int tam;

		void insertarPrimerDato(T dato);
	public:
		Lista();
		int getTam();
		bool isVacio();
		bool borrar(int);

		void insertarInicio(T dato);
		void insertarFinal(T dato);
		void insertar(T, int);

		T buscar (int pos);
		bool modificar(T infoNueva,int pos);

		void mostrarEstado();
};

template<class T>
void Lista<T>::mostrarEstado() {
	std::cout<<"========\n";
	std::cout<<"Tamano: "<<tam<<"\n";
	std::cout<<"Datos: ";

	nodoList<T> *aux = cab;

	if(aux == NULL) {
		std::cout<<"Vacio.";
	}
	while(aux != NULL) {
		std::cout<<aux->dato<<" ";
		aux = aux->sig;
	}

	std::cout<<"\n";

}

template<class T>
Lista<T>::Lista() {
	cab = NULL;
	col = NULL;
	tam = 0;
}

template<class T>
int Lista<T>::getTam() {
	return tam;
}

template<class T>
bool Lista<T>::isVacio() {
	return cab == NULL;
}

template<class T>
bool Lista<T>::borrar(int pos) {
	if(pos >= tam || isVacio() || pos < 0 ) {
		return false;
	}

	tam--;

	if(tam == 0) {
		col = NULL;
	}

	// Caso especial eliminacion primer elemento
	if(pos == 0) {
		nodoList<T> *sig = cab->sig;
		delete cab;
		cab = sig;
		return true;
	}


	nodoList<T> *aux = cab;
	for (int i = 1; i < pos; i++) { // Deja a aux en la posicion anterior a la que se va a borar
		aux = aux->sig;
	}

	// Caso especial eliminacion del ultimo elemento
	if(pos == tam) { // No es tam-1 porque al inicio se hizo tam--
		delete aux->sig;
		aux->sig = NULL;
		col = aux;
		return true;
	}

	nodoList<T> *nuevoSiguiente = aux->sig->sig;
	delete aux->sig;
	aux->sig = nuevoSiguiente;
	return true;
}

template <class T>
void Lista<T>::insertarPrimerDato(T dato) {
	nodoList<T> *primerDato = new nodoList<T>(dato);
	col = cab = primerDato;
	tam++;
}

template <class T>
void Lista<T>::insertarInicio(T dato) {

	if(isVacio()) {
		insertarPrimerDato(dato);
		return;
	}

	nodoList<T> *nuevoDato = new nodoList<T>(dato);
	nuevoDato->sig = cab;
	cab = nuevoDato;
	tam++;

	if(tam == 1) {
		col = cab;
	}
}


template <class T>
void Lista<T>::insertarFinal(T dato) {

	if(isVacio()) {
		insertarPrimerDato(dato);
		return;
	}

	nodoList<T> *nuevoDato = new nodoList<T>(dato);
	col->sig = nuevoDato;
	col = nuevoDato;
	tam++;

	if(tam == 1) {
		cab = col;
	}
}


template <class T>
void Lista<T>::insertar(T dato, int pos) {
	if (pos > tam-1) {
		insertarFinal(dato);
		return;
	}

	else if(pos == 0) {
		insertarInicio(dato);
		return;
	}

	nodoList<T> *aux = cab;

	for (int i = 0; i < pos-1; i++) { // Deja a aux en la posicion anterior a la que se va a insertar
		aux = aux->sig;
	}

	nodoList<T> *aInsertar = new nodoList<T>(dato);
	aInsertar->sig = aux->sig;
	aux->sig = aInsertar;

	tam++;
}

template <class T>
T Lista<T>::buscar(int pos) {
	if(isVacio()) {
		T objVacio;
		return objVacio;
	}

	if(pos > tam-1) {
		T objVacio;
		return objVacio;
	}

	nodoList<T> *aux = cab;
	for (int i = 0; i < pos; i++) {
		aux = aux->sig;
	}

	return aux->dato;

}

template <class T>
bool Lista<T>::modificar(T infoNueva,int pos) {
	if(isVacio() || pos < 0 || pos > tam-1) {
		return false;
	}

	nodoList<T> *aux = cab;
	for (int i = 0; i < pos; i++) {
		aux = aux->sig;
	}

	aux->dato = infoNueva;
	return true;
}

#endif