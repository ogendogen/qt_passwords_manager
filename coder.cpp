#include "coder.h"

Coder::Coder()
{

}

Coder Coder::getInstance()
{
    return instance;
}

QByteArray Coder::encode(QByteArray input, QString master_key)
{
    for (auto &&i : input)
    {
        for (auto qsmall_key : master_key)
        {
            char small_key = qsmall_key.toLatin1();
            i ^= (int)small_key;
        }
    }
    return input;
}

QByteArray Coder::decode(QByteArray input, QString master_key)
{
    for (auto &&i : input)
    {
        for (int j=master_key.length()-1; j>=0; j--)
        {
            i ^= (int)master_key[j].toLatin1();
        }
    }
    return input;
}
