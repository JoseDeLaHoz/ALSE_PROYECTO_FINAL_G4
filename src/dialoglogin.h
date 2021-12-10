/**
 * @file dialoglogin.h
 * @authors Juan Felipe Otálora, José Luis de la Hoz y Victor Daniel Escobar
 * @date 10/12/2021
 * @brief Aquí es donde se crean las funciones, cuadros de texto y botones que se usarán en la interfaz gráfica para la ventana de ingreso a los datos de los sensores.
 */

#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>

namespace Ui {
class DialogLogin;
}
/**
 * @brief Definición de la clase DialogLogin. Aquí se maneja la interfaz donde se va ingresar a los datos de los sensores.
 */
class DialogLogin : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief La función DialogLogin se encarga de "".
     * @param parent
     */
    explicit DialogLogin(QWidget *parent = nullptr);
    /**
      * @brief Destructor de DialogLogin().
      */
    ~DialogLogin();

private slots:
    /**
     * @brief on_pushButton_loging_clicked ""
     */
    void on_pushButton_loging_clicked();
    /**
     * @brief on_pushButton_register_clicked ""
     */
    void on_pushButton_register_clicked();

signals:
    /**
     * @brief usuarioCorrecto ""
     * @param ingresar
     */
    void usuarioCorrecto(int ingresar);

private:
    /**
     * @brief ui ""
     */
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
