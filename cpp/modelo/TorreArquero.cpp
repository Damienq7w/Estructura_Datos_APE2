#include "TorreArquero.h"

// Stats fijos al nacer: bajo danio, buen alcance: danio 10, alcance 3, costo 50.
TorreArquero::TorreArquero(const Coordenada& pos)
    : Torre(10, 3, 50, pos) {}

// Cada mejora suma +5 de danio y sube un nivel (el alcance no cambia).
void TorreArquero::mejorar() {
    nivel++;
    danio += 5;
}

std::string TorreArquero::getTipo() const {
    return "Arquero";
}