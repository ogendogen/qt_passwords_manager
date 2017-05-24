#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QString>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

class TableManager : public QObject
{
    Q_OBJECT
    public:
        TableManager();
        void init(QTableWidget *table);
        void appendRow();
        void deleteLastRow();
        void deleteRow(int row);
        void moveRowUp(int row);
        void moveRowDown(int row);
        bool isRow(QList<QTableWidgetItem*>);

    public slots:
        void cellClicked(int, int);

    private:
        QTableWidget *table;
        bool initialized = false;
        int last_clicked = 0;
        void prepareRow(int row);
};

#endif // TABLEMANAGER_H
