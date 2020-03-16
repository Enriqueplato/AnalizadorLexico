#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Analizador Lexico");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked(){
    QString filtro = "Text File (*.txt)";
    QString nombreArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo", QDir::homePath(), filtro);
    QFile file(nombreArchivo);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Cuidado", "El archivo NO se pudo abrir");
    }
    QTextStream in(&file);
    QString texto = in.readAll();
    ui->textoPlano->setPlainText(texto);
    file.close();
}

void Widget::on_btnAbrirArchivo_clicked()
{

}
