#include "widget.h"

#include <QList>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include <QSizePolicy>
#include <QPalette>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    /* Logo Area */
    labelLogo = new QLabel(this);
    labelLogo->setPixmap(QPixmap("./images/cdutosalogo.png"));

    /* STCFlash Output area */
    textBrowserSTCFlash = new QTextBrowser(this);
    textBrowserSTCFlash->append(tr("Author: Dawn"));
    textBrowserSTCFlash->append(tr("Base on stcflash project."));
    textBrowserSTCFlash->append("");
    textBrowserSTCFlash->append(tr("The following is a table of protocols and corresponding MCUs that have been tested working with each protocol."));
    textBrowserSTCFlash->append("");
    textBrowserSTCFlash->append(tr("Protocol | MCUs"));
    textBrowserSTCFlash->append("---------|--------------------------------");
    textBrowserSTCFlash->append("89       | STC89C52RC (v4.3C), STC89C54RD+ (v4.3C), STC90C52RC (v4.3C)");
    textBrowserSTCFlash->append("12cx052  | STC12C2052 (v5.8D)");
    textBrowserSTCFlash->append("12c52    | STC12C5608AD (v6.0G), STC12C5204AD (v6.0H)");
    textBrowserSTCFlash->append("12c5a    | STC10F04XE (v6.5J), STC12C5A16S2 (v6.2I),  STC11F02E (v6.5K)");
    textBrowserSTCFlash->append("\n");

    processSTCFalsh = new QProcess(this);

    /* Protocol Selection Area */
    labelProtocol = new QLabel(this);
    labelProtocol->setText(tr("Protocol"));

    comboBoxProtocol = new QComboBox(this);
    comboBoxProtocol->addItem("89");
    comboBoxProtocol->addItem("12cx052");
    comboBoxProtocol->addItem("12c52");
    comboBoxProtocol->addItem("12c5a");

    /* Buad Rate Selection Area */
    labelBaudRate = new QLabel(this);
    labelBaudRate->setText(tr("Buad Rate"));

    comboBoxBaudRate = new QComboBox(this);
    QStringList baudList;
    baudList << "1200" << "2400" << "4800"
             << "9600" << "14400" << "19200"
             << "28800" << "38400" << "57600"
             << "115200";
    comboBoxBaudRate->addItems(baudList);
    comboBoxBaudRate->setCurrentIndex(1);

    /* Port Selection Area */
    labelPort = new QLabel(this);
    labelPort->setText(tr("Port"));

    comboBoxPort = new PortComboBox(this);
//    comboBoxPort->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    pushButtonScan = new QPushButton(this);
    pushButtonScan->setText(tr("Scan"));
    pushButtonScan->setEnabled(true);
    pushButtonScan->setFixedHeight(24);

    /* File Select Area */
    labelFile = new QLabel(this);
    labelFile->setText(tr("File"));

    lineEditFile = new FileLineEdit(this);
