#include <QIntValidator>
#include "BindDialog.h"
#include "ui_BindDialog.h"
#include "../ErrorMessage.h"

BindDialog::BindDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::BindDialog) {
    _ui->setupUi(this);
    _ui->lineEdit->setValidator(new QIntValidator(_ui->lineEdit));
    connect(_ui->firstFitButton, &QPushButton::clicked, this, &BindDialog::firstFitSlot);
    connect(_ui->nextFitButton, &QPushButton::clicked, this, &BindDialog::nextFitSlot);
    connect(_ui->bestFitButton, &QPushButton::clicked, this, &BindDialog::bestFitSlot);
    connect(_ui->worstFitButton, &QPushButton::clicked, this, &BindDialog::worstFitSlot);

}

BindDialog::~BindDialog() {
    delete _ui;
}

BindDialog::BindDialog(OS *os, QWidget *parent) : BindDialog(parent) {
    this->_os = os;
}

void BindDialog::firstFitSlot() {
    fitExec(FIRST_FIT);
}

void BindDialog::nextFitSlot() {
    fitExec(NEXT_FIT);
}

void BindDialog::bestFitSlot() {
    fitExec(BEST_FIT);
}

void BindDialog::worstFitSlot() {
    fitExec(WORST_FIT);
}


void BindDialog::fitExec(ALGO mode) {
    int size = _ui->lineEdit->text().toInt();
    qDebug("input size :  %d \n",size);
    if(size==0){
        ErrorMessage::msg("最小值为1!", this);
    }
    if (!_os->dividePartition(size, mode)) {
        ErrorMessage::msg("分配失败", this);
    }
    this->close();
}

