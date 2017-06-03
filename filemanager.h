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
#include "coder.h"

class FileManager
{
    public:
        FileManager();
        ~FileManager();
        FileManager(QString file_name, QString master_key, bool truncate=false);
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
        QString master_key;
        Coder coder = Coder::getInstance();
};

#endif // FILEMANAGER_H
