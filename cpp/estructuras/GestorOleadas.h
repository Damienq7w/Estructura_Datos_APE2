#ifndef GESTOR_OLEADAS_H
#define GESTOR_OLEADAS_H

#include <queue>
#include "Oleada.h"

// Cola FIFO de oleadas pendientes: se liberan en el orden en que fueron agregadas.
class GestorOleadas {
private:
    std::queue<Oleada> oleadas;

public:
    // Constructor del gestor de oleadas.
    GestorOleadas();

    // Agrega una nueva oleada al final de la cola.
    void agregarOleada(const Oleada& oleada);

    // Retorna y elimina la primera oleada de la cola.
    // Si no existen oleadas pendientes, retorna una oleada vacia.
    Oleada siguienteOleada();

    // Determina si existen oleadas pendientes en la cola.
    bool hayOleadasPendientes() const;
};

#endif // GESTOR_OLEADAS_H