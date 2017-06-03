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
        table << new QTableWidgetItem(logins[i].toString());
        table << new QTableWidgetItem(passwords[i].toString());
        table << new QTableWidgetItem(descriptions[i].toString());
    }
    return table;
}

bool FileManager::saveRow(QList<QString> row)
{
    if (row.count() != 3) return false;
    qDebug() << row[0];
    qDebug() << row[1];
    qDebug() << row[2];

    logins << row[0];
    passwords << row[1];
    descriptions << row[2];
    return true;
}

void FileManager::clearArrays()
{
    while (logins.count() > 0)
    {
        logins.removeFirst();
        passwords.removeFirst();
        descriptions.removeFirst();
    }
}

void FileManager::saveToFile()
{
    QJsonObject object;
    object.insert("logins", logins);
    object.insert("passwords", passwords);
    object.insert("descriptions", descriptions);

    QJsonDocument document_to_save;
    document_to_save.setArray(logins);
    document_to_save.setArray(passwords);
    document_to_save.setArray(descriptions);

    file.write(document_to_save.toJson());
}

bool FileManager::setFileName(QString file_name)
{
    if (!QFile::exists(file_name)) return false;

    file.setFileName(file_name);
    if (!file.isOpen()) return file.open(QIODevice::ReadWrite);
    return true;
}

bool FileManager::isValid()
{
    QJsonObject object = document.object();
    return object.contains("logins") && object.contains("passwords") && object.contains("descriptions");
}
