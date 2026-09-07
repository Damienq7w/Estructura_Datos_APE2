#include "CatalogoTorres.h"
#include "TorreArquero.h"
#include "TorreCanon.h"
#include <iostream>
#include <stdexcept>

// Constructor del struct: solo copia los datos que le pasan.
CatalogoTorres::TipoTorre::TipoTorre(std::string nombre_, int costo_, int danioBase_, int alcanceBase_)
    : nombre(std::move(nombre_)), costo(costo_), danioBase(danioBase_), alcanceBase(alcanceBase_) {}

// El orden aqui importa: la posicion 0 es "Arquero", la 1 es "Canon", y
// ese mismo numero es el que usa crear() (y el que escribe el jugador).
const std::vector<CatalogoTorres::TipoTorre> CatalogoTorres::TIPOS = {
    TipoTorre("Arquero", 50, 10, 3),
    TipoTorre("Canon",   90, 25, 2)
};

// Recorre TIPOS e imprime una linea por cada uno, con su indice al frente
// para que el jugador sepa que numero escribir en el menu.
void CatalogoTorres::mostrarOpciones() {
    for (size_t i = 0; i < TIPOS.size(); ++i) {
        const TipoTorre& t = TIPOS[i];
        std::cout << i << ") " << t.nombre << " - Costo: " << t.costo
                  << " | Danio: " << t.danioBase << " | Alcance: " << t.alcanceBase
                  << std::endl;
    }
}

// Traduce el indice elegido a la subclase concreta. Si el indice no
// corresponde a ningun tipo conocido, se lanza una excepcion en vez de
// devolver un puntero invalido.
Torre* CatalogoTorres::crear(int indiceTipo, const Coordenada& pos) {
    switch (indiceTipo) {
        case 0:
            return new TorreArquero(pos);
        case 1:
            return new TorreCanon(pos);
        default:
            throw std::invalid_argument("Indice de torre invalido: " + std::to_string(indiceTipo));
    }
}