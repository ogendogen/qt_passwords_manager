#include "passwordgenerator.h"

PasswordGenerator::PasswordGenerator()
{

}

void PasswordGenerator::setRequirements(bool small_letters, bool big_letters, bool digits, bool special_chars, int min_chars, int max_chars)
{
    this->small_letters = small_letters;
    this->big_letters = big_letters;
    this->digits = digits;
    this->special_chars = special_chars;
    this->min_chars = min_chars;
    this->max_chars = max_chars;
}

QString PasswordGenerator::generate()
{
    int len = randomNumFromRange(min_chars, max_chars);
    QString output = "";
    while(1)
    {
        for (int i=0; i<len; i++)
        {
            int type = qrand() % 4;
            switch(type)
            {
                case 0:
                    output.append(randomNumFromRange((int)'a', (int)'z'));
                    break;
                case 1:
                    output.append(randomNumFromRange((int)'A', (int)'Z'));
                    break;
                case 2:
                    output.append(randomNumFromRange((int)'0', (int)'9'));
                    break;
                case 3:
                    output.append(randomNumFromRange(50, 150));
                    break;
            }
        }

        if (isPasswordMeetRequirements(output)) break;
    }
    return output;
}

int PasswordGenerator::randomNumFromRange(int min, int max)
{
    return qrand() % (max - min) + min;
}

bool PasswordGenerator::isPasswordMeetRequirements(QString password)
{
    if (password.length() < min_chars || password.length() > max_chars) return false;
    bool tester;
    if (small_letters)
    {
        tester = false;
        for (int i=0; i<password.count(); i++)
        {
            if (password[i] >= 'a' && password[i] <= 'z')
            {
                tester = true;
                break;
            }
        }
        if (!tester) return false;
    }
    // && !password.contains(new QRegularExpression("[A-Z]+"))) return false;
    if (big_letters)
    {
        tester = false;
        for (int i=0; i<password.count(); i++)
        {
            if (password[i] >= 'A' && password[i] <= 'Z')
            {
                tester = true;
                break;
            }
        }
        if (!tester) return false;
    }
    if (digits)
    {
        tester = false;
        for (int i=0; i<password.count(); i++)
        {
            if (password[i] >= '0' && password[i] <= '9')
            {
                tester = true;
                break;
            }
        }
        if (!tester) return false;
    }
    if (special_chars)
    {
        tester = false;
        for (int i=0; i<password.count(); i++)
        {
            if (password[i] < 'A' && password[i] > '9')
            {
                tester = true;
                break;
            }
        }
        if (!tester) return false;
    }
    return true;
}
