/**
 * @file dia_createuser.h
 * @authors Juan Felipe Otálora, José Luis de la Hoz y Victor Daniel Escobar
 * @date 10/12/2021
 * @brief Aquí es donde se crean las funciones, cuadros de texto y botones que se usarán en la interfaz gráfica para la ventana creación del usuario desde esta.
 */

#ifndef DIA_CREATEUSER_H
#define DIA_CREATEUSER_H
#include "Control_DB.h"
#include <QDialog>

namespace Ui {
class Dia_createUser;
}
/**
 * @brief Definición de la clase Dia_createUser. Aquí se maneja la interfaz donde se va a crear un usuario.
 */
class Dia_createUser : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Dia_createUser
     * @param parent
     */
    explicit Dia_createUser(QWidget *parent = nullptr);
    /**
      * @brief Destructor de Dia_createUser()
      */
    ~Dia_createUser();

private slots:
    /**
     * @brief on_buttonBox_create_accepted ""
     */
    void on_buttonBox_create_accepted();
    /**
     * @brief on_pushButton_validar_clicked ""
     */
    void on_pushButton_validar_clicked();

private:
    /**
     * @brief ui ""
     */
    Ui::Dia_createUser *ui;
    /**
     * @brief "_name" es la variable que almacenará el nombre de la persona que se esté registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _name="";
    /**
     * @brief _lastName es la variable que almacenará el apellido de la persona que se esté registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _lastName="";
    /**
     * @brief _document es la variable que almacenará el documento de identidad de la persona que se esté registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _document="";
    /**
     * @brief _dateBirth es la variable que almacenará la fecha de nacimiento de la persona que se esté registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _dateBirth="";
    /**
     * @brief _newUser es la variable que almacenará el usuario de la persona que se esté registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _newUser="";
    /**
     * @brief _newPassword es la variable que almacenará la contraseña de la persona que se esté registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _newPassword="";
    /**
     * @brief _confirmPassword es una variable que sirve para validar la contraseña de la persona que se esté registrando registrando el cual será recibido desde la interfaz gráfica.
     */
    QString _confirmPassword="";
    /**
     * @brief _cultivo es la variable que almacenará el tipo de cultivo del cual se quieren recibir los datos y alertas de los sensores, siendo 1 el cultivo de papa y 2 el cultivo de rosas, este dato será recibido desde la interfaz gráfica.
     */
    int _cultivo=1;

    Control_DB _control{"Sensores.db"};

};

#endif // DIA_CREATEUSER_H
