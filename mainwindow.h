#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QCloseEvent>
#include "generatorwindow.h"
#include "tablemanager.h"
#include "filemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_pressed();

    void on_pushButton_4_released();

    void on_pushButton_5_pressed();

    void on_pushButton_5_released();

    void on_pushButton_6_clicked();

    void on_actionGenerator_hase_2_triggered();

    void on_pushButton_clicked();

    void on_actionNowy_triggered();

    void on_actionZako_cz_triggered();

    void on_actionO_Autorze_triggered();

    void on_actionWczytaj_triggered();

    void on_actionZapisz_triggered();

protected:
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);


private:
    Ui::MainWindow *ui;
    TableManager manager;
    GeneratorWindow *generator = new GeneratorWindow(this);
    bool passwords_hidden = false;
};

#endif // MAINWINDOW_H
