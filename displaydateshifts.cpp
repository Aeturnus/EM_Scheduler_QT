#include "displaydateshifts.h"
#include "ui_displaydateshifts.h"

#include <QLabel>
#include <QString>

#include <string>
#include <sstream>

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Date.h"

DisplayDateShifts::DisplayDateShifts(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DisplayDateShifts)
{
    ui->setupUi(this);
}

DisplayDateShifts::~DisplayDateShifts()
{
    delete ui;
    for(int i = 0; i < shiftNum; i++)
    {
        delete shiftWidgets[i];     //Free the DisplayShifts
    }
    delete[] shiftWidgets;          //Free the array of pointers
}

void DisplayDateShifts::init(Date *attachDate, Scheduler *attachSchedule)
{
    date = attachDate;
    schedule = attachSchedule;
    Shift::findShiftsWithDate(&shiftPtrVector,date,schedule->shifts(),schedule->getShiftNum(),false);   //Populate the vector
    shiftNum = shiftPtrVector.size();

    labelDate = new QLabel(this);       //Label for date
    //Build the date string
    std::stringstream sstream;
    sstream<<std::dec<<date->getMonth()<< " "<<date->getNumDay();
    labelDate->setText(QString::fromStdString(sstream.str()));          //Set the date

    shiftWidgets = new DisplayShift*[shiftNum];
    for(int i = 0; i <shiftNum; i++)
    {
        shiftWidgets[i] = new DisplayShift(this);       //Allocate memory for each shift widget
        //INIT THEM
        shiftWidgets[i]->init(shiftPtrVector[i],schedule);
        shiftWidgets[i]->show();
    }

    //Size and placement of shifts
    update();

}

void DisplayDateShifts::update(void)
{
    labelDate->move(0,0);
    //Place shifts
    int height = labelDate->height();
    for(int i = 0; i < shiftNum; i++)
    {
        if(i == 0)
        {
            //If it's the first one, move relative to labelDate
            shiftWidgets[i]->move(shiftWidgets[i]->width()/8,labelDate->height() + labelDate->y());
        }
        else
        {
            //If it's not the first one, move it relative to the last shift widget
            shiftWidgets[i]->move(shiftWidgets[i]->width()/8,shiftWidgets[i-1]->height() + shiftWidgets[i-1]->y());
        }
        height += shiftWidgets[i]->height();
        shiftWidgets[i]->update();
    }

    resize(shiftWidgets[0]->width()+shiftWidgets[0]->width()/4,height);
}

unsigned int DisplayDateShifts::getShiftNum(void)
{
    return shiftNum;
}
