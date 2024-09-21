#include "Estudiante.h"
#include <iostream>


Estudiante::Estudiante(const std::string& nombre, int edad)
    : nombre(nombre), edad(edad) {}

void Estudiante::agregarMateria(const std::string& nombreMateria, int calificacion) {
    materias.push_back(nombreMateria);
    calificaciones.push_back(calificacion);
}

void Estudiante::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << "\nEdad: " << edad << std::endl;
    std::cout << "Materias y Calificaciones:" << std::endl;
    for (size_t i = 0; i < materias.size(); ++i) {
        std::cout << materias[i] << ": " << calificaciones[i] << std::endl;
    }
    std::cout << "Promedio: " << promedio() << std::endl;
}


EstudianteLicenciatura::EstudianteLicenciatura(const std::string& nombre, int edad)
    : Estudiante(nombre, edad) {}

double EstudianteLicenciatura::promedio() const {

    if (calificaciones.empty()) return 0.0;
    int suma = 0;
    for (int cal : calificaciones) {
        suma += cal;
    }
    return static_cast<double>(suma) / calificaciones.size();
}


EstudianteMaestria::EstudianteMaestria(const std::string& nombre, int edad)
    : Estudiante(nombre, edad) {}

double EstudianteMaestria::promedio() const {

    if (calificaciones.empty()) return 0.0;
    if (calificaciones.size() == 1) return static_cast<double>(calificaciones[0]);

    std::vector<int> califs = calificaciones;
    int min_calif = *std::min_element(califs.begin(), califs.end());
    int suma = 0;
    for (int cal : califs) {
        suma += cal;
    }
    suma -= min_calif;
    return static_cast<double>(suma) / (calificaciones.size() - 1);
}
