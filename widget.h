#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTextBrowser>
#include <QProcess>

#include "portcombobox.h"
#include "filelineedit.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void doDownload();
    void doReadSTCFlash();
    void doStopProcess();
    void enablePushButtonStop();
    void disablePushButtonStop();

private:

    QLabel       *labelLogo;

    QLabel       *labelProtocol;
    QComboBox    *comboBoxProtocol;

    QLabel       *labelBaudRate;
    QComboBox    *comboBoxBaudRate;

    QLabel       *labelPort;
    PortComboBox *comboBoxPort;
    QPushButton  *pushButtonScan;

    QLabel       *labelFile;
    FileLineEdit *lineEditFile;
    QPushButton  *pushButtonFile;

    QPushButton  *pushButtonDownload;
    QPushButton  *pushButtonStop;
    QPushButton  *pushButtonClose;

    QTextBrowser *textBrowserSTCFlash;

    QHBoxLayout  *hBoxLayoutProtocolBaud;
    QHBoxLayout  *hBoxLayoutBottomButtons;
    QGridLayout  *gridLayoutMain;

    QProcess     *processSTCFalsh;
};

#endif // WIDGET_H
