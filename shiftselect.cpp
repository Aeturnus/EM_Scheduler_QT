#include "shiftselect.h"
#include "ui_shiftselect.h"

ShiftSelect::ShiftSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShiftSelect)
{
    ui->setupUi(this);
}

ShiftSelect::~ShiftSelect()
{
    delete ui;
}

void ShiftSelect::init(Shift *attachShift, Scheduler *attachSchedule)
{
    shift = attachShift;
    schedule = attachSchedule;

    update();
}

void ShiftSelect::update(void)
{
    QString nametime = QString::fromStdString(shift->getName()) + " " + QString::fromStdString(shift->shiftTimeString());

    ui->labelNameTime->setText(nametime);

    QString studentname = (shift->student()!=nullptr)?(QString::fromStdString(shift->student()->getName())):"Open";
    ui->labelStudent->setText(studentname);

    ui->checkBoxIsBlocked->setChecked(shift->isBlocked());
    ui->checkBoxIsManual->setChecked(shift->isManual());

    QString blockreason = QString::fromStdString(shift->getBlockReason());
    ui->labelBlockReason->setText(blockreason);

    //TODO: DATE
    this->setWindowTitle(QString::fromStdString(shift->date()->toString()));
}

void ShiftSelect::on_pushButtonSetManual_clicked()
{
    shift->setManual(true);
    update();
}

void ShiftSelect::on_pushButtonUnsetManual_clicked()
{
    shift->setManual(false);
    update();
}

void ShiftSelect::on_pushButtonBlock_clicked()
{
   shift->block(shift->getBlockReason());
   shift->setManual(true);
   update();
}


void ShiftSelect::on_pushButtonUnblock_clicked()
{
    shift->unblock();
    shift->setManual(true);
    update();
}
