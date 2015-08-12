#include "studentselect.h"
#include "ui_studentselect.h"

#include <QSignalMapper>
#include <QMessageBox>

#include "displayshift.h"
#include "overrideselect.h"

StudentSelect::StudentSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StudentSelect)
{
    ui->setupUi(this);
}

StudentSelect::~StudentSelect()
{
    delete ui;
    delete signalMapper;
    for(int i = 0; i < schedule->getStudentNum();i++)
    {
        delete displayStudent[i];
    }
    delete[] displayStudent;
}

void StudentSelect::init(Shift *attachShift, Scheduler *attachSchedule)
{
    shift = attachShift;
    schedule = attachSchedule;
    signalMapper = new QSignalMapper(this);

    displayStudent = new DisplayStudent*[schedule->getStudentNum()];
    int x,y;
    for(int i = 0; i < schedule->getStudentNum(); i++)
    {
        //Grab space for the buttons
        displayStudent[i] = new DisplayStudent(this);
        displayStudent[i]->init(&schedule->students()[i],schedule);
        x = 20 + (i%2) * (displayStudent[i]->width() + 10);
        y = 20 + (i/2 * (displayStudent[i]->height() + 10));

        displayStudent[i]->move(x,y);
        displayStudent[i]->show();

        //Map signals
        connect(displayStudent[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
        signalMapper->setMapping((QObject*)displayStudent[i],(QObject*)displayStudent[i]);  //You're kidding me. You have to cast the pointers for the mapping to work
    }

    connect(signalMapper,SIGNAL(mapped(QObject*)),this,SLOT(selected(QObject*)));

    int maxWidth,maxHeight,lastStudent;
    lastStudent = schedule->getStudentNum() - 1;

    //If it's an even index, it's going to be on the left. Grab its position
    if(schedule->getStudentNum()%2 == 0)
    {
        maxWidth = displayStudent[lastStudent]->x() + displayStudent[lastStudent]->width();
    }
    else
    {
        maxWidth = displayStudent[lastStudent-1]->x() + displayStudent[lastStudent-1]->width();
    }
    maxWidth += 20;
    maxHeight = displayStudent[lastStudent]->y() + displayStudent[lastStudent]->height() + 20;
    resize(maxWidth,maxHeight);
}

void StudentSelect::selected(QObject *objectClicked)
{
    DisplayStudent* clickedObject = (DisplayStudent*)objectClicked;
    Scheduler::AssignReturn state;
    state = schedule->assign(shift,clickedObject->getStudent(),true);
    bool success = false;
    //Throw an error message if it can't be assigned
    OverrideSelect o;
    o.init(schedule,shift,clickedObject->getStudent(),state,&success);
    switch(state)
    {
        case Scheduler::SUCCESS:
            success = true;
            break;
        case Scheduler::CONSEC:
            //QMessageBox::critical(this,tr("Error"),tr("Student will have too many consecutive shifts"));
            o.exec();
            break;
        case Scheduler::OVERLAP:
            QMessageBox::critical(this,tr("Error"),tr("Student has a time conflict"));
            break;
        case Scheduler::OVERMAX:
            //QMessageBox::critical(this,tr("Error"),tr("Student has the maximum number of shifts"));
            o.exec();
            break;
        case Scheduler::MINTIME:
            //QMessageBox::critical(this,tr("Error"),tr("Student has had a shift in the last 8 hours"));
            o.exec();
            break;
        case Scheduler::ISNULL:
            QMessageBox::critical(this,tr("Error"),tr("Student is non-existent (How did you even do this?)"));
            break;


    }
    if(success)
        this->close();
    /*
    if(state == Scheduler::SUCCESS)
    {
        this->close();
    }
    else if(state == Scheduler::CONSEC)
    {
        QMessageBox::critical(this,tr("Error"),tr("Student will have too many consecutive shifts"));
    }
    else if (state == Scheduler::OVERLAP)
    {
        QMessageBox::critical(this,tr("Error"),tr("Student has a time conflict"));
    }
    else if (state == Scheduler::OVERMAX)
    {
        QMessageBox::critical(this,tr("Error"),tr("Student has the maximum number of shifts"));
    }
    */
}
