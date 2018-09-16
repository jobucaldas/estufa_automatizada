#ifndef SERIALTHREADING_H
#define SERIALTHREADING_H

#include <QSerialPort>
#include <QThread>

class SerialThreading : public QThread
{
    Q_OBJECT

public:
    // Main
    explicit SerialThreading(QObject *parent = nullptr);

    // Serial port variables
    QSerialPort* serial;

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

public slots:
    void run();

    void onSentDateTime(QString, QString);

    void onSentDowTime(QString[], QString[]);

    void onSentDowBool(QString[]);

private:
    // Serial port variables
    static const quint16 arduinoVendorId  = 9025;
    static const quint16 arduinoProductId = 66;

signals:
    void changeLabels(QString, QString, QString, QString);
};

#endif // SERIALTHREADING_H
