#include "TorreCanon.h"

// Stats fijos al nacer: alto danio, poco alcance: danio 25, alcance 2, costo 90.
TorreCanon::TorreCanon(const Coordenada& pos)
    : Torre(25, 2, 90, pos) {}

// Cada mejora suma +10 de danio (mas que el Arquero) y sube un nivel.
void TorreCanon::mejorar() {
    nivel++;
    danio += 10;
}

std::string TorreCanon::getTipo() const {
    return "Canon";
}