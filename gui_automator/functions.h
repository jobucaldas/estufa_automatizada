#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QSerialPort>

namespace functions{
class updateLabels;
}

class updateLabels
{
public:
    // Console String
    QString consoleText;

    // Char position
    int posLuz;
    int posTemp;
    int posSolo;
    int posAr;

    // Label Strings
    QString strLuz;
    QString strTemp;
    QString strSolo;
    QString strAr;

    // Check value
    QString chkValueSeg = "false";
    QString chkValueTer = "false";
    QString chkValueQua = "false";
    QString chkValueQui = "false";
    QString chkValueSex = "false";
    QString chkValueSab = "false";
    QString chkValueDom = "false";
};

#endif // FUNCTIONS_H
