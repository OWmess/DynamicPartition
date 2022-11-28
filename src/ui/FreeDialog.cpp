#include "FreeDialog.h"
#include "ui_FreeDialog.h"

FreeDialog::FreeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FreeDialog)
{
    ui->setupUi(this);
}

FreeDialog::~FreeDialog()
{
    delete ui;
}
