#include "displaydateshifts.h"
#include "ui_displaydateshifts.h"

#include <QLabel>
#include <QString>
#include <QFont>

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
    //(QFont)(labelDate->font()).setBold(true);
    QFont tempfont;
    tempfont.setBold(true);
    tempfont.setPointSize(12);
    labelDate->setFont(tempfont);
    labelDate->setAlignment(Qt::AlignHCenter);


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
    //Place shifts
    int prevH = labelDate->height();  //Height of previous element
    int prevY = labelDate->y();  //Y of previous element

    labelDate->move(0,prevH/4);
    for(int i = 0; i < shiftNum; i++)
    {
        if(i == 0)
        {
            //If it's the first one, move relative to labelDate
            prevH = labelDate->height();
            prevY = labelDate->y();
            shiftWidgets[i]->move(shiftWidgets[i]->width()/8,prevH + prevY + prevH/4);
        }
        else
        {
            //If it's not the first one, move it relative to the last shift widget
            prevH = shiftWidgets[i-1]->height();
            prevY = shiftWidgets[i-1]->y();
            shiftWidgets[i]->move(shiftWidgets[i]->width()/8,prevH + prevY + prevH/4);
        }
        shiftWidgets[i]->update();
    }
    resize(shiftWidgets[0]->width()+shiftWidgets[0]->width()/4,shiftWidgets[shiftNum-1]->height() + shiftWidgets[shiftNum-1]->height()/4 + shiftWidgets[shiftNum-1]->y());
    labelDate->resize(this->width(),labelDate->height());
}

unsigned int DisplayDateShifts::getShiftNum(void)
{
    return shiftNum;
}

Date* DisplayDateShifts::getDate(void)
{
    return date;
}
