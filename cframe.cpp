#include "cframe.h"
#include "ui_cframe.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <sstream>
#include <algorithm>
#include <QListWidgetItem>

#include "vehiculo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "auto.h"
#include "camion.h"
#include <QTextEdit>
#include <QJsonArray>
#include <QDebug>

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
     cargarEstudiantesEnLista();
     te_AgregarCarro = ui->te_AgregarCarro;

}

cframe::~cframe()
{
    delete ui;
}

void cframe::on_Bton_Agregarestudiante_clicked()
{

    QString input = ui->te_estudiantes->toPlainText().trimmed();

    if (input.isEmpty()) {
        QMessageBox::warning(this, "Entrada Vacía", "Por favor, ingrese los datos del estudiante.");
        return;
    }


    QStringList lineas = input.split('\n', Qt::SkipEmptyParts);
    for (const QString& linea : lineas) {
        QStringList partes = linea.split('-', Qt::KeepEmptyParts);
        if (partes.size() != 5) {
            QMessageBox::warning(this, "Formato Incorrecto", "Cada estudiante debe tener el formato: Nombre-Edad-TipoDeClase-Materia-Calificacion");
            continue;
        }

        QString nombre = partes.at(0).trimmed();
        bool ok;
        int edad = partes.at(1).trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Edad Inválida", "La edad debe ser un número entero.");
            continue;
        }

        QString tipoClase = partes.at(2).trimmed();
        QString materia = partes.at(3).trimmed();
        int calificacion = partes.at(4).trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Calificación Inválida", "La calificación debe ser un número entero.");
            continue;
        }


        if (tipoClase.compare("EstudianteLicenciatura", Qt::CaseInsensitive) == 0) {
            auto estudiante = std::make_unique<EstudianteLicenciatura>(nombre.toStdString(), edad);
            estudiante->agregarMateria(materia.toStdString(), calificacion);
            estudiantes.push_back(std::move(estudiante));
        }
        else if (tipoClase.compare("EstudianteMaestria", Qt::CaseInsensitive) == 0) {
            auto estudiante = std::make_unique<EstudianteMaestria>(nombre.toStdString(), edad);
            estudiante->agregarMateria(materia.toStdString(), calificacion);
            estudiantes.push_back(std::move(estudiante));
        }
        else {
            QMessageBox::warning(this, "Tipo de Clase Inválido", "El tipo de clase debe ser 'EstudianteLicenciatura' o 'EstudianteMaestria'.");
            continue;
        }
    }


    guardarEnArchivo();


    ui->te_estudiantes->clear();
     cargarEstudiantesEnLista();
     QMessageBox::information(this, "Éxito", "Estudiantes agregados correctamente.");
}


void cframe::guardarEnArchivo()
{
    QFile archivo("estudiantes.txt");
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Error al Guardar", "No se pudo abrir el archivo para escribir.");
        return;
    }

    QTextStream out(&archivo);
    for (const auto& estudiante : estudiantes) {

        std::string tipoClase;
        if (dynamic_cast<EstudianteLicenciatura*>(estudiante.get()) != nullptr) {
            tipoClase = "EstudianteLicenciatura";
        }
        else if (dynamic_cast<EstudianteMaestria*>(estudiante.get()) != nullptr) {
            tipoClase = "EstudianteMaestria";
        }
        else {
            tipoClase = "Desconocido";
        }


        std::vector<std::string> materias = estudiante->getMaterias();
        std::vector<int> califs = estudiante->getCalificaciones();

        for (size_t i = 0; i < materias.size(); ++i) {
            out << QString::fromStdString(estudiante->getNombre()) << "-"
                << QString::number(estudiante->getEdad()) << "-"
                << QString::fromStdString(tipoClase) << "-"
                << QString::fromStdString(materias[i]) << "-"
                << QString::number(califs[i]) << "\n";
        }
    }

    archivo.close();
}

void cframe::on_lw_listadoestudiante_itemClicked(QListWidgetItem *item)
{

    if (!item) return;

    QString nombreEstudiante = item->text();


    for (const auto& estudiante : estudiantes) {
        if (estudiante->getNombre() == nombreEstudiante.toStdString()) {

            QString datos = QString::fromStdString(estudiante->getNombre() + "-" +
                                                   std::to_string(estudiante->getEdad()) + "-" +
                                                   (dynamic_cast<EstudianteLicenciatura*>(estudiante.get()) ? "Licenciatura" : "Maestría") + "-" +
                                                   "Materia" + "-" +
                                                   "Calificacion");
            ui->te_ModificarEstudiante->setPlainText(datos);
            break;
        }
    }
}

