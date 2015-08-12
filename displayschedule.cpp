#include "displayschedule.h"
#include "ui_displayschedule.h"

#include <QLabel>
#include <QFont>
#include <QString>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Date.h"
#include "displaydateshifts.h"

DisplaySchedule::DisplaySchedule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisplaySchedule)
{
    ui->setupUi(this);

    schedule = nullptr;

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
        for(int i = 0; i < 7; i++)
        {
            delete weekdayLabel[i];
        }
        delete[] dateShiftWidgets;
    }
    schedule = nullptr;
}

void DisplaySchedule::init(Scheduler *attachSchedule)
{
    deleteMem();

    schedule = attachSchedule;

    //Initialize dateshifts and find the talles one
    int maxHeight = 0;

    dateShiftWidgets = new DisplayDateShifts*[schedule->getDateNum()];
    unsigned int dateNum = schedule->getDateNum();
    for(int i = 0; i < dateNum; i++)
    {
        dateShiftWidgets[i] = new DisplayDateShifts(this);
        dateShiftWidgets[i]->init(&(schedule->dates()[i]),schedule,i);
        if(dateShiftWidgets[i]->height() > maxHeight)
        {
            maxHeight = dateShiftWidgets[i]->height();  //Update maxHeight if a taller one is found
        }

    }

    //Initialize weekdays
    QFont weekdayFont;
    weekdayFont.setBold(true);
    weekdayFont.setPointSize(14);
    int dateWidth = dateNum>0?dateShiftWidgets[0]->width():180 + 180/4;
    for(int i = 0; i < 7; i++)
    {
        weekdayLabel[i] = new QLabel(this);
        weekdayLabel[i]->setFont(weekdayFont);
        weekdayLabel[i]->setAlignment(Qt::AlignHCenter);
        weekdayLabel[i]->setText(QString::fromStdString(Date::WEEKDAY_NAMES[i]));
        weekdayLabel[i]->resize(dateWidth,50);
        if(i == 0)
        {
            weekdayLabel[i]->move(0,weekdayLabel[i]->height()/4);
        }
        else
        {
            weekdayLabel[i]->move(weekdayLabel[i-1]->width() + weekdayLabel[i-1]->x(),weekdayLabel[i]->height()/4);
        }
        weekdayLabel[i]->show();
    }



    //Place the dateshifts
    //x = datewidth*weekdaynumber,y= base + row*maxheight
    int row = 0;
    int base = weekdayLabel[0]->height() + weekdayLabel[0]->y();
    DisplayDateShifts* dateShift;
    for(int i = 0; i < dateNum; i++)
    {
        dateShift = dateShiftWidgets[i];
        dateShift->move(dateWidth * dateShift->getDate()->getNumDayOfWeek(),base + row*maxHeight);
        dateShiftWidgets[i]->show();

        if(dateShift->getDate()->getNumDayOfWeek() == 6)    //If saturday, move down a row
        {
            row++;
        }
    }

    resize(weekdayLabel[6]->x() + weekdayLabel[6]->width(),dateShiftWidgets[dateNum-1]->y() + dateShiftWidgets[dateNum-1]->height());
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
