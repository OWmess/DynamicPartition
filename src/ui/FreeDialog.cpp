#include "FreeDialog.h"
#include "ui_FreeDialog.h"

FreeDialog::FreeDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::FreeDialog)
{
    _ui->setupUi(this);
}

FreeDialog::~FreeDialog()
{
    delete _ui;
}

FreeDialog::FreeDialog(OS *os, QWidget *parent):FreeDialog(parent) {
    _os=os;
}
