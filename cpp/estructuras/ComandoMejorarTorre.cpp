#include "ComandoMejorarTorre.h"

// nivelAnterior/danioAnterior/alcanceAnterior arrancan en 0 porque recien
// se van a llenar de verdad cuando se llame a ejecutar().
ComandoMejorarTorre::ComandoMejorarTorre(Torre* torre_)
    : torre(torre_), nivelAnterior(0), danioAnterior(0), alcanceAnterior(0) {}

// Primero saca una "foto" de los stats actuales (por si hay que
// deshacer despues), y recien ahi llama a mejorar().
void ComandoMejorarTorre::ejecutar() {
    nivelAnterior = torre->getNivel();
    danioAnterior = torre->getDanio();
    alcanceAnterior = torre->getAlcance();
    torre->mejorar();
}

// Le pasa a la torre los valores guardados en el snapshot, dejandola
// exactamente como estaba antes de mejorar().
void ComandoMejorarTorre::deshacer() {
    torre->restaurar(nivelAnterior, danioAnterior, alcanceAnterior);
}