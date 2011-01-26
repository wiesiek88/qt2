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

    animation = new QPropertyAnimation(ui->pushButton,"geometry");
}

AboutBox::~AboutBox()
{
    delete ui;
}

void AboutBox::showEvent(QShowEvent * event)
{

    animation->setDuration(2000);
    animation->setStartValue(QRect(0, 0, 100, 30));
    animation->setEndValue(QRect(250, 220, 100, 30));

    animation->start();
}
