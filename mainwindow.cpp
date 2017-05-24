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
    manager.appendRow();
}

void MainWindow::on_pushButton_3_clicked()
{
    // usunięcie ostatniej opcji
    if (ui->tableWidget->rowCount() == 1)
    {
        QMessageBox::critical(this, "Uwaga!", "Nie możesz usunąć ostatniego wiersza!");
        return;
    }
    int result = QMessageBox::warning(this, "Uwaga!", "Zamierzasz usunąć bezpowrotnie ostatni wpis! Czy chcesz kontynuować ?", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No) return;
    manager.deleteLastRow();
}

void MainWindow::on_pushButton_4_clicked()
{
    // przesunięcie wiersza w dół
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if (!manager.isRow(items))
    {
        QMessageBox::warning(this, "Uwaga!", "Możesz wybrać tylko jeden cały wiersz!");
        ui->pushButton_4->setStyleSheet("color: black;");
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

void MainWindow::on_pushButton_4_pressed()
{
    ui->pushButton_4->setStyleSheet("color: red;");
}

void MainWindow::on_pushButton_4_released()
{
    ui->pushButton_4->setStyleSheet("color: black;");
}

void MainWindow::on_pushButton_5_pressed()
{
    ui->pushButton_5->setStyleSheet("color: red;");
}

void MainWindow::on_pushButton_5_released()
{
    ui->pushButton_5->setStyleSheet("color: black;");
}

void MainWindow::on_pushButton_6_clicked()
{
    // usunięcie zaznaczonej opcji
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    if (!manager.isRow(items))
    {
        QMessageBox::warning(this, "Uwaga!", "Możesz tylko usuwać wiersz!");
        return;
    }
    manager.deleteRow(items[0]->row());
}
