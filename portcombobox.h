#ifndef PORTLABEL_H
#define PORTLABEL_H

#include <QSerialPortInfo>
#include <QComboBox>
#include <QList>
#include <QString>

class PortComboBox: public QComboBox
{
    Q_OBJECT

public:
    PortComboBox(QWidget *parent = 0);
    ~PortComboBox();

    QString getCurrentPortName() const;

public slots:
    void doPortScan();

private:
    void reset();

    QList<QSerialPortInfo> portInfoList;
    QString currentPortName;
};

#endif // PORTLABEL_H
