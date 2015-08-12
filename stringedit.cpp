#include "stringedit.h"
#include "ui_stringedit.h"

#include <QString>

#include <string>

StringEdit::StringEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StringEdit)
{
    ui->setupUi(this);
}

StringEdit::~StringEdit()
{
    delete ui;
}

void StringEdit::init(std::string *attachString, std::string title)
{
    stringEdit = attachString;
    this->setWindowTitle(QString::fromStdString(title));
    ui->lineEdit->setText(QString::fromStdString(*stringEdit));
}

void StringEdit::on_buttonBox_accepted()
{
    *stringEdit = ui->lineEdit->text().toStdString();
}
