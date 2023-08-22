#include <iostream>
#include "Queue.h"
#include "Lista.h"
#include "Modelos.h"
using namespace std;

void agregarTarea(Lista<Tarea> *, int &);
float asignarTareas(Procesador *, Queue<Tarea> *, int, int);
void mostrarProcesadores(Procesador *, int);
void empaquetarTareas(Lista<Tarea> *, Queue<Tarea>*);

int mostrarMenuPrincipal()
{
	cout << "========= Gestion de tareas =========\n";
	cout << "Elija la siguiente accion:\n";
	cout << "  (1) Agregar una tarea\n";
	cout << "  (2) Eliminar una tarea\n";
	cout << "  (3) Ver tareas\n";
	cout << "  (4) Realizar tareas\n";
	cout << "  (0) Salir\n";
	cout << "--> ";
	int op;
	cin >> op;
	return op;
}

/**
 * Lista las tareas existentes
 * Retorna el numero de tareas existentes
*/
int listarTareas(Lista<Tarea> *listaTareas)
{
	if (listaTareas->isVacio())
	{
		cout << "  No existen tareas.\n";
		return 0;
	}
	else
	{
		int i=0;
		for(i=0; i<listaTareas->getTam(); i++){
			Tarea t = listaTareas->buscar(i);
			cout<<"    "<<i+1<<". Id:"<<t.getId()<<" tiempo: "<<t.tiempo<<endl;
		}
		return i+1;
	}
}

int main(int argc, char *argv[])
{

	Lista<Tarea> *listaTareas = new Lista<Tarea>;
	int nProcesadores, tiempoTotal = 0;

	bool encendido = true;
	while (encendido)
	{
		int op = mostrarMenuPrincipal();
		switch (op)
		{
		case 1:
			agregarTarea(listaTareas, tiempoTotal);
			break;
		case 2:
			{
				int nTareas = listarTareas(listaTareas);
				if(nTareas != 0){
					int aEliminar;
					cout<<"  Ingrese el indice de la tarea: ";
					cin>>aEliminar;
					if(aEliminar <= 0 || aEliminar > nTareas){
						cout<<"  Opcion invalida.\n";
						continue;
					}
					tiempoTotal-=listaTareas->buscar(aEliminar-1).tiempo;
					listaTareas->borrar(aEliminar-1);
				}
			}
			break;
		case 3:
			cout<<"  Tareas existentes:\n";
			listarTareas(listaTareas);
			break;
		case 4:
			{
				if(listaTareas->isVacio()){
					cout<<"  No hay tareas.\n";
					continue;
				}
				cout<<"  ingrese el numero de procesadores: ";
				cin>>nProcesadores;
				Procesador procesadores[nProcesadores];
				Queue<Tarea> *tareas = new Queue<Tarea>;
				empaquetarTareas(listaTareas, tareas);
				float tIdeal = asignarTareas(procesadores, tareas, nProcesadores, tiempoTotal);
				cout<<"  Tiempo ideal para cada procesador: "<<tIdeal<<endl;
				mostrarProcesadores(procesadores, nProcesadores);
				delete tareas;
				break;
			}
		case 0:
			encendido = false;
			break;

		default:
			cout<<"Opcion incorrecta.\n";
		}
	}

	delete listaTareas;

	return 0;
}

void empaquetarTareas(Lista<Tarea> *listaTareas, Queue<Tarea> *cola ){
	// Ordena las tareas por tiempo:
	Lista<Tarea> *listaOrdenada = new Lista<Tarea>;
	listaOrdenada->insertarFinal(listaTareas->buscar(0)); // Ya se verificó que no esté vacia en el switch
	int tamano = listaTareas->getTam();
	for(int i=1; i < tamano; i++){
		Tarea elem = listaTareas->buscar(i);
		int j=0;
		for(j=0; j<listaOrdenada->getTam(); j++){
			if(elem.tiempo <= listaOrdenada->buscar(j).tiempo){
				break;
			}
		}
		listaOrdenada->insertar(elem, j);
	}

	for(int i=0; i<listaOrdenada->getTam(); i++){
		// ordenada la lista, los pequeños irán al inicio
		// insertando a la izquierda en la cola los más pequeños quedan
		// a la derecha y por ende los más grandes a la izquierda
		cola->enqueue(0, listaOrdenada->buscar(i));
	}
	delete listaOrdenada;
}

