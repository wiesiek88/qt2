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
    translator.load(QString("qute_drawer_") + locale);
    app.installTranslator(&translator);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
