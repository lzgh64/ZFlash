#include "filelineedit.h"

#include <QFileDialog>

FileLineEdit::FileLineEdit(QWidget *parent)
    : QLineEdit(parent)
{

}

FileLineEdit::~FileLineEdit()
{

}

void FileLineEdit::doSelectFile()
{
    setText(QFileDialog::getOpenFileName(this, tr("Select File"), ".",
                                         "Intel Hex/Binary (*.hex; *.bin);;"
                                            "All Files (*)"));
}
