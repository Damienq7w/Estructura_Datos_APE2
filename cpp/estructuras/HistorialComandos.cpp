#include "HistorialComandos.h"

// Va sacando comandos del tope hasta que la pila queda vacia, borrando
// cada uno con delete (ya nadie mas los va a usar).
void HistorialComandos::vaciar(std::stack<ComandoTorre*>& pila) {
    while (!pila.empty()) {
        delete pila.top();
        pila.pop();
    }
}

// Al morir el HistorialComandos, se aseguran de liberar todo lo que
// haya quedado guardado en ambas pilas.
HistorialComandos::~HistorialComandos() {
    vaciar(pilaDeshacer);
    vaciar(pilaRehacer);
}

// Un comando nuevo siempre va al tope de pilaDeshacer. Y como ya no
// tiene sentido "rehacer" una rama vieja despues de una accion nueva,
// se vacia pilaRehacer.
void HistorialComandos::registrar(ComandoTorre* c) {
    pilaDeshacer.push(c);
    vaciar(pilaRehacer);
}

// Saca el ultimo comando ejecutado, lo deshace, y lo guarda en
// pilaRehacer por si se quiere volver a aplicar mas adelante.
void HistorialComandos::deshacer() {
    ComandoTorre* c = pilaDeshacer.top();
    pilaDeshacer.pop();
    c->deshacer();
    pilaRehacer.push(c);
}

// Operacion inversa a deshacer(): saca el ultimo deshecho, lo vuelve a
// ejecutar, y lo regresa a pilaDeshacer.
void HistorialComandos::rehacer() {
    ComandoTorre* c = pilaRehacer.top();
    pilaRehacer.pop();
    c->ejecutar();
    pilaDeshacer.push(c);
}

bool HistorialComandos::puedeDeshacer() const { return !pilaDeshacer.empty(); }
bool HistorialComandos::puedeRehacer() const { return !pilaRehacer.empty(); }
