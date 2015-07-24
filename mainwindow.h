#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

#include "../EM_Scheduler/Scheduler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init(Scheduler* attachSchedule,std::string* attachSaveDir, std::string* attachExportDir);

private slots:
    void on_actionNew_Schedule_triggered();

    void on_actionExport_xls_triggered();

    void updateMenu();

private:
    Ui::MainWindow *ui;

    Scheduler* schedule;
    std::string* savedir;
    std::string* exportdir;

    bool scheduleLoaded;




};

#endif // MAINWINDOW_H
