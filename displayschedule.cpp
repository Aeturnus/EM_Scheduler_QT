#include "displayschedule.h"
#include "ui_displayschedule.h"

#include "../EM_Scheduler/Scheduler.h"
#include "displaydateshifts.h"

DisplaySchedule::DisplaySchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplaySchedule)
{
    ui->setupUi(this);

    schedule = nullptr;

    resize(10000,10000);
}

DisplaySchedule::~DisplaySchedule()
{
    delete ui;
    deleteMem();
}

void DisplaySchedule::deleteMem(void)
{
    if(schedule != nullptr)
    {
        unsigned int dateNum = schedule->getDateNum();
        for(int i = 0; i < dateNum; i++)
        {
            delete dateShiftWidgets[i];
        }
        delete[] dateShiftWidgets;
    }
    schedule = nullptr;
}

void DisplaySchedule::init(Scheduler *attachSchedule)
{
    schedule = attachSchedule;
    dateShiftWidgets = new DisplayDateShifts*[schedule->getDateNum()];

    unsigned int dateNum = schedule->getDateNum();
    for(int i = 0; i < dateNum; i++)
    {
        dateShiftWidgets[i] = new DisplayDateShifts(this);
        dateShiftWidgets[i]->init(&(schedule->dates()[i]),schedule);
        if(i == 0)
        {
            dateShiftWidgets[i]->move(0,0);
        }
        else
        {
            dateShiftWidgets[i]->move(dateShiftWidgets[i-1]->x() + dateShiftWidgets[i-1]->width() ,0);
        }
        dateShiftWidgets[i]->show();
    }
}

void DisplaySchedule::update(void)
{
    if(schedule==nullptr)
    {
        return;
    }
    unsigned int dateNum = schedule->getDateNum();
    for(int i = 0; i < dateNum; i++)
    {
        dateShiftWidgets[i]->update();
    }
}
