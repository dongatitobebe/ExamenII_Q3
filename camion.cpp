
#include "camion.h"

Camion::Camion(const std::string& modelo, int año, float kilometraje, float capacidadCarga, int viajesLargos)
    : Vehiculo(modelo, año, kilometraje), capacidadCarga(capacidadCarga), viajesLargos(viajesLargos) {}

float Camion::calcularMantenimiento() const {
    return (kilometraje * 0.1) + (capacidadCarga * 0.05) + (viajesLargos * 10);
}
