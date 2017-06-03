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
        void resetCursor();
        void operator << (const QString text);
        //void operator >> (QString &text);
        QList<QString> getRow(int row);

    private:
        QTableWidget *table;
        bool initialized = false;
        int last_clicked = 0;
        int write_cursor = 1;
        int read_cursor = 1;
        void prepareRow(int row);
};

#endif // TABLEMANAGER_H
