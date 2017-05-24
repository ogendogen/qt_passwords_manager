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
    int min_len = -1, max_len = -1;
    if (ui->radioButton->isChecked()) {min_len = 4; max_len = 6;}
    else if (ui->radioButton_2->isChecked()) {min_len = 7; max_len = 8;}
    else if (ui->radioButton_3->isChecked()) {min_len = 10; max_len = 13;}
    else if (ui->radioButton_4->isChecked()) {min_len = 14; max_len = 18;}
    else if (ui->radioButton_5->isChecked()) {min_len = 18; max_len = 32;}
    generator.setRequirements(ui->checkBox_4->isChecked(), ui->checkBox_3->isChecked(), ui->checkBox_2->isChecked(), ui->checkBox->isChecked(), min_len, max_len);
    ui->lineEdit->setText(generator.generate());
}

void GeneratorWindow::on_clipboard_button_clicked()
{
    if (ui->lineEdit->text().isEmpty()) return;
    QClipboard *clipboard = QGuiApplication::clipboard(); // jedyny wskaźnik na systemowy schowek, nie usuwać!
    clipboard->setText(ui->lineEdit->text());
    qDebug() << "kopiuje do schowka...";
}

int GeneratorWindow::isMinimumRequirementsMet()
{
    int checked = 0;
    if (ui->checkBox->isChecked()) checked++;
    if (ui->checkBox_2->isChecked()) checked++;
    if (ui->checkBox_3->isChecked()) checked++;
    if (ui->checkBox_4->isChecked()) checked++;

    return (checked >= 2 ? true : false);
}

void GeneratorWindow::on_checkBox_4_clicked()
{
    // małe litery
    if (!isMinimumRequirementsMet()) ui->checkBox_4->toggle();
}

void GeneratorWindow::on_checkBox_3_clicked()
{
    // duże litery
    if (!isMinimumRequirementsMet()) ui->checkBox_3->toggle();
}

void GeneratorWindow::on_checkBox_2_clicked()
{
    // cyfry
    if (!isMinimumRequirementsMet()) ui->checkBox_2->toggle();
}

void GeneratorWindow::on_checkBox_clicked()
{
    // znaki
    if (!isMinimumRequirementsMet()) ui->checkBox->toggle();
}
