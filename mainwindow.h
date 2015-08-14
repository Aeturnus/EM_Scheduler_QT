#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include <string>

#include "../EM_Scheduler/Scheduler.h"
#include "displayschedule.h"
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

    void on_actionOpen_Schedule_triggered();

    void on_actionSave_Schedule_triggered();

    void on_actionSave_As_triggered();

    void on_actionExport_as_triggered();

    void on_actionAuto_Assign_triggered();

    void on_actionPreferences_triggered();

    void on_actionSettings_triggered();

    void on_actionAuto_Block_triggered();

    void on_pushButtonNew_clicked();

    void on_pushButtonOpen_clicked();

    void on_actionAuto_triggered();

    void on_actionView_open_shifts_triggered();

    void on_actionManual_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    void resizeEvent(QResizeEvent *event);

    void resizeScrollArea(void);

    QScrollArea* scrollArea;

    Scheduler* schedule;
    std::string* savedir;
    std::string* exportdir;

    std::string savepath;
    std::string exportpath;

    DisplaySchedule* display;
    bool scheduleLoaded;
    bool displayAllocated;

    void newSchedule(void);
    void open(void);
    void save(void);
    void saveAs(void);
    void exportNormal(void);
    void exportAs(void);



};

#endif // MAINWINDOW_H
