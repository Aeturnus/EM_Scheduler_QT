#ifndef NEWSCHEDULE_H
#define NEWSCHEDULE_H

#include <QDialog>

#include <string>
#include <vector>
#include "../EM_Scheduler/Scheduler.h"



namespace Ui {
class NewSchedule;
}

class NewSchedule : public QDialog
{
    Q_OBJECT

public:
    explicit NewSchedule(QWidget *parent = 0);
    ~NewSchedule();
    void init(Scheduler* attachSchedule, std::string* attachSaveDir, std::string* attachExportDir, bool* attachSuccess);

private slots:

    void on_checkBox_AdvMode_stateChanged(int arg1);

    void on_buttonBox_accepted();


    void on_lineEdit_NameSchedule_textChanged(const QString &arg1);

    void on_toolButton_StartDate_clicked();

    void on_toolButton_EndDate_clicked();

    void on_dateEdit_Start_dateChanged(const QDate &date);

    void on_toolButton_StudentNames_clicked();

private:
    Ui::NewSchedule *ui;

    bool advmode;
    std::vector<std::string> studentNameVector;
    std::vector<std::string> shiftNameVector;
    std::vector<std::vector<int>> shiftTimeVector;

    //Attach points
    Scheduler* schedule;
    std::string* savedir;
    std::string* exportdir;

    bool* success;


    //Functions
    void updateAdv(void);
    void updateButtonBox(void);

    void adjustStudentNameVector(void);
    void adjustShiftVector(void);

};

#endif // NEWSCHEDULE_H
