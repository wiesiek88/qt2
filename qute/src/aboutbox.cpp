#include "aboutbox.h"
#include "ui_aboutbox.h"

AboutBox::AboutBox(QString title, QString version, QString copyright, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutBox)
{
    ui->setupUi(this);
    ui->title->setText(title);
    ui->version->setText(version);
    ui->copyright->setText(copyright);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));
}

AboutBox::~AboutBox()
{
    delete ui;
}
