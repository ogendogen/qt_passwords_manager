#ifndef GENERATORWINDOW_H
#define GENERATORWINDOW_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QClipboard>
#include <QMessageBox>
#include "passwordgenerator.h"

namespace Ui {
class GeneratorWindow;
}

class GeneratorWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GeneratorWindow(QWidget *parent = 0);
    ~GeneratorWindow();

private slots:
    void on_generation_button_clicked();

    void on_clipboard_button_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_clicked();

private:
    Ui::GeneratorWindow *ui;
    int isMinimumRequirementsMet();
    PasswordGenerator generator;
};

#endif // GENERATORWINDOW_H
