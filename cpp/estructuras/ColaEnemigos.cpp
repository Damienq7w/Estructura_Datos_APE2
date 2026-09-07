#include "ColaEnemigos.h"

ColaEnemigos::ColaEnemigos()
    : colaCircular() {
}

void ColaEnemigos::encolar(const Cozy& enemigo) {
    colaCircular.push(enemigo);
}

void ColaEnemigos::actualizarQuantum(Mapa& mapa, GestorJuego& estado) {

    // Se obtiene el tamanio ANTES de comenzar el bucle.
    // Esto garantiza que cada Cozy sea procesado una sola vez
    // por quantum, aunque posteriormente vuelva a ingresar a la cola.
    int cantidadAProcesar = static_cast<int>(colaCircular.size());

    const std::vector<Coordenada>& ruta = mapa.getRuta();
    std::vector<Torre*> torresActivas = mapa.getTorresActivas();

    for (int i = 0; i < cantidadAProcesar; i++) {

        // front() obtiene el primer elemento de la cola
        // y pop() lo elimina de la cola.
        Cozy enemigo = colaCircular.front();
        colaCircular.pop();

        // Se obtiene la posicion actual del enemigo dentro de la ruta.
        const Coordenada& posActual =
            ruta[enemigo.getIndiceRuta()];

        // Todas las torres activas comprueban si pueden atacar
        // al enemigo ubicado en su posicion actual.
        for (Torre* torre : torresActivas) {

            if (enemigo.estaVivo() &&
                torre->estaEnRango(posActual)) {

                // La torre aplica su ataque sobre la copia local del
                // enemigo (la misma que luego se vuelve a encolar).
                torre->atacar(enemigo);
            }
        }

        // Si el enemigo fue eliminado durante el ataque,
        // se suma su recompensa y no vuelve a la cola.
        if (!enemigo.estaVivo()) {
            estado.sumarPuntaje(enemigo.getRecompensa());
            continue;
        }

        // El enemigo avanza dentro de la ruta.
        enemigo.avanzar();

        // Si alcanza la posicion final, se considera una fuga.
        if (enemigo.llegoAlFinal(
                static_cast<int>(ruta.size()))) {

            estado.restarVida(DANO_POR_FUGA);
            continue;
        }

        // Si continua vivo y no ha llegado al final,
        // vuelve a colocarse al final de la cola.
        colaCircular.push(enemigo);
    }
}

bool ColaEnemigos::estaVacia() const {
    return colaCircular.empty();
}

int ColaEnemigos::tamanio() const {
    return static_cast<int>(colaCircular.size());
}
