#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <qtextcodec.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString locale = QLocale::system().name();

    QTranslator translator;
    #ifdef VIEWER
    translator.load(QString("lang/qute_viewer_") + locale);
    #else
    translator.load(QString("lang/qute_drawer_") + locale);
    #endif
    app.installTranslator(&translator);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
