#include "Cozy.h"

#include <algorithm>

// Constructor que inicializa las caracteristicas principales del enemigo.
Cozy::Cozy(const std::string& tipo, int pvMax, int velocidad, int recompensa)
    : tipo(tipo),
      pv(pvMax),
      pvMax(pvMax),
      indiceRuta(0),
      velocidad(velocidad),
      recompensa(recompensa) {
}

// Nunca deja el pv negativo, asi estaVivo() queda bien definido con pv > 0.
void Cozy::recibirDano(int dano) {
    pv = std::max(0, pv - dano);
}

// Determina si el enemigo continua con puntos de vida.
bool Cozy::estaVivo() const {
    return pv > 0;
}

// Incrementa la posicion del enemigo dentro de la ruta
// de acuerdo con su velocidad.
void Cozy::avanzar() {
    indiceRuta += velocidad;
}

// "-1" porque el ultimo indice valido de la ruta es longitudRuta - 1
// (la fuente de energia).
bool Cozy::llegoAlFinal(int longitudRuta) const {
    return indiceRuta >= longitudRuta - 1;
}

// Retorna el tipo de enemigo.
const std::string& Cozy::getTipo() const {
    return tipo;
}

// Retorna los puntos de vida actuales del enemigo.
int Cozy::getPv() const {
    return pv;
}

// Retorna los puntos de vida maximos del enemigo.
int Cozy::getPvMax() const {
    return pvMax;
}

// Retorna el indice actual del enemigo dentro de la ruta.
int Cozy::getIndiceRuta() const {
    return indiceRuta;
}

// Retorna la velocidad de movimiento del enemigo.
int Cozy::getVelocidad() const {
    return velocidad;
}

// Retorna la recompensa otorgada al eliminar al enemigo.
int Cozy::getRecompensa() const {
    return recompensa;
}