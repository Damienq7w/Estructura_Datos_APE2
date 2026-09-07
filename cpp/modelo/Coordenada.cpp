#include "Coordenada.h"

#include <cmath>
#include <sstream>

// Constructor de la coordenada.
Coordenada::Coordenada(int fila, int columna)
    : fila(fila), columna(columna) {
}

// Retorna la fila de la coordenada.
int Coordenada::getFila() const {
    return fila;
}

// Retorna la columna de la coordenada.
int Coordenada::getColumna() const {
    return columna;
}

// Distancia Manhattan: se usa para decidir si un enemigo esta dentro
// del alcance de una torre (Torre.estaEnRango).
int Coordenada::distanciaA(const Coordenada& otra) const {
    return std::abs(fila - otra.fila) +
           std::abs(columna - otra.columna);
}

// Compara dos coordenadas para determinar si representan
// la misma posicion en el mapa.
bool Coordenada::operator==(const Coordenada& otra) const {
    return fila == otra.fila &&
           columna == otra.columna;
}

// Retorna la coordenada en formato de texto.
std::string Coordenada::toString() const {
    std::ostringstream salida;

    salida << "(" << fila << ", " << columna << ")";

    return salida.str();
}