#include <QtGui>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderArea = new RenderArea();\
    setCentralWidget(renderArea);

    createActions();

    setWindowTitle(tr("QuTe Viewer"));
    resize(500, 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changePen()
{
    RenderArea::Shape shape = RenderArea::Shape(drawGroup->checkedAction()->data().toInt());
    renderArea->setShape(shape);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About QuTe Drawer"),
            tr("<b>QuTe Drawer</b><br/>Version: 0.1.1 23-11-2010"));
}

void MainWindow::createActions()
{
    connect(ui->exitAct, SIGNAL(triggered()), this, SLOT(close()));

    drawGroup = new QActionGroup(this);
    ui->lineAct->setCheckable(true);
    ui->lineAct->setData(RenderArea::Line);
    ui->rectAct->setCheckable(true);
    ui->rectAct->setData(RenderArea::Rect);
    ui->roundRectAct->setCheckable(true);
    ui->roundRectAct->setData(RenderArea::RoundRect);
    ui->ellipseAct->setCheckable(true);
    ui->ellipseAct->setData(RenderArea::Ellipse);
    
    drawGroup->addAction(ui->lineAct);
    drawGroup->addAction(ui->rectAct);
    drawGroup->addAction(ui->roundRectAct);
    drawGroup->addAction(ui->ellipseAct);
    ui->lineAct->setChecked(true);
    connect(drawGroup, SIGNAL(triggered(QAction*)), this, SLOT(changePen()));
    
    connect(ui->aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}
