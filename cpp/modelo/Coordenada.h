#ifndef COORDENADA_H
#define COORDENADA_H

#include <string>

class Coordenada {
private:
    const int fila;
    const int columna;

public:
    // Constructor de la coordenada.
    Coordenada(int fila, int columna);

    // Retorna la fila de la coordenada.
    int getFila() const;

    // Retorna la columna de la coordenada.
    int getColumna() const;

    // Distancia Manhattan: se usa para decidir si un enemigo esta dentro
    // del alcance de una torre (Torre.estaEnRango).
    int distanciaA(const Coordenada& otra) const;

    // Compara dos coordenadas para determinar si representan
    // la misma posicion en el mapa.
    bool operator==(const Coordenada& otra) const;

    // Retorna la coordenada en formato de texto.
    std::string toString() const;
};

#endif // COORDENADA_H