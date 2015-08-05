#include "editschedule.h"
#include "ui_editschedule.h"

#include <QString>

#include <string>
#include <vector>

#include "../EM_Scheduler/Scheduler.h"
#include "newrotators.h"

EditSchedule::EditSchedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSchedule)
{
    ui->setupUi(this);
}

EditSchedule::~EditSchedule()
{
    delete ui;
}

void EditSchedule::init(Scheduler *attachSchedule)
{
    schedule = attachSchedule;

    ui->spinBoxShiftMax->setValue(schedule->getMaxShifts());
    ui->spinBoxShiftMax->setMinimum(14);

    ui->spinBoxShiftMin->setValue(schedule->getMinShifts());
    ui->spinBoxShiftMin->setMinimum(12);

    ui->spinBoxConMax->setValue(schedule->getMaxConsecutive());

    ui->lineEditName->setText(QString::fromStdString(schedule->getName()));
}

void EditSchedule::on_buttonBox_accepted()
{
    schedule->setName(ui->lineEditName->text().toStdString());
    schedule->setMaxShifts((unsigned int)ui->spinBoxShiftMax->value());
    schedule->setMinShifts((unsigned int)ui->spinBoxShiftMin->value());
    schedule->setMaxConsecutive((unsigned int)ui->spinBoxConMax->value());
    this->close();
}

void EditSchedule::on_buttonBox_rejected()
{
    this->close();
}

void EditSchedule::on_toolButtonStudentNames_clicked()
{
    std::vector<std::string> stunames;
    stunames.clear();
    for(int i = 0; i < schedule->getStudentNum(); i++)
    {
        stunames.push_back(schedule->students()[i].getName());  //Populate vector of names
    }

    NewRotators n;
    n.init(&stunames);
    n.exec();

    for(int i = 0; i < schedule->getStudentNum(); i++)
    {
        schedule->students()[i].setName(stunames[i]);
    }


}
