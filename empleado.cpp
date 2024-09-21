#include "Empleado.h"


Empleado::Empleado(const std::string& nombre, int edad)
    : nombre(nombre), edad(edad) {}

void Empleado::guardar(std::ofstream& out) const {
    out << nombre << '\n' << edad << '\n';
}

void Empleado::cargar(std::ifstream& in) {
    in >> nombre >> edad;
}


EmpleadoFijo::EmpleadoFijo(const std::string& nombre, int edad, float salarioFijo)
    : Empleado(nombre, edad), salarioFijo(salarioFijo) {}

float EmpleadoFijo::calcularSalario() const {
    return salarioFijo;
}

void EmpleadoFijo::guardar(std::ofstream& out) const {
    Empleado::guardar(out);
    out << "Fijo\n" << salarioFijo << '\n';
}

void EmpleadoFijo::cargar(std::ifstream& in) {
    Empleado::cargar(in);
    in >> salarioFijo;
}


EmpleadoContratado::EmpleadoContratado(const std::string& nombre, int edad, float tarifaPorHora, int horasTrabajadas)
    : Empleado(nombre, edad), tarifaPorHora(tarifaPorHora), horasTrabajadas(horasTrabajadas) {}

float EmpleadoContratado::calcularSalario() const {
    return tarifaPorHora * horasTrabajadas;
}

void EmpleadoContratado::guardar(std::ofstream& out) const {
    Empleado::guardar(out);
    out << "Contratado\n" << tarifaPorHora << '\n' << horasTrabajadas << '\n';
}

void EmpleadoContratado::cargar(std::ifstream& in) {
    Empleado::cargar(in);
    in >> tarifaPorHora >> horasTrabajadas;
}


void Empresa::agregarEmpleado(Empleado* empleado) {
    empleados.emplace_back(empleado);
}

void Empresa::eliminarEmpleado(int index) {
    if (index >= 0 && index < empleados.size()) {
        empleados.erase(empleados.begin() + index);
    }
}

void Empresa::guardarEmpleados(const std::string& archivo) {
    std::ofstream out(archivo);
    for (const auto& empleado : empleados) {
        empleado->guardar(out);
    }
}

void Empresa::cargarEmpleados(const std::string& archivo) {
    std::ifstream in(archivo);
    while (in) {
        std::string tipo;
        in >> tipo;
        if (tipo == "Fijo") {
            auto empleado = new EmpleadoFijo("", 0, 0);
            empleado->cargar(in);
            agregarEmpleado(empleado);
        } else if (tipo == "Contratado") {
            auto empleado = new EmpleadoContratado("", 0, 0, 0);
            empleado->cargar(in);
            agregarEmpleado(empleado);
        }
    }
}
