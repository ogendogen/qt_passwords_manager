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
        FileManager(QString file_name, bool truncate=false);
        bool saveRow(QList<QString> row);
        QList<QTableWidgetItem*> readAllRows();
        void saveToFile();
        void clearArrays();
        bool isValid();
        bool setFileName(QString file_name);

        int countFiles();
        int countFilesInDir(QDir dir);
        QList<QFile> readAllFiles();

    private:
        QFile file;
        QJsonDocument document;
        QJsonArray logins;
        QJsonArray passwords;
        QJsonArray descriptions;
};

#endif // FILEMANAGER_H