//    lineEditFile->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    pushButtonFile = new QPushButton(this);
    pushButtonFile->setText(tr("Select"));
    pushButtonFile->setFixedHeight(24);

    /* Download & Close Push Button Area */
    pushButtonDownload = new QPushButton(this);
    pushButtonDownload->setText(tr("Download"));

    pushButtonStop = new QPushButton(this);
    pushButtonStop->setText(tr("Stop"));

    pushButtonClose = new QPushButton(this);
    pushButtonClose->setText(tr("Close"));

    /* Connect Signal & Slot */
    connect(pushButtonScan, SIGNAL(clicked()),
            comboBoxPort, SLOT(doPortScan()));

    connect(pushButtonFile, SIGNAL(clicked()),
            lineEditFile, SLOT(doSelectFile()));

    connect(pushButtonDownload, SIGNAL(clicked(bool)),
            this, SLOT(doDownload()));
    connect(pushButtonDownload, SIGNAL(clicked(bool)),
            this, SLOT(enablePushButtonStop()));

    connect(pushButtonStop, SIGNAL(clicked(bool)),
            this, SLOT(doStopProcess()));
    connect(pushButtonStop, SIGNAL(clicked(bool)),
            this, SLOT(disablePushButtonStop()));

    connect(pushButtonClose, SIGNAL(clicked(bool)),
            this, SLOT(close()));

    connect(processSTCFalsh, SIGNAL(readyReadStandardOutput()),
            this, SLOT(doReadSTCFlash()));
    connect(processSTCFalsh, SIGNAL(finished(int)),
            this, SLOT(disablePushButtonStop()));

    /* Layout Setting */
    gridLayoutMain = new QGridLayout(this);

    /* Init Push Buttons' status */
    disablePushButtonStop();

    // Line 0
    gridLayoutMain->addWidget(labelLogo, 0, 0, 1, 4, Qt::AlignCenter);

    gridLayoutMain->setRowStretch(0, 0);

    // Line 1
    gridLayoutMain->addWidget(textBrowserSTCFlash, 1, 0, 1, 4);

    gridLayoutMain->setRowStretch(1, 1);

    // Line 2
    hBoxLayoutProtocolBaud = new QHBoxLayout(this);

    hBoxLayoutProtocolBaud->addWidget(labelProtocol,    0, Qt::AlignLeft);
    hBoxLayoutProtocolBaud->addWidget(comboBoxProtocol, 1);

    hBoxLayoutProtocolBaud->addSpacing(12);

    hBoxLayoutProtocolBaud->addWidget(labelBaudRate,    0, Qt::AlignRight);
    hBoxLayoutProtocolBaud->addWidget(comboBoxBaudRate, 1);

    gridLayoutMain->addLayout(hBoxLayoutProtocolBaud, 2, 0, 1, 4);

    gridLayoutMain->setRowStretch(2, 0);

    // Line 3
    gridLayoutMain->addWidget(labelPort,      3, 0, 1, 1, Qt::AlignLeft);
    gridLayoutMain->addWidget(comboBoxPort,   3, 1, 1, 2);
    gridLayoutMain->addWidget(pushButtonScan, 3, 3, 1, 1, Qt::AlignLeft);

    gridLayoutMain->setRowStretch(3, 0);

    // Line 4
    gridLayoutMain->addWidget(labelFile,      4, 0, 1, 1, Qt::AlignLeft);
    gridLayoutMain->addWidget(lineEditFile,   4, 1, 1, 2);
    gridLayoutMain->addWidget(pushButtonFile, 4, 3, 1, 1, Qt::AlignLeft);

    gridLayoutMain->setRowStretch(4, 0);

    // Line 5
    hBoxLayoutBottomButtons = new QHBoxLayout(this);
    hBoxLayoutBottomButtons->addWidget(pushButtonDownload);
    hBoxLayoutBottomButtons->addWidget(pushButtonStop);
    hBoxLayoutBottomButtons->addWidget(pushButtonClose);

    gridLayoutMain->addLayout(hBoxLayoutBottomButtons,
                              5, 0, 1, 4, Qt::AlignCenter);

    gridLayoutMain->setRowStretch(5, 0);

    // Set Column Stretch
    gridLayoutMain->setColumnStretch(0, 0);
    gridLayoutMain->setColumnStretch(1, 1);
    gridLayoutMain->setColumnStretch(2, 0);

    // Set Main Layout
    setLayout(gridLayoutMain);

    // Set This Widget
    setFixedSize(400, 550);
    QPalette paletteBackgroud;
    paletteBackgroud.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(paletteBackgroud);
}

Widget::~Widget()
{
    delete labelLogo;

    delete labelProtocol;
    delete comboBoxProtocol;

    delete labelBaudRate;
    delete comboBoxBaudRate;

    delete labelPort;
    delete comboBoxPort;
    delete pushButtonScan;

    delete labelFile;
    delete lineEditFile;
    delete pushButtonFile;

    delete pushButtonDownload;
    delete pushButtonStop;
    delete pushButtonClose;

    delete textBrowserSTCFlash;

    delete hBoxLayoutProtocolBaud;
    delete hBoxLayoutBottomButtons;
    delete gridLayoutMain;
}

void Widget::doDownload()
{
    QString cmd = QString("./stcflash/stcflash.exe")
            + " --port "     + comboBoxPort    ->currentText().split(' ')[0]
            + " --lowbaud "  + comboBoxBaudRate->currentText()
            + " --protocol " + comboBoxProtocol->currentText()
            + " "            + lineEditFile    ->text();
    processSTCFalsh->start(cmd, QProcess::ReadWrite);
}

void Widget::doReadSTCFlash()
{
    textBrowserSTCFlash->append(processSTCFalsh->readAll());
}

void Widget::doStopProcess()
{
    processSTCFalsh->terminate();
    textBrowserSTCFlash->append(tr("Downloading stoped..."));
}

void Widget::enablePushButtonStop()
{
    pushButtonStop->setEnabled(true);

    pushButtonScan->setEnabled(false);
    pushButtonFile->setEnabled(false);
    pushButtonDownload->setEnabled(false);
    pushButtonClose->setEnabled(false);
}

void Widget::disablePushButtonStop()
{
    pushButtonStop->setEnabled(false);

    pushButtonScan->setEnabled(true);
    pushButtonFile->setEnabled(true);
    pushButtonDownload->setEnabled(true);
    pushButtonClose->setEnabled(true);
}
