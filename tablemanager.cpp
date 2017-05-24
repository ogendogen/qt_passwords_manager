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
