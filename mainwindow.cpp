#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager.init(ui->tableWidget);

    try
    {
        FileManager file_manager("testtttttt.json");
    }
    catch(std::invalid_argument &e)
    {
        qDebug() << e.what();
    }

}

MainWindow::~MainWindow()
{
    if (generator->isActiveWindow()) generator->close();
    delete generator;
    delete ui;
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

void MainWindow::on_actionGenerator_hase_2_triggered()
{
    generator->show();
}

void MainWindow::on_pushButton_clicked()
{
    // ukrywanie i odkrywanie haseł
    if (passwords_hidden)
    {
        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            if (ui->tableWidget->item(i, 1)->text() != "")
            {
                QString buffer = ui->tableWidget->item(i, 1)->data(3).toString();
                qDebug() << buffer;
                ui->tableWidget->item(i, 1)->setText(buffer);
                ui->tableWidget->item(i, 1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
                ui->pushButton->setText("Ukryj hasła");
            }
        }
        passwords_hidden = false;
    }
    else
    {
        for (int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            if (ui->tableWidget->item(i, 1)->text() != "")
            {
                QString password = ui->tableWidget->item(i, 1)->text();
                ui->tableWidget->item(i, 1)->setData(3, password);
                ui->tableWidget->item(i, 1)->setText("***");
                ui->tableWidget->item(i, 1)->setFlags(0);
                ui->pushButton->setText("Pokaż hasła");
            }
        }
        passwords_hidden = true;
    }
}

void MainWindow::on_actionNowy_triggered()
{
    int result = QMessageBox::warning(this, "Uwaga!", "Utworzenie nowego projektu zniszczy całą dotychczasową pracę! Czy kontynuować ?", QMessageBox::Yes | QMessageBox::No);
    while (result != QMessageBox::Yes && result != QMessageBox::No) result = QMessageBox::warning(this, "Uwaga!", "Utworzenie nowego projektu zniszczy całą dotychczasową pracę! Czy kontynuować ?", QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::No) return;
    ui->tableWidget->clearContents();
}

void MainWindow::on_actionZako_cz_triggered()
{
    this->close();
}

void MainWindow::on_actionO_Autorze_triggered()
{
    QMessageBox::information(this, "Informacja o autorze", "Menadżer haseł napisany w C++/Qt\nAutor: Marcin K ISI1");
}

void MainWindow::on_actionWczytaj_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Wybierz plik do otwarcia...", QDir::currentPath(), "Json Files (*.json)");
    qDebug() << filename;
    if (filename.isEmpty()) return;

    FileManager file_manager(filename);
    if (!file_manager.isValid())
    {
        QMessageBox::critical(this, "Błąd!", "Plik nie zawiera prawidłowego obiektu JSON!");
        return;
    }

    QList<QTableWidgetItem*> rows = file_manager.readAllRows();
    ui->tableWidget->clearContents();

    manager.resetCursor();
    for (auto row : rows) manager << row->text();
}

void MainWindow::on_actionZapisz_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Zapisz dane do pliku...", QDir::currentPath(), "Json Files (*.json)");
    if (filepath.isEmpty()) return;

    QStringList list = filepath.split("/");
    QString filename = list.last();

    FileManager file_manager(filename);
    QList<QString> row;
    int size = ui->tableWidget->rowCount() * ui->tableWidget->columnCount();
    for (int i=1; i<=size; i++)
    {
        QString content;
        manager >> content;
        if (content.isEmpty()) break;

        row << content;
        if (row.count() == 3)
        {
            file_manager.saveRow(row);
            row.clear();
        }
    }

    //file_manager.saveToFile();
}
