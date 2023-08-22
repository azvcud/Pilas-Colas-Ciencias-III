#ifndef QUEUE_H
#define QUEUE_H

template <class T>
struct nodo {
    T dato;
    nodo<T> *der = 0, *izq = 0;

    nodo() { };
    nodo(T dato){
        this->dato = dato;
    };
};

/*
Cola que permite insertar y atender por dos las
el lado se especifica en los metodos de enqueue o
dequeue.
 0: -> izquierda
 1: <- derecha
*/
template <class T>
class Queue {
    private:
        // centinelas
        nodo<T> *cab, *fin;
		int _tamano = 0;

    public:
        static const int IZQ = 0;
        static const int DER = 1;

        Queue();
        ~Queue();
		int tamano();
        bool queue_vacia();
        void enqueue (int lado, T nuevo);
        T dequeue (int lado);
        void estado();

};

template <class T>
void Queue<T>::estado(){

}

template <class T>
Queue<T>::Queue(){
    cab = new nodo<T>;
    fin = new nodo<T>;

    cab->der = fin;
    fin->izq = cab;
}

template <class T>
Queue<T>::~Queue(){
    nodo<T> *aux = cab;
    while (aux->der != 0)
    {
        aux = aux->der;
        delete aux->izq;
    }
    delete fin;
}

template<class T>
int Queue<T>::tamano(){
	return _tamano;
}
	
template <class T>
bool Queue<T>::queue_vacia(){
    return cab->der == fin;
}

/**
 * lado = 0 -> izquierda
 * lado = 1 -> derecha
 * Se inserta en el lado indicado
*/
template <class T>
void Queue<T>::enqueue(int lado, T nuevo){
    if(lado != 0 && lado != 1){
        return;
    }

    nodo<T> *nuevoNodo = new nodo<T>(nuevo);
    _tamano++;

    if(lado == 1){
        nuevoNodo->der = fin;
        nuevoNodo->izq = fin->izq;
        fin->izq->der = nuevoNodo;
        fin->izq = nuevoNodo;
    }
    else {
        nuevoNodo->izq = cab;
        nuevoNodo->der = cab->der;
        cab->der->izq = nuevoNodo;
        cab->der = nuevoNodo;
    }
}

/**
 * lado = 0 -> izquierda
 * lado = 1 -> derecha
 * Se atiende por el lado indicado
*/
template <class T>
T Queue<T>::dequeue(int lado){
    T dato;

    if( (lado != 0 && lado != 1) || this->queue_vacia()){
        return dato;
    }

    _tamano--;
    if(lado == 0){
        nodo<T> *extraccion = cab->der;
        cab->der = extraccion->der;
        extraccion->der->izq = cab;
        dato = extraccion->dato;
        delete extraccion;
    }
    else {
        nodo<T> *extraccion = fin->izq;
        fin->izq = extraccion->izq;
        extraccion->izq->der = fin;
        dato = extraccion->dato;
        delete extraccion;
    }

    return dato;
}



#endif
