#include "displayshift.h"
#include "ui_displayshift.h"

#include <QLabel>
#include <QString>
#include <QFont>

#include <string>
#include <sstream>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Date.h"

#include "shiftselect.h"

DisplayShift::DisplayShift(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DisplayShift)
{
    ui->setupUi(this);
}

DisplayShift::~DisplayShift()
{
    delete ui;
}

void DisplayShift::init(Shift *attachShift, Scheduler *attachSchedule)
{
    shift = attachShift;
    schedule = attachSchedule;
    selected = false;
    update();
}

void DisplayShift::update(void)
{
    if(shift->isBlocked())
    {
        //If it's blocked
        ui->label_title->setText(QString::fromStdString(shift->getBlockReason()));

        ui->label_student->setText("");
        ui->label_manual->setText("");
    }
    else
    {
        //Title
        ui->label_title->setText(QString::fromStdString(shift->getName()) +" "+QString::fromStdString(shift->shiftTimeString(false)));

        //Student Name
        if(shift->student() == nullptr)
        {
            ui->label_student->setText("<font color=red>OPEN</font>");
        }
        else
        {
            ui->label_student->setText("<font color=blue>" + QString::fromStdString(shift->student()->getName()) + "</font>");
        }

        //Is manually set
        if(shift->isManual())
        {
            ui->label_manual->setText("MANUALLY SET");
        }
        else
        {
            ui->label_manual->setText("");
        }
    }
}

void DisplayShift::mousePressEvent(QMouseEvent* event)
{
    ShiftSelect* s = new ShiftSelect();
    s->init(shift,schedule);
    s->exec();

    delete s;
}
