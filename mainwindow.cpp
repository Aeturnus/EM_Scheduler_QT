#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Date.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Parser.h"
#include "../EM_Scheduler/xlsoutput.h"

#include "newschedule.h"
#include <xlslib.h>
#include <xlslib/common.h>

using namespace xlslib_core;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init(Scheduler *attachSchedule, string *attachSaveDir, string *attachExportDir)
{
    scheduleLoaded = false;
    schedule = attachSchedule;
    savedir = attachSaveDir;
    exportdir = attachExportDir;

}

void MainWindow::on_actionNew_Schedule_triggered()
{
    NewSchedule n;
    n.init(schedule,savedir,exportdir,&scheduleLoaded);
    n.exec();//Force user to accept something
}

void MainWindow::on_actionExport_xls_triggered()
{
    //Make sure a schedule is loaded
    if(scheduleLoaded)
    {
        workbook wb;
        scheduleToXLS(*schedule,wb);
        std::string exportpath = (Parser::stringReplaceAll((std::string)"\\",(std::string)"/",*exportdir) + "/" + schedule->getName() + ".xls" );
        wb.Dump(exportpath);
        ui->statusBar->showMessage("Schedule exported to " + QString::fromStdString(exportpath),0);
    }
}

void MainWindow::updateMenu()
{
    //Grey out "Export .xls" if schedule not loaded
    ui->actionExport_xls->setEnabled(scheduleLoaded);
    ui->actionSave_Schedule->setEnabled(scheduleLoaded);
}
