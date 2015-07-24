#include "newrotators.h"
#include "ui_newrotators.h"

#include <QLineEdit>

#include <string>
#include <sstream>
#include <vector>

NewRotators::NewRotators(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRotators)
{
    ui->setupUi(this);
}

NewRotators::~NewRotators()
{
    delete ui;

    //Delete each lineEdit
    for(int i = 0; i < studentNames->size(); i++)
    {
        delete nameEdits[i];
    }
    delete[] nameEdits;
}

void NewRotators::init(std::vector<std::string> *studentNameVector)
{
    studentNames = studentNameVector;
    nameEdits = new QLineEdit* [studentNames->size()];

    for(int i = 0; i <studentNames->size(); i++)
    {
        nameEdits[i] = new QLineEdit(this);
    }

    //Initialize names
    QString name;
    std::stringstream sstream;
    for(int i = 0; i < studentNames->size(); i++)
    {
        if((*studentNameVector)[i] == "")
        {
            sstream.str("");
            sstream<<std::dec<<"Student "<<(i+1)<<"'s name";
            name = QString::fromStdString(sstream.str());
        }
        else
        {
            name = QString::fromStdString((*studentNameVector)[i]);
        }
        nameEdits[i]->setText(name);
    }

    int x,y;
    //Placement of lineEdits
    for(int i = 0; i < studentNames->size(); i++)
    {
        x = 20;
        y = 20 + nameEdits[i]->height() * (i/2);
        if(i%2)
        {
            x += nameEdits[i]->width() + nameEdits[i]->width()/2;
        }

        nameEdits[i]->move(x,y);
        nameEdits[i]->show();
    }

    x = 20 + nameEdits[0]->width() * 2 + nameEdits[0]->width()/2;
    y = (10 + nameEdits[0]->height()) * studentNames->size() / 2  + ui->buttonBox->height() + 30;
    resize(x,y);

    x = width()-10 - (ui->buttonBox->width());
    //y = nameEdits[studentNames->size() - 1]->y() + nameEdits[studentNames->size() - 1]->height() + 10;
    y = height()-10-(ui->buttonBox->height());
    ui->buttonBox->move(x,y);
}

void NewRotators::on_buttonBox_accepted()
{
    for(int i = 0; i < studentNames->size(); i++)
    {
        //Enter names into the vector
        (*studentNames)[i] = nameEdits[i]->text().toStdString();
    }
}