void cframe::on_pushButton_clicked()
{

    if (!ui->lw_listadoestudiante->currentItem()) {
        QMessageBox::warning(this, "Selección Incorrecta", "Por favor, selecciona un estudiante para modificar.");
        return;
    }

    QString input = ui->te_ModificarEstudiante->toPlainText().trimmed();
    QStringList partes = input.split('\n', Qt::SkipEmptyParts);

    if (partes.isEmpty()) {
        QMessageBox::warning(this, "Entrada Vacía", "Por favor, ingrese los nuevos datos del estudiante.");
        return;
    }

    QString nombreOriginal = ui->lw_listadoestudiante->currentItem()->text();
    for (const auto& estudiante : estudiantes) {
        if (QString::fromStdString(estudiante->getNombre()) == nombreOriginal) {

            QStringList datos = partes[0].split(':');
            if (datos.size() != 2) {
                QMessageBox::warning(this, "Formato Incorrecto", "El formato debe ser: Materia:Calificacion");
                return;
            }
            estudiante->agregarMateria(datos[0].trimmed().toStdString(), datos[1].trimmed().toInt());
            QMessageBox::information(this, "Éxito", "Datos del estudiante modificados correctamente.");
            cargarEstudiantesEnLista();
            return;
        }
    }

    QMessageBox::warning(this, "Error", "No se encontró al estudiante.");
}

void cframe::cargarEstudiantesEnLista()
{
    ui->lw_listadoestudiante->clear();
    for (const auto& estudiante : estudiantes) {
        ui->lw_listadoestudiante->addItem(QString::fromStdString(estudiante->getNombre()));
    }
}

void cframe::on_bton_eliminarEstudiante_clicked()
{

    QString nombreEstudiante = ui->le_EliminarEstudiante->text().trimmed();

    if (nombreEstudiante.isEmpty()) {
        QMessageBox::warning(this, "Entrada Vacía", "Por favor, ingrese el nombre del estudiante a eliminar.");
        return;
    }


    auto it = std::remove_if(estudiantes.begin(), estudiantes.end(),
                             [&nombreEstudiante](const std::unique_ptr<Estudiante>& estudiante) {
                                 return QString::fromStdString(estudiante->getNombre()) == nombreEstudiante;
                             });

    if (it != estudiantes.end()) {
        estudiantes.erase(it, estudiantes.end());
        QMessageBox::information(this, "Éxito", "Estudiante eliminado correctamente.");
        cargarEstudiantesEnLista();
        ui->le_EliminarEstudiante->clear();
    } else {
        QMessageBox::warning(this, "Error", "No se encontró al estudiante.");
    }
}

// Ejercicio 2
void cframe::on_bton_AgregarAuto_clicked()
{
    QString texto = te_AgregarCarro->toPlainText();
    QStringList datos = texto.split("-");

    if (datos.size() != 3) {
        QMessageBox::warning(this, "Error", "Ingrese los datos en el formato: Auto-Año-Kilometraje");
        return;
    }

    std::string modelo = datos[0].toStdString();
    int año = datos[1].toInt();
    float kilometraje = datos[2].toFloat();


    Auto* nuevoAuto = new Auto(modelo, año, kilometraje);


    QFile file("vehiculos.json");
    if (!file.open(QIODevice::Append)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo");
        return;
    }

    QJsonObject jsonObj;
    jsonObj["modelo"] = QString::fromStdString(nuevoAuto->getModelo());
    jsonObj["año"] = nuevoAuto->getAño();
    jsonObj["kilometraje"] = nuevoAuto->getKilometraje();
    jsonObj["mantenimiento"] = nuevoAuto->calcularMantenimiento();

    QJsonDocument jsonDoc(jsonObj);
    file.write(jsonDoc.toJson());
    file.close();


    te_AgregarCarro->clear();
    QMessageBox::information(this, "Éxito", "Vehículo agregado exitosamente.");
}

void cframe::on_bton_Agregarcamion_clicked()
{    QString input = te_AgregarCamion->toPlainText();
    QStringList datos = input.split('-');

    if (datos.size() != 5) {
        QMessageBox::warning(this, "Error", "Ingrese los datos en el formato correcto: Camion-Año-Kilometraje-Capacidad-ViajesLargos");
        return;
    }

    std::string modelo = datos[0].toStdString();
    int año = datos[1].toInt();
    float kilometraje = datos[2].toFloat();
    float capacidad = datos[3].toFloat();
    int viajesLargos = datos[4].toInt();


    Camion nuevoCamion(modelo, año, kilometraje, capacidad, viajesLargos);


    QFile file("camiones.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para guardar datos.");
        return;
    }

    QJsonArray jsonArray;
    if (file.size() > 0) {

        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        jsonArray = doc.array();
    }


    QJsonObject jsonCamion;
    jsonCamion["modelo"] = QString::fromStdString(nuevoCamion.getModelo());
    jsonCamion["año"] = nuevoCamion.getAño();
    jsonCamion["kilometraje"] = nuevoCamion.getKilometraje();
    jsonCamion["capacidad"] = capacidad;
    jsonCamion["viajesLargos"] = viajesLargos;
    jsonCamion["mantenimiento"] = nuevoCamion.calcularMantenimiento();

    jsonArray.append(jsonCamion);


    QJsonDocument newDoc(jsonArray);
    file.resize(0);
    file.write(newDoc.toJson());
    file.close();

    te_AgregarCamion->clear();
    QMessageBox::information(this, "Éxito", "Camión agregado exitosamente.");
}


void cframe::on_bton_seleccionarEmpleado_clicked()
{
}

