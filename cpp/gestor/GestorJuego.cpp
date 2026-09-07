#include "GestorJuego.h"

#include <algorithm>
#include <iostream>

#include "../estructuras/ColaEnemigos.h"
#include "../estructuras/GestorOleadas.h"
#include "../estructuras/HistorialComandos.h"
#include "../estructuras/Mapa.h"
#include "../estructuras/ComandoColocarTorre.h"
#include "../estructuras/ComandoMejorarTorre.h"
#include "../modelo/Cozy.h"
#include "../modelo/Oleada.h"
#include "../modelo/Torre.h"

GestorJuego::GestorJuego(int vidaInicial, ColaEnemigos& colaEnemigos_, GestorOleadas& gestorOleadas_,
                         HistorialComandos& historial_, Mapa& mapa_)
    : vidaJugador(vidaInicial),
      puntuacion(0),
      oleadaActual(0),
      colaEnemigos(colaEnemigos_),
      gestorOleadas(gestorOleadas_),
      historial(historial_),
      mapa(mapa_) {
}

// Si ya no quedan enemigos en ruta, carga la siguiente oleada pendiente
// antes de procesar el quantum actual.
void GestorJuego::procesarQuantum() {
    if (colaEnemigos.estaVacia() && gestorOleadas.hayOleadasPendientes()) {
        Oleada siguiente = gestorOleadas.siguienteOleada();
        oleadaActual = siguiente.getNumero();
        for (const Cozy& c : siguiente.getEnemigos()) {
            colaEnemigos.encolar(c);
        }
    }
    colaEnemigos.actualizarQuantum(mapa, *this);
}

void GestorJuego::restarVida(int cantidad) {
    vidaJugador = std::max(0, vidaJugador - cantidad);
}

void GestorJuego::sumarPuntaje(int cantidad) {
    puntuacion += cantidad;
}

// Crea el comando, lo ejecuta y solo lo registra en el historial si la
// colocacion fue exitosa. Si fallo (casilla ocupada o sin espacio) el
// comando no sirve para deshacer, asi que se libera aqui mismo.
bool GestorJuego::colocarTorreJugador(Torre* t) {
    ComandoColocarTorre* comando = new ComandoColocarTorre(t, &mapa);
    comando->ejecutar();
    if (comando->isExitosa()) {
        historial.registrar(comando);
        return true;
    }
    delete comando;
    return false;
}

void GestorJuego::mejorarTorreJugador(Torre* t) {
    ComandoMejorarTorre* comando = new ComandoMejorarTorre(t);
    comando->ejecutar();
    historial.registrar(comando);
}

void GestorJuego::deshacerUltimaAccion() {
    if (historial.puedeDeshacer()) {
        historial.deshacer();
    }
}

void GestorJuego::rehacerUltimaAccion() {
    if (historial.puedeRehacer()) {
        historial.rehacer();
    }
}

bool GestorJuego::juegoTerminado() const {
    return vidaJugador <= 0;
}

bool GestorJuego::haGanado() const {
    return !gestorOleadas.hayOleadasPendientes() && colaEnemigos.estaVacia();
}

void GestorJuego::mostrarEstado() const {
    std::cout << "Vida: " << vidaJugador << " | Oleada: " << oleadaActual
              << " | Puntaje: " << puntuacion << std::endl;
    mapa.imprimirMapa();
}

void GestorJuego::mostrarResultadoFinal(bool victoria) const {
    std::cout << (victoria ? "Victoria!" : "Derrota") << std::endl;
    std::cout << "Puntaje final: " << puntuacion
              << " | Oleada alcanzada: " << oleadaActual << std::endl;
}

Mapa& GestorJuego::getMapa() const {
    return mapa;
}

int GestorJuego::getVidaJugador() const {
    return vidaJugador;
}

int GestorJuego::getPuntuacion() const {
    return puntuacion;
}

int GestorJuego::getOleadaActual() const {
    return oleadaActual;
}
