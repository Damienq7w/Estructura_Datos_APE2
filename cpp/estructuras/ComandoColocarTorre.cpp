#include "ComandoColocarTorre.h"

// Guarda la torre y el mapa; exitosa arranca en false porque todavia no
// se ha intentado colocar nada.
ComandoColocarTorre::ComandoColocarTorre(Torre* torre_, Mapa* mapa_)
    : torre(torre_), mapa(mapa_), exitosa(false) {}

// Le delega a Mapa::colocarTorre() el trabajo real, y guarda el
// resultado (true/false) para saber despues si hay que deshacer algo.
void ComandoColocarTorre::ejecutar() {
    exitosa = mapa->colocarTorre(torre);
}

// Solo quita la torre si de verdad se llego a colocar; si colocarTorre()
// fallo, no hay nada que deshacer.
void ComandoColocarTorre::deshacer() {
    if (exitosa) {
        mapa->quitarTorre(torre);
    }
}

bool ComandoColocarTorre::isExitosa() const { return exitosa; }
Torre* ComandoColocarTorre::getTorre() const { return torre; }
