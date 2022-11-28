#include "InitDialog.h"
#include "ui_InitDialog.h"

InitDialog::InitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitDialog)
{
    ui->setupUi(this);
}

InitDialog::~InitDialog()
{
    delete ui;
}
