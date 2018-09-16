#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <QMainWindow>

namespace Ui {
class ConfigForm;
}

class ConfigForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigForm(QWidget *parent = nullptr);
    ~ConfigForm();
    void SetUiWidgets();

private slots:
    void on_btnExit_clicked();

    void on_btnSave_clicked();

private:
    Ui::ConfigForm *ui;

    // Info strings
    QString datePicker;
    QString timePicker;

    // DOW strings
    QString dowBool[7];
    QString dowStart[7];
    QString dowFinish[7];

signals:
    void sendDateTime(QString, QString);

    void sendDowTime(QString[], QString[]);

    void sendDowBool(QString[]);
};

#endif // CONFIGFORM_H
