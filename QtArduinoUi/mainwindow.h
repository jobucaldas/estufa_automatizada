#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialthreading.h"
#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openSerialPort();    

    void changeLabels(QString, QString, QString, QString);

    // Serial port variables
    QSerialPort* _serial;

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
    void onSentDateTime(QString, QString);

    void onSentDowTime(QString[], QString[]);

    void onSentDowBool(QString[]);

private slots:
    void on_btnExit_clicked();

    void on_btnConfig_clicked();

    void on_btnRefresh_clicked();

    void writeData();

private:
    Ui::MainWindow *ui;

    // Serial port variables
    static const quint16 arduinoVendorId  = 9025;
    static const quint16 arduinoProductId = 66;
};

#endif // MAINWINDOW_H
