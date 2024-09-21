#include "auto.h"

Auto::Auto(const std::string& modelo, int año, float kilometraje)
    : Vehiculo(modelo, año, kilometraje) {}

float Auto::calcularMantenimiento() const {
//kilometraje entre 1000 por el año 2023 -menos el año actual por 50
    return (kilometraje / 1000) * (2024 - año) * 50;
}
