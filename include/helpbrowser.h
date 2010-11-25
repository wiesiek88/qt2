#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextBrowser>

class QHelpEngine;

class HelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    HelpBrowser(QHelpEngine *helpEngine, QWidget *parent = 0);
    QVariant loadResource(int type, const QUrl &url);

private:
    QHelpEngine *helpEngine;
};

#endif
