#include "GestorOleadas.h"

// Constructor del gestor de oleadas.
GestorOleadas::GestorOleadas()
    : oleadas() {
}

// Agrega una nueva oleada al final de la cola.
void GestorOleadas::agregarOleada(const Oleada& oleada) {
    oleadas.push(oleada);
}

// Retorna y elimina la primera oleada de la cola.
// Si no existen oleadas pendientes, retorna una oleada vacia.
Oleada GestorOleadas::siguienteOleada() {
    if (oleadas.empty()) {
        return Oleada::generar(0);
    }

    Oleada siguiente = oleadas.front();
    oleadas.pop();

    return siguiente;
}

// Determina si existen oleadas pendientes en la cola.
bool GestorOleadas::hayOleadasPendientes() const {
    return !oleadas.empty();
}