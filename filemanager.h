#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QList>
#include <QTableWidgetItem>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <stdexcept>

class FileManager
{
    public:
        FileManager();
        ~FileManager();
        FileManager(QString file_name);
        bool saveRow(QList<QTableWidgetItem*> row);
        QList<QTableWidgetItem*> readAllRows();
        bool isValid();

        int countFiles();
        int countFilesInDir(QDir dir);
        QList<QFile> readAllFiles();

    private:
        QFile file;
        QJsonDocument document;
};

#endif // FILEMANAGER_H
