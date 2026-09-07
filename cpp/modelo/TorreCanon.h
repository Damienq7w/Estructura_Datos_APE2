#ifndef TORRE_CANON_H
#define TORRE_CANON_H

#include "Torre.h"

// Torre de danio alto pero poco alcance. Sirve para "rematar" enemigos
// cerca de tramos concretos de la ruta.
class TorreCanon : public Torre {
public:
    explicit TorreCanon(const Coordenada& pos);

    void mejorar() override;
    std::string getTipo() const override;
};

#endif