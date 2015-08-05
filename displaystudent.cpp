#include "displaystudent.h"
#include "ui_displaystudent.h"

#include <QPushButton>
#include <QString>

DisplayStudent::DisplayStudent(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::DisplayStudent)
{
    ui->setupUi(this);
}

DisplayStudent::~DisplayStudent()
{
    delete ui;
}

void DisplayStudent::init(Student *attachStudent, Scheduler *attachSchedule)
{
    student = attachStudent;
    schedule = attachSchedule;
    update();
}

void DisplayStudent::update()
{
    ui->labelName->setText(QString::fromStdString(student->getName()));
    ui->labelShiftcount->setText(QString::number(student->getShiftCount()) + " assigned shifts");
    ui->labelShiftMax->setText("(" + QString::number(schedule->getMaxShifts()) +" maximum shifts)");

    if(student->getShiftCount() >= schedule->getMaxShifts())
    {
        this->setEnabled(false);
    }
    else
    {
        this->setEnabled(true);
    }
}

Student* DisplayStudent::getStudent()
{
    return student;
}
