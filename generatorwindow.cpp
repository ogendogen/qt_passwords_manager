#include "generatorwindow.h"
#include "ui_generatorwindow.h"

GeneratorWindow::GeneratorWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneratorWindow)
{
    ui->setupUi(this);
}

GeneratorWindow::~GeneratorWindow()
{
    delete ui;
}

void GeneratorWindow::on_generation_button_clicked()
{
    qDebug() << "generacja...";
}

void GeneratorWindow::on_clipboard_button_clicked()
{
    qDebug() << "kopiuje do schowka...";
}
