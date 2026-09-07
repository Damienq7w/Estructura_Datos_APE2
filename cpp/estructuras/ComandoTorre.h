#ifndef COMANDO_TORRE_H
#define COMANDO_TORRE_H

// Interfaz del patron Command: cualquier accion que se pueda hacer sobre
// una torre (colocarla, mejorarla) se envuelve en una clase que sabe
// como ejecutarse y como deshacerse. Asi HistorialComandos puede manejar
// deshacer/rehacer sin saber que tipo de accion es cada una.
class ComandoTorre {
public:
    // Virtual y con cuerpo vacio (= default) para que, al borrar un
    // ComandoTorre* que en realidad apunta a una subclase
    // (ComandoColocarTorre, etc.), se llame al destructor correcto.
    // Al no tener nada mas que implementar, no hace falta un .cpp aparte.
    virtual ~ComandoTorre() = default;

    // Aplica la accion (colocar la torre, mejorarla, etc.).
    virtual void ejecutar() = 0;

    // Revierte exactamente lo que hizo ejecutar().
    virtual void deshacer() = 0;
};

#endif