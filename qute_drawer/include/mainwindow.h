#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "renderarea.h"

class QAction;
class QMenu;
class QScrollArea;
class QScrollBar;

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void changePen();
    void about();

private:
    void createActions();
    Ui::MainWindow *ui;
    RenderArea *renderArea;
    QActionGroup *drawGroup;
};

#endif

