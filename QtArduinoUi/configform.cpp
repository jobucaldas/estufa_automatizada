#include "configform.h"
#include "ui_configform.h"

ConfigForm::ConfigForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigForm)
{
    ui->setupUi(this);

    SetUiWidgets();
}

void ConfigForm::SetUiWidgets()
{
    // Set date
    ui->datePicker->setCalendarPopup(true);
    ui->datePicker->setDate(QDate::currentDate());

    // Set time
    ui->timePicker->setTime(QTime::currentTime());
}

ConfigForm::~ConfigForm()
{
    delete ui;
}

void ConfigForm::on_btnExit_clicked()
{
    this->close();
}

void ConfigForm::on_btnSave_clicked()
{
    // Gets values and sends them to strings
    datePicker = ui->datePicker->date().toString();
    timePicker = ui->timePicker->time().toString();

    // Emits date and time to thread
    emit sendDateTime(datePicker, timePicker);

    // Gets dow values and sends them to strings
    if(ui->chkSeg->isChecked())
        dowBool[0] = "true";
    else
        dowBool[0] = "false";

    if(ui->chkTer->isEnabled())
        dowBool[1] = "true";
    else
        dowBool[1] = "false";

    if(ui->chkQua->isEnabled())
        dowBool[2] = "true";
    else
        dowBool[2] = "false";

    if(ui->chkQui->isChecked())
        dowBool[3] = "true";
    else
        dowBool[3] = "false";

    if(ui->chkSex->isEnabled())
        dowBool[4] = "true";
    else
        dowBool[4] = "false";

    if(ui->chkSab->isEnabled())
        dowBool[5] = "true";
    else
        dowBool[5] = "false";

    if(ui->chkDom->isEnabled())
        dowBool[6] = "true";
    else
        dowBool[6] = "false";

    // Emit dow bool
    emit sendDowBool(dowBool);

    // Gets start time
    dowStart[0] = ui->timePickerSeg1->time().toString();
    dowStart[1] = ui->timePickerTer1->time().toString();
    dowStart[2] = ui->timePickerQua1->time().toString();
    dowStart[3] = ui->timePickerQui1->time().toString();
    dowStart[4] = ui->timePickerSex1->time().toString();
    dowStart[5] = ui->timePickerSab1->time().toString();
    dowStart[6] = ui->timePickerDom1->time().toString();

    // Gets finish time
    dowFinish[0] = ui->timePickerSeg2->time().toString();
    dowFinish[1] = ui->timePickerTer2->time().toString();
    dowFinish[2] = ui->timePickerQua2->time().toString();
    dowFinish[3] = ui->timePickerQui2->time().toString();
    dowFinish[4] = ui->timePickerSex2->time().toString();
    dowFinish[5] = ui->timePickerSab2->time().toString();
    dowFinish[6] = ui->timePickerDom2->time().toString();

    // Emit dow time
    emit sendDowTime(dowStart, dowFinish);
}
