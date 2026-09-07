#ifndef COMANDO_COLOCAR_TORRE_H
#define COMANDO_COLOCAR_TORRE_H

#include "ComandoTorre.h"
#include "Mapa.h"
#include "Torre.h"

// Comando que representa la accion "colocar esta torre en el mapa".
class ComandoColocarTorre : public ComandoTorre {
private:
    Torre* const torre;  // la torre que se quiere colocar
    Mapa* const mapa;     // en que mapa se coloca
    bool exitosa;          // si colocarTorre() tuvo exito o no

public:
    // Solo guarda las referencias; todavia no coloca nada (eso pasa en
    // ejecutar()).
    ComandoColocarTorre(Torre* torre, Mapa* mapa);

    // Intenta colocar la torre en el mapa y guarda si funciono.
    void ejecutar() override;

    // Si se llego a colocar, la quita de nuevo. Si nunca se pudo colocar
    // (casilla ocupada, sin espacio), no hace nada.
    void deshacer() override;

    // Para que quien creo el comando pueda revisar si funciono (por
    // ejemplo, para avisarle al jugador "no se pudo colocar la torre").
    bool isExitosa() const;
    Torre* getTorre() const;
};

#endif
