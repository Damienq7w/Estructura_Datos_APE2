#ifndef COMANDO_MEJORAR_TORRE_H
#define COMANDO_MEJORAR_TORRE_H

#include "ComandoTorre.h"
#include "Torre.h"

// Comando que representa la accion "mejorar esta torre". Guarda una
// "foto" (snapshot) de como estaba la torre antes de mejorar, para poder
// devolverla exactamente a ese estado si se deshace.
class ComandoMejorarTorre : public ComandoTorre {
private:
    Torre* const torre;
    int nivelAnterior;
    int danioAnterior;
    int alcanceAnterior;

public:
    // Todavia no guarda el snapshot: eso se hace en ejecutar(), justo
    // antes de mejorar.
    explicit ComandoMejorarTorre(Torre* torre);

    // Guarda como estaba la torre y luego la mejora.
    void ejecutar() override;

    // Devuelve la torre al estado que tenia justo antes de mejorar().
    void deshacer() override;
};

#endif