#include "displayschedule.h"
#include "ui_displayschedule.h"

#include "../EM_Scheduler/Scheduler.h"
#include "displaydateshifts.h"

DisplaySchedule::DisplaySchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplaySchedule)
{
    ui->setupUi(this);
}

DisplaySchedule::~DisplaySchedule()
{
    delete ui;
    for(int i = 0; i < 1; i++)
    {
        delete dateShiftWidgets[i];
    }
    delete[] dateShiftWidgets;
}

void DisplaySchedule::init(Scheduler *attachSchedule)
{
    schedule = attachSchedule;

    dateShiftWidgets = new DisplayDateShifts*[1];

    for(int i = 0; i < 1; i++)
    {
        dateShiftWidgets[i]->init(&(schedule->dates()[i]),schedule);
        dateShiftWidgets[i]->move(0,0);
        dateShiftWidgets[i]->show();
    }
}
