#include "newschedule.h"
#include "ui_newschedule.h"

#include <QDir>
#include <QString>
#include <QPushButton>
#include <QDialogButtonBox>

#include <string>
#include <sstream>
#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Date.h"
#include "../EM_Scheduler/Shift.h"

#include "setdate.h"
#include "newrotators.h"

NewSchedule::NewSchedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSchedule)
{
    ui->setupUi(this);
    //Unimplemented buttons
    ui->spinBox_NumShifts->hide();
    ui->toolButton_ShiftEdit->hide();
    ui->label_8->hide();
    ui->label_9->hide();
}

NewSchedule::~NewSchedule()
{
    delete ui;
}

void NewSchedule::init(Scheduler* attachSchedule, std::string* attachSaveDir, std::string* attachExportDir, bool* attachSuccess)
{
    advmode = false;
    schedule = attachSchedule;
    savedir = attachSaveDir;
    exportdir = attachExportDir;
    success = attachSuccess;

    //Setup spinboxes
    ui->spinBox_NumStudents->setMinimum(1);
    ui->spinBox_NumStudents->setValue(6);
    ui->spinBox_NumMaxShifts->setMinimum(14);
    ui->spinBox_NumMaxShifts->setValue(14);
    ui->spinBox_NumMinShifts->setMinimum(12);
    ui->spinBox_NumMinShifts->setValue(12);
    ui->spinBox_NumShifts->setMinimum(1);
    ui->spinBox_NumShifts->setValue(5);
    ui->spinBox_NumMaxCon->setValue(4);

    //Set up the student name vector
    studentNameVector.clear();
    adjustStudentNameVector();
    adjustShiftVector();

    //Original
    /*
    //Initial values of shifts
    shiftNameVector[0] = "Shift";
    shiftTimeVector[0] = {7,16};
    shiftNameVector[1] = "Shift";
    shiftTimeVector[1] = {15,24};
    shiftNameVector[2] = "Shift";
    shiftTimeVector[2] = {23,32};
    shiftNameVector[3] = "Crash";
    shiftTimeVector[3] = {7,16};
    shiftNameVector[4] = "Crash";
    shiftTimeVector[4] = {15,24};
    */
    //Initial values of shifts
    shiftNameVector[0] = "Shift";
    shiftTimeVector[0] = {7,16};
    shiftNameVector[1] = "Crash";
    shiftTimeVector[1] = {7,16};
    shiftNameVector[2] = "Shift";
    shiftTimeVector[2] = {15,24};
    shiftNameVector[3] = "Crash";
    shiftTimeVector[3] = {15,24};
    shiftNameVector[4] = "Shift";
    shiftTimeVector[4] = {23,32};


    //Set day to be today
    ui->dateEdit_Start->setDate(QDate::currentDate());
    //ui->dateEdit_Start->setMinimumDate(QDate::currentDate());
    ui->dateEdit_End->setDate(QDate::currentDate());
    //ui->dateEdit_End->setMinimumDate(QDate::currentDate());
    ui->dateEdit_End->setMinimumDate(ui->dateEdit_Start->date());

    ui->labelNameWarning->show();
    updateMaxWarning();

    updateButtonBox();
    updateAdv();

}
void NewSchedule::on_buttonBox_accepted()
{
    //Handle other stuff
    std::string name = ui->lineEdit_NameSchedule->text().toStdString();

    Date start,end;
    start.setDate(ui->dateEdit_Start->date().day(),ui->dateEdit_Start->date().month()-1,ui->dateEdit_Start->date().year());
    end.setDate(ui->dateEdit_End->date().day(),ui->dateEdit_End->date().month()-1,ui->dateEdit_End->date().year());

    int numshift = ui->spinBox_NumShifts->value();
    int numstudents = ui->spinBox_NumStudents->value();

    //Turn the shift time vector into a 2D array
    unsigned int shifttimes[numshift][2];
    for(int i = 0; i < numshift; i++)
    {
        shifttimes[i][0] = shiftTimeVector[i][0];
        shifttimes[i][1] = shiftTimeVector[i][1];
    }


    schedule->init(name,start,end,numshift,&shiftNameVector[0],shifttimes,numstudents,&studentNameVector[0]);

    //Put this after...It'll clober everything otherwise
    schedule->setMaxShifts(ui->spinBox_NumMaxShifts->value());
    schedule->setMinShifts(ui->spinBox_NumMinShifts->value());
    schedule->setMaxConsecutive(ui->spinBox_NumMaxCon->value());


    //Create dirs
    *savedir = ui->lineEdit_DirectorySave->text().toStdString();
    *exportdir = ui->lineEdit_DirectoryExport->text().toStdString();

    QString dirpath = QString::fromStdString(*savedir);
    QDir dir(dirpath);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }
    dirpath = QString::fromStdString(*exportdir);
    dir.setPath(dirpath);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }

    *success = true;
}


