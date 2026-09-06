#ifndef CATALOGO_ENEMIGOS_H
#define CATALOGO_ENEMIGOS_H

#include <string>
#include "Cozy.h"

// Catalogo que contiene los tipos de enemigo disponibles
// y permite crear instancias de Cozy a partir de sus caracteristicas.
class CatalogoEnemigos {
public:

    // Plantilla de un tipo de enemigo (stats base, antes de escalar por dificultad).
    struct TipoEnemigo {
        std::string nombre;
        int pvBase;
        int velocidad;
        int recompensa;

        // Constructor de la plantilla de un tipo de enemigo.
        TipoEnemigo(
            const std::string& nombre,
            int pvBase,
            int velocidad,
            int recompensa
        );
    };

    // Lista fija de tipos de enemigo disponibles.
    static const TipoEnemigo TIPOS[3];

    // Escala el pv base segun el factor de dificultad (numero de oleada):
    // pv = pvBase + 25% de pvBase por cada punto de factorDificultad.
    static Cozy crear(int indiceTipo, int factorDificultad);
};

#endif // CATALOGO_ENEMIGOS_H