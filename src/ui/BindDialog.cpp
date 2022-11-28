#include "BindDialog.h"
#include "ui_BindDialog.h"

BindDialog::BindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BindDialog)
{
    ui->setupUi(this);
}

BindDialog::~BindDialog()
{
    delete ui;
}
