#include "tablemanager.h"

TableManager::TableManager()
{
    initialized = false;
}

void TableManager::init(QTableWidget *table)
{
    this->table = table;

    table->verticalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setStretchLastSection(true);
    for (int i=0; i<table->rowCount(); i++)
    {
        for (int j=0; j<table->columnCount(); j++)
        {
            table->setItem(i,j, new QTableWidgetItem);
        }
    }

    table->resizeRowsToContents();
    initialized = true;
}

void TableManager::appendRow()
{
    if (!initialized) return;
    table->insertRow(table->rowCount());
    prepareRow(table->rowCount()-1);
}

void TableManager::deleteRow(int row)
{
    table->removeRow(row);
}

void TableManager::deleteLastRow()
{
    if (!initialized || table->rowCount() == 1) return;
    table->removeRow(table->rowCount()-1);
}

void TableManager::moveRowDown(int row)
{
    if (row == table->rowCount()-1) return;
    QStringList row1;

    for (int i=0; i<table->columnCount(); i++) row1 << table->item(row, i)->text();
    table->removeRow(row);

    table->insertRow(++row);
    for (int i=0; i<table->columnCount(); i++) table->setItem(row, i, new QTableWidgetItem(row1[i]));

    table->selectRow(row);
}

void TableManager::moveRowUp(int row)
{
    if (row == 0) return;
    QStringList row1;

    for (int i=0; i<table->columnCount(); i++) row1 << table->item(row, i)->text();
    table->removeRow(row);

    table->insertRow(--row);
    for (int i=0; i<table->columnCount(); i++) table->setItem(row, i, new QTableWidgetItem(row1[i]));

    table->selectRow(row);
}

bool TableManager::isRow(QList<QTableWidgetItem *> items)
{
    if (items.isEmpty() || items.count() % table->columnCount() != 0) return false;
    int row = items[0]->row();
    if (row == -1) return false;

    for (int i=1; i<items.count(); i++)
        if (items[i]->row() != row) return false;

    return true;
}

void TableManager::prepareRow(int row)
{
    if (!initialized) return;
    for (int i=0; i<table->columnCount(); i++) table->setItem(row, i, new QTableWidgetItem());
}

void TableManager::resetCursor()
{
    write_cursor = 1;
}

void TableManager::operator <<(const QString text)
{
    int row = write_cursor / 3;
    if (write_cursor % 3 == 0) row--;

    int column = write_cursor % 3;
    column--;
    if (column < 0) column = 2;

    qDebug() << "Row = " << row << " | Column = " << column;
    table->setItem(row, column, new QTableWidgetItem(text));
    write_cursor++;
}

QList<QString> TableManager::getRow(int row)
{
    QList<QString> list;
    list << (table->item(row, 0) != nullptr ? table->item(row, 0)->text() : "");
    list << (table->item(row, 1) != nullptr ? table->item(row, 1)->text() : "");
    list << (table->item(row, 2) != nullptr ? table->item(row, 2)->text() : "");
    return list;
}

/*void TableManager::operator >>(QString &text)
{
    int row = read_cursor / 3;
    if (read_cursor % 3 == 0) row--;

    int column = read_cursor % 3;
    column--;
    if (column < 0) column = 2;

    QTableWidgetItem *item = table->item(row, column);
    qDebug() << item->text();
    if (item == nullptr)
    {
        read_cursor = 1;
        text = "";
        return;
    }
    text = item->text();
    read_cursor++;
}*/
