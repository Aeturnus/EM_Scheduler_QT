#include "mainwindow.h"
#include "newschedule.h"
#include <QApplication>
#include <QDir>

#include <iostream>
#include <string>

//#include "../EM_Scheduler/xlsoutput.h"
#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Date.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Parser.h"
#include <xlslib.h>
#include <xlslib/common.h>


#define TEST 1

#define BUILD 0

using namespace std;
using namespace xlslib_core;
int main(int argc, char *argv[])
{
    Scheduler schedule;
    string savedir;
    string exportdir;
    workbook wb;

    QApplication a(argc, argv);
    MainWindow w;
    w.init(&schedule,&savedir,&exportdir);
    w.show();

    #if(BUILD == TEST)
    //Testing
    schedule.autoblock();
    schedule.autoassign();
    scheduleToXLS(schedule,wb);

    //Export test
    wb.Dump(exportdir + "\\" + schedule.getName() + ".xls");

    #endif


    return a.exec();
}
