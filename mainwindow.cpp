#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../EM_Scheduler/Scheduler.h"
#include "../EM_Scheduler/Student.h"
#include "../EM_Scheduler/Date.h"
#include "../EM_Scheduler/Shift.h"
#include "../EM_Scheduler/Parser.h"
#include "../EM_Scheduler/xlsoutput.h"

#include "newschedule.h"
#include "editpreferences.h"
#include "editschedule.h"
#include "showunassigned.h"

#include <xlslib.h>
#include <xlslib/common.h>

#include <QDir>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QScrollArea>
#include <QScrollBar>

#include <QDesktopServices>

#include <QImage>
#include <QPainter>
#include <QPrinter>

#include <string>
#include <ostream>
#include <istream>

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
    delete display;
}

void MainWindow::init(Scheduler *attachSchedule, string *attachSaveDir, string *attachExportDir)
{
    this->setWindowState(Qt::WindowMaximized);
    scheduleLoaded = false;
    display = new DisplaySchedule(this);
    //display->setBackgroundRole(QPalette::Dark);
    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(display);
    display->show();

    resizeScrollArea();
    scrollArea->show();

    schedule = attachSchedule;
    savedir = attachSaveDir;
    exportdir = attachExportDir;
    *savedir = "C:/EM_Scheduler/schedules";
    *exportdir = "C:/EM_Scheduler/spreadsheets";
    //Create paths
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

    updateMenu();
}

void MainWindow::on_actionNew_Schedule_triggered()
{
    newSchedule();
}

void MainWindow::on_actionExport_xls_triggered()
{
    exportNormal();
}

void MainWindow::updateMenu()
{
    //Grey out schedule related options if not loaded
    ui->actionExport_as->setEnabled(scheduleLoaded);
    ui->actionExport_xls->setEnabled(scheduleLoaded);
    ui->actionSave_Schedule->setEnabled(scheduleLoaded);
    ui->actionSave_As->setEnabled(scheduleLoaded);
    ui->menuSchedule->setEnabled(scheduleLoaded);

    if(!scheduleLoaded)
    {
        display->hide();
        scrollArea->hide();
        ui->pushButtonNew->move(this->width()/2 - ui->pushButtonNew->width()/2, ui->centralWidget->height()/2 - ui->pushButtonNew->height());
        ui->pushButtonOpen->move(this->width()/2 - ui->pushButtonOpen->width()/2, ui->centralWidget->height()/2 + 20);
        ui->pushButtonNew->show();
        ui->pushButtonOpen->show();
    }
    else
    {
        display->show();
        scrollArea->show();
        ui->pushButtonNew->hide();
        ui->pushButtonOpen->hide();
    }

}

void MainWindow::on_actionOpen_Schedule_triggered()
{
    open();
}

void MainWindow::on_actionSave_Schedule_triggered()
{
    save();
}

void MainWindow::open(void)
{
    QString dirPath = QString::fromStdString((*savedir));
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Schedule"),dirPath,tr("Schedule files (*.schd);;All files (*.*)"));
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
            return;
        }

        //Delete up here; display requires old schedule pointer to work
        if(scheduleLoaded)
        {
            delete display;
        }

        ui->statusBar->showMessage("Schedule loaded from " + fileName);
        scheduleLoaded = true;
        ifstream filei;
        filei.open(fileName.toStdString(), ios_base::in | ios_base::binary);//Binary mode so it doesn't reach premature EOF
        schedule->streamInBinary(filei);
        filei.close();
        savepath = fileName.toStdString();
        exportpath = (Parser::stringReplaceAll((std::string)"\\",(std::string)"/",*exportdir) + "/" + schedule->getName() + ".xls" );



        display = new DisplaySchedule(this);
        display->init(schedule);
        scrollArea->setWidget(display);
        display->show();
    }
    updateMenu();
}

