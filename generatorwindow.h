#ifndef GENERATORWINDOW_H
#define GENERATORWINDOW_H

#include <QDialog>
#include <QString>
#include <QDebug>

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

private:
    Ui::GeneratorWindow *ui;
};

#endif // GENERATORWINDOW_H
