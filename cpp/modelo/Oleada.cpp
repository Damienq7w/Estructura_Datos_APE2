#include "Oleada.h"

#include "CatalogoEnemigos.h"

// Constructor privado de la oleada.
Oleada::Oleada(int numero, const std::vector<Cozy>& enemigos)
    : numero(numero),
      enemigos(enemigos) {
}

// Genera una oleada completa de enemigos segun el numero de oleada.
Oleada Oleada::generar(int numero) {
    int cantidad = 3 + numero; // mas enemigos conforme avanza el juego

    std::vector<Cozy> enemigos;
    enemigos.reserve(cantidad);

    for (int i = 0; i < cantidad; i++) {
        int indiceTipo = elegirTipo(numero, i);

        enemigos.push_back(
            CatalogoEnemigos::crear(indiceTipo, numero)
        );
    }

    return Oleada(numero, enemigos);
}

// Determina el tipo de enemigo que se generara segun la oleada
// y la posicion que ocupa dentro del grupo.
int Oleada::elegirTipo(int numero, int posicion) {

    // Oleadas bajas: mayormente "Normal" (indice 0).
    // A partir de la oleada 3 aparecen "Rapido" (indice 1) y desde la 5, "Tanque" (indice 2).

    if (numero >= 5 && posicion % 3 == 0) {
        return 2;
    }

    if (numero >= 3 && posicion % 2 == 0) {
        return 1;
    }

    return 0;
}

// Retorna la lista de enemigos pertenecientes a la oleada.
const std::vector<Cozy>& Oleada::getEnemigos() const {
    return enemigos;
}

// Retorna el numero de la oleada.
int Oleada::getNumero() const {
    return numero;
}