void MainWindow::save(void)
{
    if(scheduleLoaded)
    {
        //std::string savepath = (Parser::stringReplaceAll((std::string)"\\",(std::string)"/",*savedir) + "/" + schedule->getName() + ".schd" );
        ofstream fileo;
        fileo.open(savepath, ios_base::out | ios_base::binary);
        if(fileo.is_open())
        {
            schedule->streamOutBinary(fileo);
            ui->statusBar->showMessage("Schedule saved to " + QString::fromStdString(savepath),0);
        }
        else
        {
            ui->statusBar->showMessage("ERROR saving schedule to" + QString::fromStdString(savepath),0);
        }
        fileo.close();
    }
}

void MainWindow::saveAs(void)
{
    if(!scheduleLoaded)
        return;
    QString dirPath = QString::fromStdString((*savedir)) +"/"+ QString::fromStdString(schedule->getName());
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Schedule"),dirPath,tr("Schedule files (*.schd);;All files (*.*)"));
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not write to file"));
            return;
        }
        ui->statusBar->showMessage("Schedule saved to " + fileName);

        ofstream fileo;
        fileo.open(fileName.toStdString(), ios_base::out | ios_base::binary);
        schedule->streamOutBinary(fileo);
        fileo.close();
    }
    savepath = fileName.toStdString();
}
void MainWindow::exportNormal(void)
{
    //Make sure a schedule is loaded
    if(scheduleLoaded)
    {
        workbook wb;
        scheduleToXLS(*schedule,wb);
        //exportpath = (Parser::stringReplaceAll((std::string)"\\",(std::string)"/",*exportdir) + "/" + schedule->getName() + ".xls" );
        wb.Dump(exportpath);
        ui->statusBar->showMessage("Schedule exported to " + QString::fromStdString(exportpath),0);
    }
    QDesktopServices::openUrl(QString::fromStdString(*exportdir));
}

