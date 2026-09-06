#ifndef COLA_ENEMIGOS_H
#define COLA_ENEMIGOS_H

#include <queue>

#include "Mapa.h"
#include "../gestor/GestorJuego.h"
#include "../modelo/Cozy.h"

// Cola circular: cada Cozy vivo que no llega al final se vuelve a encolar
// al final de la cola, simulando su avance continuo por la ruta.
class ColaEnemigos {
private:
    // Cantidad de vida que pierde el jugador por cada enemigo que logra escapar.
    static constexpr int DANO_POR_FUGA = 1;

    // Cola FIFO utilizada para administrar el orden de procesamiento
    // de los enemigos durante cada quantum.
    std::queue<Cozy> colaCircular;

public:
    // Constructor que inicializa la cola de enemigos vacia.
    ColaEnemigos();

    // Agrega un enemigo al final de la cola.
    void encolar(const Cozy& enemigo);

    // Procesa un quantum completo del juego:
    // 1. Cada enemigo es procesado una sola vez.
    // 2. Las torres atacan al enemigo si esta dentro de su rango.
    // 3. Los enemigos eliminados se retiran de la cola.
    // 4. Los enemigos que llegan al final generan una fuga.
    // 5. Los enemigos que siguen vivos regresan al final de la cola.
    void actualizarQuantum(Mapa& mapa, GestorJuego& estado);

    // Determina si la cola no contiene enemigos.
    bool estaVacia() const;

    // Retorna la cantidad actual de enemigos almacenados en la cola.
    int tamanio() const;
};

#endif // COLA_ENEMIGOS_H