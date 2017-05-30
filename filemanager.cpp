#include "filemanager.h"

FileManager::FileManager()
{

}

FileManager::FileManager(QString file_name)
{
    file.setFileName(file_name);
    if (!file.open(QIODevice::ReadWrite)) throw std::invalid_argument("can't open file");

    document = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
}

FileManager::~FileManager()
{
    if (file.isOpen()) file.close();
}

QList<QTableWidgetItem*> FileManager::readAllRows()
{
    QList<QTableWidgetItem*> table;

    QJsonObject object = document.object();
    QJsonArray logins = object["logins"].toArray();
    QJsonArray passwords = object["passwords"].toArray();
    QJsonArray descriptions = object["descriptions"].toArray();
    for (int i=0; i<logins.count(); i++)
    {
        table << new QTableWidgetItem(logins[i]);
        table << new QTableWidgetItem(passwords[i]);
        table << new QTableWidgetItem(descriptions[i]);
    }
    return table;
}
