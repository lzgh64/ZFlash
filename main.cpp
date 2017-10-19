#include "widget.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include <QIcon>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

//    if ("zh" == QLocale::system().name()) {
        QTranslator *translator = new QTranslator;
        translator->load("zh.qm", ".");
        a.installTranslator(translator);
//    }

    w.show();

    return a.exec();
}