void NewSchedule::updateAdv(void)
{
    ui->spinBox_NumMaxCon->setEnabled(advmode);
    ui->spinBox_NumShifts->setEnabled(advmode);
    ui->toolButton_ShiftEdit->setEnabled(advmode);
    ui->lineEdit_DirectorySave->setEnabled(advmode);
    ui->lineEdit_DirectoryExport->setEnabled(advmode);
}

void NewSchedule::on_checkBox_AdvMode_stateChanged(int arg1)
{
    advmode = ui->checkBox_AdvMode->isChecked();
    updateAdv();
}




void NewSchedule::on_lineEdit_NameSchedule_textChanged(const QString &arg1)
{
    updateButtonBox();
}

void NewSchedule::updateButtonBox(void)
{
   //If there's no name, can't accept this dialog
   if(ui->lineEdit_NameSchedule->text().size() == 0)
   {
       ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
       ui->buttonBox->button(QDialogButtonBox::Ok)->setToolTip("<Schedule/Course Name> field cannot be empty");
   }
   else
   {
       ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
   }

}

void NewSchedule::adjustStudentNameVector(void)
{
    int num = ui->spinBox_NumStudents->value();
    while(studentNameVector.size() < num)
    {
        studentNameVector.push_back("");
    }
    while(studentNameVector.size() > num)
    {
        studentNameVector.pop_back();
    }
}

void NewSchedule::adjustShiftVector(void)
{
    int num = ui->spinBox_NumShifts->value();
    while(shiftNameVector.size() < num)
    {
        shiftNameVector.push_back("");
        shiftTimeVector.push_back({0,24});
    }
    while(shiftNameVector.size() < num)
    {
        shiftNameVector.pop_back();
        shiftTimeVector.pop_back();
    }
}

void NewSchedule::on_toolButton_StartDate_clicked()
{
    //Start up a setdate dialog
    SetDate d;
    QDate date;
    d.init(&date);
    d.exec();
    ui->dateEdit_Start->setDate(date);
    ui->dateEdit_End->setMinimumDate(date); //Set End's min date
    updateMaxWarning();
}

void NewSchedule::on_toolButton_EndDate_clicked()
{
    //Start up a setdate dialog
    SetDate d;
    QDate date;
    d.init(&date,ui->dateEdit_Start->date());   //Minimum date is the start
    d.exec();
    ui->dateEdit_End->setDate(date);
    updateMaxWarning();
}

void NewSchedule::on_dateEdit_Start_dateChanged(const QDate &date)
{
    ui->dateEdit_End->setMinimumDate(ui->dateEdit_Start->date());   //Set End's min date
    updateMaxWarning();
}

void NewSchedule::on_toolButton_StudentNames_clicked()
{
    ui->labelNameWarning->hide();
    NewRotators n;
    adjustStudentNameVector();
    n.init(&studentNameVector);
    n.exec();
    for(int i = studentNameVector.size()-1; i>=0; i--)
    {
        if(studentNameVector[i].size() == 0)
            ui->labelNameWarning->show();
    }
}

void NewSchedule::on_spinBox_NumMaxShifts_valueChanged(int arg1)
{
    updateMaxWarning();
}

void NewSchedule::updateMaxWarning(void)
{
    int diff = ui->dateEdit_Start->date().daysTo(ui->dateEdit_End->date());
    int shiftcount = diff * 5 / ui->spinBox_NumStudents->value();
    if(ui->spinBox_NumMaxShifts->value() < shiftcount)
    {
        std::stringstream sstream;
        sstream<<std::dec<<"You need a maximum of "<<shiftcount<<" shifts to guarantee all shifts are filled"<<std::endl;
        ui->labelMaxShiftWarning->setText(QString::fromStdString(sstream.str()));
        ui->labelMaxShiftWarning->show();
        ui->labelMaxShiftWarning->adjustSize();
    }
    else
    {
        ui->labelMaxShiftWarning->hide();
    }
}

void NewSchedule::on_dateEdit_End_dateChanged(const QDate &date)
{
    updateMaxWarning();
}
