#ifndef OLEADA_H
#define OLEADA_H

#include <vector>
#include "Cozy.h"

// Grupo de enemigos que se libera de una sola vez. La dificultad crece con
// el numero de oleada: mas enemigos y tipos mas fuertes en oleadas altas.
class Oleada {
private:
    const int numero;
    const std::vector<Cozy> enemigos;

    // Constructor privado: las oleadas se crean mediante el metodo generar().
    Oleada(int numero, const std::vector<Cozy>& enemigos);

    // Determina el tipo de enemigo que se generara segun la oleada
    // y la posicion que ocupa dentro del grupo.
    static int elegirTipo(int numero, int posicion);

public:
    // Genera una oleada completa de enemigos segun el numero de oleada.
    static Oleada generar(int numero);

    // Retorna la lista de enemigos pertenecientes a la oleada.
    const std::vector<Cozy>& getEnemigos() const;

    // Retorna el numero de la oleada.
    int getNumero() const;
};

#endif // OLEADA_H