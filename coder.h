#ifndef CODER_H
#define CODER_H

#include <QByteArray>
#include <QDebug>
#include <QString>

class Coder
{
    public:
        static Coder getInstance();
        QByteArray encode(QByteArray input, QString master_key);
        QByteArray decode(QByteArray input, QString master_key);

    private:
        Coder();
        static Coder instance;
};

#endif // CODER_H