void agregarTarea(Lista<Tarea> *lista, int &tiempoTotal)
{
	cout << "  AGREGAR TAREA.\n";
	int tiempo;
	cout << "  Ingrese la duracion de la tarea: ";
	cin >> tiempo;
	if(tiempo <= 0){
		cout<<"  tiempo invalido.\n";
	}
	else{
		Tarea t(true, tiempo);
		lista->insertarFinal(t);
		tiempoTotal += t.tiempo;
	}
}

/**
 * Decide cual será el siguiente procesador en el que insertar datos
 * avanzar representa seguir hacia la derecha
 * no avanzar representa retroceder, en direccion la direccion izquierda
*/
void siguienteProcesador(int &indActual, int nProcesadores, bool &avanzar){
	indActual += (avanzar ? 1 : -1);
	if(indActual < 0){
		indActual = 1;
		avanzar = true;
	}
	else if(indActual >= nProcesadores){
		indActual = nProcesadores-2;
		avanzar = false;
	}
	indActual %= nProcesadores; // Evita salirse del rango
}

float asignarTareas(Procesador *procesadores, Queue<Tarea> *tareas, int nProcesadores, int tiempoTotal)
{
	// Tiempo ideal en el que todos los procesadores tienen el mismo tiempo
	float tiempoIdeal = tiempoTotal / float(nProcesadores);
	// Cuando un procesador sobrepasa el tiempo ideal, el tiempo objetivo debe cambiar
	float tiempoIdealTrabajo = tiempoTotal / float(nProcesadores);

	int indProcesador = 0;			// Iterador para los procesadores
	int tareasSinAsignar = 0;		// Cuenta cuantos ciclos sin asignar una tarea han pasado
	int procesadoresSinAsingar = 0; // Cuanta las veces que se ha cambiado de procesador porque el
									// anterior no fue apto para recibir una tarea
	bool avanzar = true; // dependencia de siguienteProcesador(...)
	while (!tareas->queue_vacia())
	{ /* tareas.tamano() > nProcesadores &&  ??*/
		Tarea t = tareas->dequeue(0);

		if (procesadoresSinAsingar >= nProcesadores)
		{
			/* Ninguno de los procesadores es candidato para agregar
			tareas sin superar el tiempo ideal
			*/
			procesadores[indProcesador].agregarTarea(t);
			tiempoIdealTrabajo = ( tiempoIdealTrabajo*float(nProcesadores)-procesadores[indProcesador].getTiempo() )
									/float(nProcesadores);
			siguienteProcesador(indProcesador, nProcesadores, avanzar);
			tareasSinAsignar = procesadoresSinAsingar = 0;
			// indProcesador = (indProcesador + 1) % nProcesadores;
			continue;
		}
		else if (tareasSinAsignar >= tareas->tamano() + 1)
		{
			// Procesador actual no es apto para ninguna tarea, pasa al siguiente procesador
			indProcesador = (indProcesador + 1) % nProcesadores;
			procesadoresSinAsingar++;
			tareasSinAsignar = 0;
		}

		if(t.tiempo > tiempoIdealTrabajo){
			procesadores[indProcesador].agregarTarea(t);
			siguienteProcesador(indProcesador, nProcesadores, avanzar);
			tareasSinAsignar = procesadoresSinAsingar = 0;
			tiempoIdealTrabajo = ( tiempoIdealTrabajo*float(nProcesadores)-procesadores[indProcesador].getTiempo() )
									/float(nProcesadores);
		}
		else if (procesadores[indProcesador].getTiempo() + t.tiempo <= tiempoIdealTrabajo)
		{
			procesadores[indProcesador].agregarTarea(t);
			siguienteProcesador(indProcesador, nProcesadores, avanzar);
			tareasSinAsignar = procesadoresSinAsingar = 0;
		}
		else
		{
			// La tarea no fue apta para asignar, vuelve al final de la fila
			tareas->enqueue(1, t);
			tareasSinAsignar++;
		}
	}

	return tiempoIdeal;
}

void mostrarProcesadores(Procesador *procesadores, int tamProcesadores)
{
	cout << "  $$$ Proceso para realizar tareas $$$\n\n";
	for (int i = 0; i < tamProcesadores; i++)
	{
		cout << "  Procesador #" << i+1 << " total:" << procesadores[i].getTiempo()
			 << " [ " << procesadores[i].getTareas() << "]\n";
	}
}
