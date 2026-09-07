#ifndef HISTORIAL_COMANDOS_H
#define HISTORIAL_COMANDOS_H

#include <stack>
#include "ComandoTorre.h"

// Lleva el historial de deshacer/rehacer usando dos pilas de comandos
// (patron Command + Undo/Redo). En Java se usa Deque<ComandoTorre>
// (ArrayDeque); aqui se pide explicitamente std::stack, que ofrece la
// misma operacion push/pop/top que se necesita.
class HistorialComandos {
private:
    std::stack<ComandoTorre*> pilaDeshacer; // comandos que se pueden deshacer
    std::stack<ComandoTorre*> pilaRehacer;   // comandos que se acaban de deshacer

    // std::stack no tiene un metodo clear(), asi que esta funcion la
    // vacia a mano: va sacando el tope y borrando el comando (en Java
    // pilaRehacer.clear() bastaba porque el recolector de basura se
    // encarga; en C++ hay que liberar la memoria nosotros mismos).
    static void vaciar(std::stack<ComandoTorre*>& pila);

public:
    // Al destruirse, libera cualquier comando que haya quedado pendiente
    // en cualquiera de las dos pilas (para no dejar fugas de memoria).
    ~HistorialComandos();

    // Se llama justo despues de ejecutar() un comando nuevo: lo agrega
    // al tope de la pila de deshacer y borra la pila de rehacer, porque
    // una accion nueva invalida cualquier "rehacer" que estuviera pendiente.
    void registrar(ComandoTorre* c);

    // Saca el comando del tope de pilaDeshacer, le pide que se deshaga,
    // y lo pasa a pilaRehacer por si se quiere rehacer despues.
    // Ojo: hay que revisar puedeDeshacer() antes de llamar a esto, o
    // se intenta sacar el tope de una pila vacia (igual que en Java,
    // donde eso lanzaria NoSuchElementException).
    void deshacer();

    // Lo mismo que deshacer() pero al reves: saca de pilaRehacer, vuelve
    // a ejecutar el comando, y lo regresa a pilaDeshacer.
    void rehacer();

    // Para que quien llama pueda preguntar antes si hay algo que
    // deshacer/rehacer, y asi evitar el problema de la pila vacia.
    bool puedeDeshacer() const;
    bool puedeRehacer() const;
};

#endif
