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


DisplayShift::DisplayShift(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplayShift)
{
    ui->setupUi(this);
}

DisplayShift::~DisplayShift()
{
    delete ui;
    delete label_manual;
    delete label_studentname;
    delete label_times;
    delete label_title;
    delete font_manual;
    delete font_studentname;
    delete font_times;
    delete font_title;
}

void DisplayShift::init(Shift *attachShift, Scheduler *attachSchedule)
{
    shift = attachShift;
    schedule = attachSchedule;
    selected = false;

    label_manual = new QLabel(this);
    label_studentname = new QLabel(this);
    label_times = new QLabel(this);
    label_title = new QLabel(this);

    font_manual = new QFont();
    font_studentname = new QFont();
    font_times = new QFont();
    font_title = new QFont();

    update();
}

void DisplayShift::update(void)
{
    if(shift->isBlocked())
    {
        //If it's blocked
        font_title->setItalic(true);
        font_title->setBold(false);
        label_title->setFont(*font_title);
        label_title->setText(QString::fromStdString(shift->getBlockReason()));

        label_times->setText("");
        label_studentname->setText("");
        label_manual->setText("");
    }
    else
    {
        //Title
        font_title->setItalic(false);
        font_title->setBold(true);
        label_title->setFont(*font_title);
        label_title->setText(QString::fromStdString(shift->getName()));

        //Times
        font_times->setItalic(true);
        label_title->setFont(*font_times);
        label_title->setText(QString::fromStdString(shift->shiftTimeString(false)));

        //Student Name
        if(shift->student() == nullptr)
        {
            font_studentname->setBold(true);
            label_studentname->setFont(*font_studentname);
            label_studentname->setText("<font color=red>OPEN</font>");
        }
        else
        {
            font_studentname->setBold(false);
            label_studentname->setFont(*font_studentname);
            label_studentname->setText(QString::fromStdString(shift->student()->getName()));
        }

        //Is manually set
        if(shift->isManual())
        {
            font_manual->setBold(true);
            label_manual->setFont(*font_manual);
            label_manual->setText("MANUALLY SET");
        }
        else
        {
            label_manual->setText("");
        }
    }

    //Move them
    label_title->move(0,0);
    label_times->move(0,label_title->height() + label_title->y());
    label_studentname->move(0,label_times->height() + label_times->y());
    label_manual->move(0,label_studentname->height() + label_studentname->y());
}
