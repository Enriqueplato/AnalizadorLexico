#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>
#define MAX 650
#define MAX_RES 10

char *PalabrasReservadas[MAX_RES] = {"entero", "decimal", "boolean", "cadena", "si", "sino", "mientras", "hacer", "verdadero", "falso"};
//unsigned char entrada[MAX];
//char *p;

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
    ui->tpCodigo->setPlainText(texto);
    file.close();
}


void Widget::on_btnRun_clicked()
{

    //Declaracion de String con el contenido del plaintextedit
    QString text = ui->tpCodigo->toPlainText();
    QString miComando;
    QString miValor;
    QString xLinea;
    QString otra;

    QStringList lineas = text.split(";", QString::SkipEmptyParts); //partimos el texto por cada linea
    QStringList palabra;
    static int i = 0;
    xLinea = lineas.at(i); //No deja picar la linea en este mismo paso

    palabra = xLinea.split(",", QString::SkipEmptyParts); //picando la linea por palabras
    miComando = palabra.at(0); //tomando la primera palabra
    miValor = palabra.at(1); //tomando la segunda palabra
    otra = palabra.at(2);

    ui->ptTokensError->setPlainText(QString::number(i+1));
    ui->ptTokens->setPlainText(miComando);
    ui->ptTokensError->appendPlainText(miValor);
    ui->ptTemporal->setPlainText(otra);
    if((i >= 0) && (i < lineas.count())) i++;
    if(i >= lineas.count()) i = 0;
}
