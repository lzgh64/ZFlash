#ifndef FILELINEEDIT_H
#define FILELINEEDIT_H

#include <QWidget>
#include <QLineEdit>

class FileLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    FileLineEdit(QWidget *parent = 0);
    ~FileLineEdit();

public slots:
    void doSelectFile();
};

#endif // FILELINEEDIT_H
