#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager.init(ui->tableWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // generator haseł
    QString a = "";
    if (ui->tableWidget->item(1,1)->isSelected()) a = "true"; else a = "false";
    qDebug() << a;
}

void MainWindow::on_pushButton_2_clicked()
{
    // dodanie nowej opcji
    manager.addRow();
}

void MainWindow::on_pushButton_3_clicked()
{
    // usunięcie ostatniej opcji
    manager.deleteRow();
}

void MainWindow::on_pushButton_4_clicked()
{
    // przesunięcie wiersza w dół
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if (!manager.isRow(items))
    {
        QMessageBox::warning(this, "Uwaga!", "Możesz wybrać tylko jeden cały wiersz!");
        return;
    }
    manager.moveRowDown(items.at(0)->row());
}

void MainWindow::on_pushButton_5_clicked()
{
    // przesunięcie wiersza w górę
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if (!manager.isRow(items))
    {
        QMessageBox::warning(this, "Uwaga!", "Możesz wybrać tylko jeden cały wiersz!");
        return;
    }
    manager.moveRowUp(items.at(0)->row());
}
