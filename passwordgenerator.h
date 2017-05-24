#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QString>
#include <QRegularExpression>

class PasswordGenerator
{
    public:
        PasswordGenerator();
        void setRequirements(bool small_letters, bool big_letters, bool digits, bool special_chars, int min_chars, int max_chars);
        QString generate();

    private:
        bool small_letters = true;
        bool big_letters = false;
        bool digits = true;
        bool special_chars = false;
        int min_chars = 8;
        int max_chars = 10;
        int randomNumFromRange(int min, int max);
        bool isPasswordMeetRequirements(QString password);
};

#endif // PASSWORDGENERATOR_H
