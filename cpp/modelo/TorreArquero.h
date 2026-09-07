#ifndef TORRE_ARQUERO_H
#define TORRE_ARQUERO_H

#include "Torre.h"

// Torre de danio bajo pero buen alcance. Ideal para cubrir tramos largos
// de la ruta sin gastar mucho.
class TorreArquero : public Torre {
public:
    // pos: casilla donde se va a colocar. Los stats base (danio, alcance,
    // costo) los fija el constructor en el .cpp.
    explicit TorreArquero(const Coordenada& pos);

    // Sube de nivel y aumenta el danio.
    void mejorar() override;

    // Nombre que se muestra en el menu y en el mapa.
    std::string getTipo() const override;
};

#endif