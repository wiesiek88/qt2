#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#include <QDialog>
#include <QTimer>
#include <QStateMachine>
#include <QPropertyAnimation>

namespace Ui {
    class AboutBox;
}

class AboutBox : public QDialog
{
    Q_OBJECT

public:
    explicit AboutBox(QString title, QString version, QString copyright = "(C) 2010-2011 Dream Team Software", QWidget *parent = 0);
    ~AboutBox();

private:
    Ui::AboutBox *ui;
    QPropertyAnimation * animation;
    QTimer * timer;
    QStateMachine * machine;
    void showEvent(QShowEvent * event);
};

#endif // ABOUTBOX_H
