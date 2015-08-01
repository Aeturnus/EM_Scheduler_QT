#include "editpreferences.h"
#include "ui_editpreferences.h"

#include "../EM_Scheduler/Student.h"

#include <QString>

EditPreferences::EditPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPreferences)
{
    ui->setupUi(this);
}

EditPreferences::~EditPreferences()
{
    delete ui;
}

EditPreferences::init(std::string *saved, std::string *savep, std::string *exportd, std::string *exportp)
{
    savedir = saved;
    savepath = savep;
    exportdir = exportd;
    exportpath = exportp;

    ui->lineEdit_SaveDir->setText(QString::fromStdString(*savedir));
    ui->lineEdit_SavePath->setText(QString::fromStdString(*savepath));
    ui->lineEdit_ExportDir->setText(QString::fromStdString(*exportdir));
    ui->lineEdit_ExportPath->setText(QString::fromStdString(*exportpath));
}

void EditPreferences::on_buttonBox_accepted()
{
    *savedir = ui->lineEdit_SaveDir->text().toStdString();
    *savepath = ui->lineEdit_SavePath->text().toStdString();
    *exportdir = ui->lineEdit_ExportDir->text().toStdString();
    *exportpath= ui->lineEdit_ExportPath->text().toStdString();
}
