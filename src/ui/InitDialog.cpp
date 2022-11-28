#include "InitDialog.h"
#include "ui_InitDialog.h"

InitDialog::InitDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::InitDialog)
{
    _ui->setupUi(this);


}



InitDialog::~InitDialog()
{
    delete _ui;
}

InitDialog::InitDialog(OS *os,QWidget *parent):InitDialog(parent) {
    _os=os;
}
