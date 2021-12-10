#include "dia_createuser.h"
#include "ui_dia_createuser.h"
#include <QMessageBox>

Dia_createUser::Dia_createUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dia_createUser)
{
    ui->setupUi(this);
}

Dia_createUser::~Dia_createUser()
{
    delete ui;
}

void Dia_createUser::on_buttonBox_create_accepted()
{
    _name = ui->lineEdit_name->text();
    _lastName = ui->lineEdit_lastName->text();
    _document = ui->lineEdit_document->text();
    _dateBirth = ui->dateEdit_dateBirth->text();
    _newUser = ui->lineEdit_newUser->text();
    _newPassword = ui->lineEdit_newPassword->text();
    _confirmPassword = ui->lineEdit_newPassword->text();

    if(ui->comboBox_cultivo->currentIndex()==0){
        _cultivo=1;
    }else {
        _cultivo=2;
    }


    if(_name=="" || _lastName==""||_document==""||_newUser==""||_newPassword==""||_confirmPassword==""){
        QMessageBox:: information(this, "Sign up","Faltan espacios");
    }
    else if(_newPassword!=_confirmPassword){
        QMessageBox:: warning(this, "Sign up","La contraseña deben coincidir");
    }
    else{
        _control.abrir_DB();
        _control.guardarUsuario_DB(_newUser.toStdString(),_newPassword.toStdString(),_name.toStdString(),_lastName.toStdString(),_document.toStdString(),_dateBirth.toStdString(),ui->spinBox_temperatura->value(),ui->spinBox_humedad->value(),ui->spinBox_velocidadViento->value(),ui->spinBox_direccionViento->value(),ui->spinBox_precipitacion->value(),ui->spinBox_intensidadLuz->value(),_cultivo);
        _control.cerrar_DB();
    }

}

void Dia_createUser::on_pushButton_validar_clicked()
{
    _name = ui->lineEdit_name->text();
    _lastName = ui->lineEdit_lastName->text();
    _document = ui->lineEdit_document->text();
    _dateBirth = ui->dateEdit_dateBirth->text();
    _newUser = ui->lineEdit_newUser->text();
    _newPassword = ui->lineEdit_newPassword->text();
    _confirmPassword = ui->lineEdit_newPassword->text();
    if(ui->comboBox_cultivo->currentIndex()==0){
        _cultivo=1;
    }else {
        _cultivo=2;
    }

    if(_name=="" || _lastName==""||_document==""||_newUser==""||_newPassword==""||_confirmPassword==""){
        QMessageBox:: information(this, "Sign up","Faltan espacios");
    }
    else if(_newPassword!=_confirmPassword){
        QMessageBox:: warning(this, "Sign up","La contraseña debe coincidir");
    }



}
