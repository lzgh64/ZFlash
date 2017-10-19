#include "portcombobox.h"
#include <QSerialPortInfo>
#include <QMessageBox>
#include <cstdlib>

PortComboBox::PortComboBox(QWidget *parent):
    QComboBox(parent)
{
    doPortScan();
}

PortComboBox::~PortComboBox()
{
}

QString PortComboBox::getCurrentPortName() const
{
    return currentPortName;
}

/* 按下检测按钮执行，修改下拉栏内容 */
void PortComboBox::doPortScan()
{
    reset();

    int portNumber = 0;
    portInfoList = QSerialPortInfo::availablePorts();
    foreach (QSerialPortInfo portInfoTmp, portInfoList) {
        currentPortName = portInfoTmp.portName();
        bool ok;
        portNumber = portInfoTmp.portName().remove(0, 3).toInt(&ok, 10);
        if (!ok) {
            QMessageBox::critical(this, "Error", "An internal error occurred!",
                                  QMessageBox::Close);
            exit(EXIT_FAILURE);
        }
        this->setItemText(portNumber, currentPortName
                      + " (" + portInfoTmp.description() + ")");
    }
    setCurrentIndex(portNumber);
}

void PortComboBox::reset()
{
    clear();
    for (int i = 0; i < 32; i++) {
        addItem("COM" + QString::number(i));
    }
}