void MainWindow::exportAs(void)
{
    //Make sure a schedule is loaded
    if(scheduleLoaded)
    {
        QString dirPath = QString::fromStdString((*exportdir)) +"/"+ QString::fromStdString(schedule->getName());
        QString fileName = QFileDialog::getSaveFileName(this,tr("Export as..."),dirPath,tr("Excel 97-2003 (*.xls);;PNG (Portable Netowrk Graphics) (*.png);;Windows bitmap (*.bmp);; JPEG (*.jpeg);; PDF (experimental!) (*.pdf)"));
        if(!fileName.isEmpty())
        {
            QFile file(fileName);
            if(!file.open(QIODevice::WriteOnly))
            {
                QMessageBox::critical(this,tr("Error"),tr("Could not write to file"));
                return;
            }

            //What file type?
            if(fileName.endsWith(".xls"))
            {
                workbook wb;
                scheduleToXLS(*schedule,wb);
                wb.Dump(fileName.toStdString());
                ui->statusBar->showMessage("Schedule exported to " + fileName,0);
                exportpath = fileName.toStdString();
            }
            else if (fileName.endsWith(".png") || fileName.endsWith(".jpeg") || fileName.endsWith(".jpg") || fileName.endsWith(".bmp"))
            {
                //display->grab().save(fileName);
                display->grab().toImage().save(fileName,0,-1);
            }
            else if (fileName.endsWith(".pdf"))
            {
                //PDF handling
                QImage image = display->grab().toImage();

                QPrinter printer(QPrinter::HighResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(fileName);

                QPainter painter(&printer);
                painter.drawImage(0,0,image);
                painter.end();
            }
            QDesktopServices::openUrl(file.fileName().remove(file.fileName().lastIndexOf('/'),file.fileName().length()-file.fileName().lastIndexOf('/')));
        }
    }
}

void MainWindow::newSchedule(void)
{
    bool result = false;    //Temporarily give a result variable

    NewSchedule n;
    n.init(schedule,savedir,exportdir,&result);
    n.exec();//Force user to accept something
    if(result)
    {
        savepath = *savedir + "/" + schedule->getName() + ".schd";
        exportpath = *exportdir + "/" + schedule->getName() + ".xls";
        updateMenu();

        //If there is already a schedule loaded, delete this
        if(scheduleLoaded)
        {
            delete display;
        }
        display = new DisplaySchedule(this);
        display->init(schedule);
        scrollArea->setWidget(display);
        display->show();
    }

    scheduleLoaded = result;

    updateMenu();
}

void MainWindow::on_actionSave_As_triggered()
{
    saveAs();
}

void MainWindow::on_actionExport_as_triggered()
{
    exportAs();
}

void MainWindow::on_actionAuto_Assign_triggered()
{
    //QDialog d;
    //d.setWindowTitle("Autoassigning...");
    //d.resize(d.width(),0);
    //d.show();
    ui->statusBar->showMessage("Autoassigning...");
    schedule->autoassign();
    display->update();
    ui->statusBar->showMessage("Autoassign complete");
    //d.close();
}

void MainWindow::on_actionPreferences_triggered()
{
    EditPreferences e;
    e.init(savedir,&savepath,exportdir,&exportpath);
    e.exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    resizeScrollArea();
}

void MainWindow::resizeScrollArea(void)
{
    scrollArea->move(0,ui->menuBar->height()+ui->mainToolBar->height());
    scrollArea->resize(width(),height() - ui->mainToolBar->height() - scrollArea->horizontalScrollBar()->height() - ui->statusBar->height());

    ui->pushButtonNew->move(this->width()/2 - ui->pushButtonNew->width()/2, ui->centralWidget->height()/2 - ui->pushButtonNew->height());
    ui->pushButtonOpen->move(this->width()/2 - ui->pushButtonOpen->width()/2, ui->centralWidget->height()/2 + 20);

}

void MainWindow::on_actionSettings_triggered()
{
    EditSchedule e;
    e.init(schedule);
    e.exec();
    display->update();
}

void MainWindow::on_actionAuto_Block_triggered()
{
    schedule->autoblock();
    display->update();
}


void MainWindow::on_pushButtonNew_clicked()
{
    newSchedule();
}

void MainWindow::on_pushButtonOpen_clicked()
{
    open();
}

void MainWindow::on_actionAuto_triggered()
{
    //on_actionAuto_Block_triggered();
    schedule->autoblock();
    on_actionAuto_Assign_triggered();
}

void MainWindow::on_actionView_open_shifts_triggered()
{
    ShowUnassigned s;
    s.init(schedule);
    s.exec();
    display->update();
}

void MainWindow::on_actionManual_triggered()
{

    QDesktopServices::openUrl(QDir::currentPath() + QString::fromStdString("/manual/UserManual.pdf"));
}



void MainWindow::on_actionAbout_triggered()
{
    QDialog x;
    x.setWindowTitle("About");
    QLabel l1(&x);
    //l1.resize(300,20);
    QLabel l2(&x);
    //l2.resize(300,20);
    QLabel l3(&x);
    //l3.resize(300,20);
    QLabel l4(&x);
    //l4.resize(300,20);
    QLabel l5(&x);
    //l5.resize(300,20);

    l1.setText("EM Scheduler (Qt) Version 1.01");
    l1.adjustSize();
    l1.move(10,10);

    l2.setText("by Brandon Nguyen");
    l2.adjustSize();
    l2.move(10,l1.y() + l1.height() + 10);

    l3.setText("<a href=\"http://brandontnguyen.com\">brandontnguyen.com</a>");
    l3.setTextFormat(Qt::RichText);
    l3.setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    l3.setOpenExternalLinks(true);
    l3.adjustSize();
    l3.move(10,l2.y() + l2.height() + 0);

    l4.setText("<a href=\"mailto:brandon.t.nguyen@utexas.edu\">brandon.t.nguyen@utexas.edu</a>");
    l4.setTextFormat(Qt::RichText);
    l4.setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    l4.setOpenExternalLinks(true);
    l4.adjustSize();
    l4.move(10,l3.y() + l3.height() + 0);

    l5.setText("Source repository: <a href=\"http://github.com/Aeturnus/EM_Scheduler_QT\">github.com/Aeturnus/EM_Scheduler_QT</a>");
    l5.setTextFormat(Qt::RichText);
    l5.setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    l5.setOpenExternalLinks(true);
    l5.move(10,l4.y() + l4.height() + 10);
    l5.adjustSize();


    x.resize(10 + l5.width() + 10, l5.height() + l5.y() + 10);
    x.exec();
}
