#include "Torre.h"

// Guarda los stats iniciales que le pasa la subclase y arranca en nivel 1.
Torre::Torre(int danio_, int alcance_, int costo_, const Coordenada& posicion_)
    : danio(danio_), alcance(alcance_), costo(costo_), nivel(1), posicion(posicion_) {}

// La torre alcanza al enemigo si la distancia entre ambas casillas es
// menor o igual que su alcance actual.
bool Torre::estaEnRango(const Coordenada& posEnemigo) const {
    return posicion.distanciaA(posEnemigo) <= alcance;
}

// Simplemente le pasa el danio de la torre al metodo recibirDano() del enemigo.
void Torre::atacar(Cozy& objetivo) const {
    objetivo.recibirDano(danio);
}

// Sobrescribe nivel/danio/alcance con los valores que le pasan (el
// "snapshot" que guardo ComandoMejorarTorre antes de mejorar).
void Torre::restaurar(int nivel_, int danio_, int alcance_) {
    this->nivel = nivel_;
    this->danio = danio_;
    this->alcance = alcance_;
}

int Torre::getDano() const { return danio; }
int Torre::getAlcance() const { return alcance; }
int Torre::getCosto() const { return costo; }
int Torre::getNivel() const { return nivel; }
const Coordenada& Torre::getPosicion() const { return posicion; }