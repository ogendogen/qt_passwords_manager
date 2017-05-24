#include "tablemanager.h"

TableManager::TableManager()
{
    initialized = false;
}

void TableManager::init(QTableWidget *table)
{
    this->table = table;
    connect(table, SIGNAL(cellClicked(int,int)), this, SLOT(cellClicked(int,int)));

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

void TableManager::addRow()
{
    if (!initialized) return;
    table->insertRow(table->rowCount());
    prepareRow(table->rowCount()-1);
}

void TableManager::deleteRow()
{
    if (!initialized) return;
    table->removeRow(table->rowCount()-1);
}

void TableManager::cellClicked(int row, int column)
{
    if (column != 1) return;
    last_clicked = row;
    qDebug() << QString::number(last_clicked);
}

void TableManager::prepareRow(int row)
{
    if (!initialized) return;
    for (int i=0; i<table->columnCount(); i++) table->setItem(row, i, new QTableWidgetItem());
}
