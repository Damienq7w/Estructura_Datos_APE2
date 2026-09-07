#include "CatalogoEnemigos.h"

// Constructor de la plantilla de un tipo de enemigo.
CatalogoEnemigos::TipoEnemigo::TipoEnemigo(
    const std::string& nombre,
    int pvBase,
    int velocidad,
    int recompensa
)
    : nombre(nombre),
      pvBase(pvBase),
      velocidad(velocidad),
      recompensa(recompensa) {
}

// Lista fija de tipos de enemigo disponibles.
const CatalogoEnemigos::TipoEnemigo CatalogoEnemigos::TIPOS[3] = {
    {"Normal", 20, 1, 10},
    {"Rapido", 12, 2, 8},
    {"Tanque", 45, 1, 20}
};

// Escala el pv base segun el factor de dificultad (numero de oleada):
// pv = pvBase + 25% de pvBase por cada punto de factorDificultad.
Cozy CatalogoEnemigos::crear(int indiceTipo, int factorDificultad) {

    const TipoEnemigo& t = TIPOS[indiceTipo];

    int pvEscalado =
        t.pvBase + (t.pvBase * factorDificultad / 4);

    return Cozy(
        t.nombre,
        pvEscalado,
        t.velocidad,
        t.recompensa
    );
}