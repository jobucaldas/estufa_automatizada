#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialthreading.h"
#include "configform.h"

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{      
    ui->setupUi(this);

    _serial = new QSerialPort(this);

    // Opens port if closed
    while(!_serial->isOpen()){
        openSerialPort();
    }

    // Connection when there's something to get
    connect(_serial, SIGNAL(readyRead()), this, SLOT(writeData()));

    //**************Connections with config window********************//

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

void MainWindow::changeLabels(QString air, QString ground, QString temp, QString light)
{    
    qDebug() << "Entered label change\n";
    // Changes labels
    ui->lblAir->setText(air);
    ui->lblGround->setText(ground);
    ui->lblTemp->setText(temp);
    ui->lblLight->setText(light);
}

void MainWindow::openSerialPort()
{
    if(!_serial->isOpen())
    {
        // Searches ports for arduino
        bool arduinoIsAvailable = false;
        QString arduinoPortName;

        // For each available serial port
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            //  Check if the serialport has both a product identifier and a vendor identifier
            if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
                //  Check if the product ID and the vendor ID match those of the arduino
                if((serialPortInfo.productIdentifier() == arduinoProductId)
                        && (serialPortInfo.vendorIdentifier() == arduinoVendorId)){
                    // Arduino is available on this port
                    arduinoIsAvailable = true;
                    arduinoPortName = serialPortInfo.portName();
                }
            }
        }

        qDebug() << "Port name: " << arduinoPortName << "\n";

        if(arduinoIsAvailable){
            qDebug() << "Found the arduino\n";
            _serial->setPortName(arduinoPortName);
            _serial->setBaudRate(QSerialPort::Baud9600);
            _serial->setDataBits(QSerialPort::Data8);
            _serial->setFlowControl(QSerialPort::NoFlowControl);
            _serial->setParity(QSerialPort::NoParity);
            _serial->setStopBits(QSerialPort::OneStop);

            if (_serial->open(QIODevice::ReadWrite)) {
                qDebug() << "Serial Port Opened\n";
            }else {
                qCritical() << "Serial Port error:" << _serial->errorString();

                qDebug() << tr("Open error");

                QMessageBox notFoundMessage;
                notFoundMessage.setText("Não foi possivel conectar-se ao arduino.");
                notFoundMessage.exec();
            }
        }else{
            qDebug() << "Arduino not found\n";
            QMessageBox notFoundMessage;
            notFoundMessage.setText("Arduino não encontrado.");
            notFoundMessage.exec();
        }
    }
}

void MainWindow::writeData()
{
    qDebug() << "Retrieving information";

    _serial->write("Refresh Data");

    consoleText += _serial->readAll();

    qDebug() << consoleText << "\n";

    // Get position of information
    posLuz  = consoleText.lastIndexOf("Luminosidade :");
    posTemp = consoleText.lastIndexOf("Temperatura:");
    posSolo = consoleText.lastIndexOf("solo:");
    posAr   = consoleText.lastIndexOf("AR:");

    // Inputs values into strings
    strLuz  = consoleText.mid(posLuz + 15, 4);
    strTemp = consoleText.mid(posTemp + 13, 2) + "°C";
    strSolo = consoleText.mid(posSolo + 6, 4);
    strAr   = consoleText.mid(posAr + 4, 4);

    // Sends strings to main thread
    changeLabels(strAr, strSolo, strTemp, strLuz);
}


void MainWindow::onSentDateTime(QString date, QString time)
{
    qDebug() << "Date Time";
    qDebug() << date << "\n" << time << "\n";

    // Write arduino console
    _serial->write("\n");

    _serial->write("New Date: ");
    _serial->write(date.toLocal8Bit());
    _serial->write("\n");

    _serial->write("New Hour: ");
    _serial->write(time.toLocal8Bit());
    _serial->write("\n");
}

void MainWindow::onSentDowBool(QString dowBoolStr[7])
{
    qDebug() << "Bool DOW\n";

    int i;
    for(i=0; i<=6; i++){
        qDebug() << dowBoolStr[i] << "\n";
    }

    QThread::msleep(10000);

    // Checked strings to console
    _serial->write("Seg: ");
    _serial->write(dowBoolStr[0].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Ter: ");
    _serial->write(dowBoolStr[1].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Qua: ");
    _serial->write(dowBoolStr[2].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Qui: ");
    _serial->write(dowBoolStr[3].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Sex: ");
    _serial->write(dowBoolStr[4].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Sab: ");
    _serial->write(dowBoolStr[5].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Dom: ");
    _serial->write(dowBoolStr[6].toLocal8Bit());
    _serial->write("\n");
}

void MainWindow::onSentDowTime(QString dowTime1[7], QString dowTime2[7])
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
    _serial->write("Seg Start: ");
    _serial->write(dowTime1[0].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Ter Start: ");
    _serial->write(dowTime1[1].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Qua Start: ");
    _serial->write(dowTime1[2].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Qui Start: ");
    _serial->write(dowTime1[3].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Sex Start: ");
    _serial->write(dowTime1[4].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Sab Start: ");
    _serial->write(dowTime1[5].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Dom Start: ");
    _serial->write(dowTime1[6].toLocal8Bit());
    _serial->write("\n");

    //***************************************************************************//

    // Finish
    _serial->write("Seg Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Ter Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Qua Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Qui Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Sex Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Sab Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");

    _serial->write("Dom Finish: ");
    _serial->write(dowTime2[6].toLocal8Bit());
    _serial->write("\n");
}

MainWindow::~MainWindow()
{
    _serial->close();

    delete ui;
}

void MainWindow::on_btnExit_clicked()
{
    _serial->close();

    this->close();
}

void MainWindow::on_btnConfig_clicked()
{
    ConfigForm* configForm = new(ConfigForm);
    configForm->show();
}

void MainWindow::on_btnRefresh_clicked()
{
    //Opens port when closed
    while(!_serial->isOpen()){
        openSerialPort();
    }
}
