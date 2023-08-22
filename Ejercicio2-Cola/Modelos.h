#ifndef MODELOS_H
#define MODELOS_H

#include <cstring>
#include "Queue.h"
#include <sstream>

class Tarea {
	
	private:
	int id;
	static int ultimaId;
	
	public:
	int tiempo;

	Tarea(bool instanciaReal = false, int tiempo = 0){
		if(instanciaReal){
			this->id = ++ultimaId;
			this->tiempo = tiempo;
		}
		else{
			id = 0;
			this->tiempo = 0;
		}
	}

	int getId(){
		return id;
	}
};

int Tarea::ultimaId = 0;

/*
Esta clase usa una cola como si fuera simple,
así las tareas entran por la izquierda y salen
por la derecha
*/
class Procesador {
	private:
	int id, tiempoPendiente = 0;
	Queue<Tarea> tareas;

	public:

	Procesador(int id=0){
		this->id = id;
	}

	void agregarTarea(Tarea t){
		tiempoPendiente += t.tiempo;
		tareas.enqueue(0, t);
	}

	Tarea realizarTarea(){
		Tarea realizada = tareas.dequeue(1);
		tiempoPendiente -= realizada.tiempo;
		return realizada;
	}

	int getTiempo(){
		return tiempoPendiente;
	}

	std::string getTareas(){
		std::stringstream ss;
		for(int i=0; i<tareas.tamano(); i++){
			Tarea t = tareas.dequeue(0);
			ss<<"Tarea(id: "<<t.getId()<<" t:"<<t.tiempo<<") ";
			tareas.enqueue(1, t);
		}
		return ss.str();
	}
};


#endif
