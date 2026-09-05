#ifndef COMANDOTORRE_H
#define COMANDOTORRE_H

// TODO: interfaz pura, sin .cpp
class ComandoTorre {
public:
    virtual void ejecutar() = 0;
    virtual void deshacer() = 0;
    virtual ~ComandoTorre() = default;
};

#endif
