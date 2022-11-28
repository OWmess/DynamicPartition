#include "BindDialog.h"
#include "ui_BindDialog.h"

BindDialog::BindDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::BindDialog)
{
    _ui->setupUi(this);
}

BindDialog::~BindDialog()
{
    delete _ui;
}

BindDialog::BindDialog(OS *os, QWidget *parent):BindDialog(parent) {
    this->_os=os;
}
