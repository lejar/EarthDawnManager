#ifndef UTILS_H
#define UTILS_H

#include <QDebug>

struct mob {
    QString name;
    int dex, str, tou, per, wil, cha;
    int karma, hp, wounds;
};

int rollDice(int sides)
{
    int roll = 0;
    int sum = 0;

    do
    {
        roll = 0;
        roll = random()%sides + 1;
        sum += roll;
    } while(roll == sides);

    return sum;
}

int rollStep(int step)
{
    int sum = 0;

    switch(step)
    {
        case 1:
            sum += rollDice(6)-3;
            break;
        case 2:
            sum += rollDice(6)-2;
            break;
        case 3:
            sum += rollDice(6)-1;
            break;
        case 4:
            sum += rollDice(6);
            break;
        case 5:
           sum += rollDice(8);
           break;
        case 6:
           sum += rollDice(10);
           break;
        case 7:
           sum += rollDice(12);
           break;
        case 8:
           sum += rollDice(6) + rollDice(6);
           break;
        case 9:
           sum += rollDice(8) + rollDice(6);
           break;
        case 10:
           sum += rollDice(8) + rollDice(8);
           break;
        case 11:
           sum += rollDice(10) + rollDice(8);
           break;
        case 12:
           sum += rollDice(10) + rollDice(10);
           break;
        case 13:
           sum += rollDice(12) + rollDice(10);
           break;
        case 14:
           sum += rollDice(12) + rollDice(12);
           break;
        case 15:
           sum += rollDice(12) + rollDice(6) + rollDice(6);
           break;
        case 16:
           sum += rollDice(12) + rollDice(8) + rollDice(6);
           break;
        case 17:
           sum += rollDice(12) + rollDice(8) + rollDice(8);
           break;
        case 18:
           sum += rollDice(12) + rollDice(10) + rollDice(8);
           break;
        case 19:
           sum += rollDice(12) + rollDice(10) + rollDice(10);
           break;
        case 20:
           sum += rollDice(12) + rollDice(12) + rollDice(10);
           break;
        case 21:
           sum += rollDice(12) + rollDice(12) + rollDice(12);
           break;
        case 22:
           sum += rollDice(12) + rollDice(12) + rollDice(6) + rollDice(6);
           break;
        case 23:
           sum += rollDice(12) + rollDice(12) + rollDice(8) + rollDice(6);
           break;
        case 24:
           sum += rollDice(12) + rollDice(12) + rollDice(8) + rollDice(8);
           break;
        case 25:
           sum += rollDice(12) + rollDice(12) + rollDice(10) + rollDice(8);
           break;
        case 26:
           sum += rollDice(12) + rollDice(12) + rollDice(10) + rollDice(10);
           break;
        case 27:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(10);
           break;
        case 28:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12);
           break;
        case 29:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(6) + rollDice(6);
           break;
        case 30:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(8) + rollDice(6);
           break;
        case 31:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(8) + rollDice(8);
           break;
        case 32:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(10) + rollDice(8);
           break;
        case 33:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(10) + rollDice(10);
           break;
        case 34:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(10);
           break;
        case 35:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12);
           break;
        case 36:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(6) + rollDice(6);
           break;
        case 37:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(8) + rollDice(6);
           break;
        case 38:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(8) + rollDice(8);
           break;
        case 39:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(10) + rollDice(8);
           break;
        case 40:
           sum += rollDice(12) + rollDice(12) + rollDice(12) + rollDice(12) + rollDice(10) + rollDice(10);
           break;
        default:
           return -666;
           break;
    }
    return sum;
}

bool uniqueName(QString name, std::vector<mob*> mobTypeList)
{
    bool unique = true;
    for(auto mobType : mobTypeList)
    {
        if(mobType->name == name)
        {
            unique = false;
            break;
        }
    }
    return unique;
}

#endif // UTILS_H
