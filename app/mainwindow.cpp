#include <QtGui>
#include <QPainter>
#include <QtHelp/QHelpEngine>
#include "helpbrowser.h"

#include "mainwindow.h"
#ifdef VIEWER
#include "ui_viewerwindow.h"
#else
#include "ui_drawerwindow.h"
#endif

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->helpWindow->setVisible(false);

    #ifdef VIEWER
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    setWindowTitle(tr("QuTe Viewer"));
    resize(500, 400);
    #else
    renderArea = new RenderArea();\
    setCentralWidget(renderArea);

    createActions();
    setWindowTitle(tr("QuTe Drawer"));
    resize(500, 400);
    #endif

    // help window
    QHelpEngine *helpEngine = new QHelpEngine(DOCS_PATH, this);
    helpEngine->setupData();

    QSplitter *helpPanel = new QSplitter(Qt::Horizontal);
    HelpBrowser *helpBrowser = new HelpBrowser(helpEngine);

    helpPanel->addWidget((QWidget*)helpEngine->contentWidget());
    helpPanel->addWidget(helpBrowser);
    helpPanel->setStretchFactor(1, 1);
    ui->helpWindow->setWidget(helpPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::about()
{
    #ifdef VIEWER
    QMessageBox::about(this, tr("About QuTe Viewer"),
            tr("<b>QuTe Viewer</b><br/>Version: 0.2.0 23-11-2010"));
    #else
    QMessageBox::about(this, tr("About QuTe Drawer"),
            tr("<b>QuTe Drawer</b><br/>Version: 0.2.0 23-11-2010"));
    #endif
}

#ifdef VIEWER
void MainWindow::createActions()
{
    connect(ui->openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->exitAct, SIGNAL(triggered()), this, SLOT(close()));

    ui->zoomInAct->setEnabled(false);
    connect(ui->zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    ui->zoomOutAct->setEnabled(false);
    connect(ui->zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    ui->normalSizeAct->setEnabled(false);
    connect(ui->normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    ui->fitToWindowAct->setEnabled(false);
    ui->fitToWindowAct->setCheckable(true);
    connect(ui->fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    ui->greyscaleAct->setEnabled(false);
    connect(ui->greyscaleAct, SIGNAL(triggered()), this, SLOT(greyScale()));

    ui->negativeAct->setEnabled(false);
    connect(ui->negativeAct, SIGNAL(triggered()), this, SLOT(negative()));

    ui->gradientAct->setEnabled(false);
    connect(ui->gradientAct, SIGNAL(triggered()), this, SLOT(gradient()));

    ui->hMirrorAct->setEnabled(false);
    connect(ui->hMirrorAct, SIGNAL(triggered()), this, SLOT(hMirror()));

    ui->vMirrorAct->setEnabled(false);
    connect(ui->vMirrorAct, SIGNAL(triggered()), this, SLOT(vMirror()));

    connect(ui->aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    connect(ui->helpAct, SIGNAL(triggered()), ui->helpWindow, SLOT(show()));
    connect(ui->helpWindow, SIGNAL(visibilityChanged(bool)),
            ui->helpAct, SLOT(setDisabled(bool)));
}


void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        image.load(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                    tr("Cannot load %1.").arg(fileName));
            return;
        }
        
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        ui->fitToWindowAct->setEnabled(true);
        updateActions();

        if (!ui->fitToWindowAct->isChecked())
            imageLabel->adjustSize();
    }
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void MainWindow::fitToWindow()
{
    bool fitToWindow = ui->fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void MainWindow::greyScale()
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++) {
            QRgb value;
            int newValue;
            value = image.pixel(QPoint(x,y));
            newValue = (qRed(value) + qGreen(value) + qBlue(value)) / 3;
            image.setPixel(x,y,qRgb(newValue, newValue, newValue));
        }
    }

    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::negative()
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++) {
            QRgb value;
            value = image.pixel(QPoint(x,y));
            image.setPixel(x,y,qRgb(255 - qRed(value), 255 - qGreen(value), 255 - qBlue(value)));
        }
    }

    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::gradient()
{
    QPoint start(0,0);
    QPoint end(0, image.height());
    QLinearGradient gradient(start, end);
    gradient.setColorAt(0.5, Qt::black);
    gradient.setColorAt(0, Qt::white);
    QImage mask = image;
    QPainter painter(&mask);
    painter.fillRect(image.rect(), gradient);
    painter.end();

    image.setAlphaChannel(mask);

    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::hMirror()
{
    mirror(true);
}

void MainWindow::vMirror()
{
    mirror(false);
}

void MainWindow::mirror(bool hori)
{
    image = image.mirrored(hori, !hori);
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::updateActions()
{
    ui->zoomInAct->setEnabled(!ui->fitToWindowAct->isChecked());
    ui->zoomOutAct->setEnabled(!ui->fitToWindowAct->isChecked());
    ui->normalSizeAct->setEnabled(!ui->fitToWindowAct->isChecked());
    ui->greyscaleAct->setEnabled(true);
    ui->negativeAct->setEnabled(true);
    ui->gradientAct->setEnabled(true);
    ui->hMirrorAct->setEnabled(true);
    ui->vMirrorAct->setEnabled(true);
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    ui->zoomInAct->setEnabled(scaleFactor < 3.0);
    ui->zoomOutAct->setEnabled(scaleFactor > 0.333);
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
#else
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

    connect(ui->helpAct, SIGNAL(triggered()), ui->helpWindow, SLOT(show()));
    connect(ui->helpWindow, SIGNAL(visibilityChanged(bool)),
            ui->helpAct, SLOT(setDisabled(bool)));
}

void MainWindow::changePen()
{
    RenderArea::Shape shape = RenderArea::Shape(drawGroup->checkedAction()->data().toInt());
    renderArea->setShape(shape);
}
#endif /* VIEWER */
