#include "serialthreading.h"
#include "configform.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QThread>
#include <QDebug>
#include <QMutex>

SerialThreading::SerialThreading(QObject *parent) : QThread(parent), serial(new QSerialPort(this))
{
    ConfigForm* configForm = new(ConfigForm);

    // Connect time with this thread
    connect(configForm, SIGNAL(sendDateTime(QString, QString)),
    this, SLOT(onSentDateTime(QString, QString)));

    // Connect dow time with this thread
    connect(configForm, SIGNAL(sendDowTime(QString[], QString[])),
    this, SLOT(onSentDowTime(QString[], QString[])));

    // Connect dow checkboxes with this thread
    connect(configForm, SIGNAL(sendDowBool(QString[])),
    this, SLOT(onSentDowBool(QString[])));
}

void SerialThreading::run()
{    


    qDebug() << "Thread ended\n";
}

void SerialThreading::onSentDateTime(QString date, QString time)
{        
    qDebug() << "Date Time";
    qDebug() << date << "\n" << time << "\n";

    // Write arduino console
    serial->write("\n");

    serial->write("New Date: ");
    serial->write(date.toLocal8Bit());
    serial->write("\n");

    serial->write("New Hour: ");
    serial->write(time.toLocal8Bit());
    serial->write("\n");
}

void SerialThreading::onSentDowBool(QString dowBoolStr[7])
{
    qDebug() << "Bool DOW\n";

    int i;
    for(i=0; i<=6; i++){
        qDebug() << dowBoolStr[i] << "\n";
    }

    // Checked strings to console
    serial->write("Seg: ");
    serial->write(dowBoolStr[0].toLocal8Bit());
    serial->write("\n");

    serial->write("Ter: ");
    serial->write(dowBoolStr[1].toLocal8Bit());
    serial->write("\n");

    serial->write("Qua: ");
    serial->write(dowBoolStr[2].toLocal8Bit());
    serial->write("\n");

    serial->write("Qui: ");
    serial->write(dowBoolStr[3].toLocal8Bit());
    serial->write("\n");

    serial->write("Sex: ");
    serial->write(dowBoolStr[4].toLocal8Bit());
    serial->write("\n");

    serial->write("Sab: ");
    serial->write(dowBoolStr[5].toLocal8Bit());
    serial->write("\n");

    serial->write("Dom: ");
    serial->write(dowBoolStr[6].toLocal8Bit());
    serial->write("\n");
}

void SerialThreading::onSentDowTime(QString dowTime1[7], QString dowTime2[7])
{
    int i;

    qDebug() << "Tempo Inicial";
    for(i=0; i<=6; i++){
        qDebug() << dowTime1[i] << "\n";
    }

    qDebug() << "Tempo Final";
    for(i=0; i<=6; i++){
        qDebug() << dowTime2[i] << "\n";
    }

    // Start
    serial->write("Seg Start: ");
    serial->write(dowTime1[0].toLocal8Bit());
    serial->write("\n");

    serial->write("Ter Start: ");
    serial->write(dowTime1[1].toLocal8Bit());
    serial->write("\n");

    serial->write("Qua Start: ");
    serial->write(dowTime1[2].toLocal8Bit());
    serial->write("\n");

    serial->write("Qui Start: ");
    serial->write(dowTime1[3].toLocal8Bit());
    serial->write("\n");

    serial->write("Sex Start: ");
    serial->write(dowTime1[4].toLocal8Bit());
    serial->write("\n");

    serial->write("Sab Start: ");
    serial->write(dowTime1[5].toLocal8Bit());
    serial->write("\n");

    serial->write("Dom Start: ");
    serial->write(dowTime1[6].toLocal8Bit());
    serial->write("\n");

    //***************************************************************************//

    // Finish
    serial->write("Seg Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");

    serial->write("Ter Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");

    serial->write("Qua Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");

    serial->write("Qui Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");

    serial->write("Sex Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");

    serial->write("Sab Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");

    serial->write("Dom Finish: ");
    serial->write(dowTime2[6].toLocal8Bit());
    serial->write("\n");
}
