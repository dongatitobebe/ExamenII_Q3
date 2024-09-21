#ifndef CAMION_H
#define CAMION_H

#include "vehiculo.h"

class Camion : public Vehiculo {
private:
    float capacidadCarga;
    int viajesLargos;

public:
    Camion(const std::string& modelo, int año, float kilometraje, float capacidadCarga, int viajesLargos);
    float calcularMantenimiento() const override;
};

#endif // CAMION_H
