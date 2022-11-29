#include "BindDialog.h"
#include "ui_BindDialog.h"
#include "ErrorMessage.h"

BindDialog::BindDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::BindDialog) {
    _ui->setupUi(this);
    connect(_ui->firstFitButton, &QPushButton::clicked, this, &BindDialog::firstFitSlot);
    connect(_ui->nextFitButton, &QPushButton::clicked, this, &BindDialog::nextFitSlot);
    connect(_ui->bestFitButton, &QPushButton::clicked, this, &BindDialog::bestFitSlot);
    connect(_ui->worstFitButton, &QPushButton::clicked, this, &BindDialog::worstFitSlot);
    connect(_ui->quickFitButton, &QPushButton::clicked, this, &BindDialog::quickFitSlot);
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

void BindDialog::quickFitSlot() {
    fitExec(QUICK_FIT);
}

void BindDialog::fitExec(ALGO mode) {
    int size = _ui->lineEdit->text().toInt();
    if (!_os->dividePartition(size, mode)) {
        ErrorMessage::msg("分配失败", this);
    }
    this->close();
}

