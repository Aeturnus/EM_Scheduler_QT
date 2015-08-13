#include "showunassigned.h"
#include "ui_showunassigned.h"

#include <QScrollBar>
#include <QDesktopWidget>
#include <QApplication>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Shift.h"

#include <vector>

#include "displayshift.h"

ShowUnassigned::ShowUnassigned(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowUnassigned)
{
    ui->setupUi(this);
}

ShowUnassigned::~ShowUnassigned()
{
    delete ui;
    delete container;
    delete scrollArea;
    delete[] &shiftWidgets[0];
}

void ShowUnassigned::init(Scheduler *attachSchedule)
{
    this->setMaximumHeight(QApplication::desktop()->height());

    schedule = attachSchedule;
    container = new QWidget(this);
    scrollArea = new QScrollArea(this);
    shiftWidgets.clear();
    int index;
    for(int i = 0; i < schedule->getShiftNum(); i++)
    {
        if(schedule->shifts()[i].student() == nullptr && !(schedule->shifts()[i].isBlocked()))
        {
            shiftWidgets.push_back(new DisplayShift(container));
            index = shiftWidgets.size() -1; //Index is the
            if(index == 0)
            {
                //(DisplayShift*)(shiftWidgets[index])->move(20,20);
                (shiftWidgets[index])->move(20,20);
            }
            else
            {
                //(DisplayShift*)(shiftWidgets[index])->move(20,(DisplayShift*)(shiftWidgets[index-1])->y() + 20);
                (shiftWidgets[index])->move(20,(shiftWidgets[index-1])->y() +(shiftWidgets[index-1])->height() + 20);
            }
            //(DisplayShift*)(shiftWidgets[index])->init(&(schedule->shifts()[i]),schedule);
            (shiftWidgets[index])->init(&(schedule->shifts()[i]),schedule);
        }
    }
    if(shiftWidgets.size() > 0)
        container->resize(180 + 40 + scrollArea->verticalScrollBar()->width(),(shiftWidgets[index])->y() + (shiftWidgets[index])->height() + 20 + scrollArea->horizontalScrollBar()->height());
    else
        container->resize(180 + 40 + scrollArea->verticalScrollBar()->width(),61+ scrollArea->horizontalScrollBar()->height());
    scrollArea->setWidget(container);
    scrollArea->move(0,0);

    this->resize(container->width(), 61 * 6);
    scrollArea->resize(this->width(),this->height());

}

void ShowUnassigned::resizeEvent(QResizeEvent *event)
{
    scrollArea->resize(this->width(),this->height());
}
