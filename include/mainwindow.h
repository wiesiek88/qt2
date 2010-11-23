/* Viewer  -- nowy plik */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>

class QLabel;
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
    #ifdef VIEWER
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

    void greyScale();
    void negative();
    void gradient();
    void hMirror();
    void vMirror();
    #else
    void changePen();
    #endif
    void about();

private:
    void createActions();
    Ui::MainWindow *ui;
    
    #ifdef VIEWER
    void mirror(bool hori);
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
    #else
    RenderArea *renderArea;
    QActionGroup *drawGroup;
    #endif
};

#endif

