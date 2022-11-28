#include "BindDialog.h"
#include "ui_BindDialog.h"

BindDialog::BindDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::BindDialog)
{
    _ui->setupUi(this);
    connect(_ui->firstFitButton, &QPushButton::clicked, this, &BindDialog::firstFitSlot);
    connect(_ui->nextFitButton, &QPushButton::clicked, this, &BindDialog::nextFitSlot);
    connect(_ui->bestFitButton, &QPushButton::clicked, this, &BindDialog::bestFitSlot);
    connect(_ui->worstFitButton, &QPushButton::clicked, this, &BindDialog::worstFitSlot);
    connect(_ui->quickFitButton, &QPushButton::clicked, this, &BindDialog::quickFitSlot);
}

BindDialog::~BindDialog()
{
    delete _ui;
}

BindDialog::BindDialog(OS *os, QWidget *parent):BindDialog(parent) {
    this->_os=os;
}

void BindDialog::firstFitSlot() {
    this->close();
}

void BindDialog::nextFitSlot() {
    this->close();
}

void BindDialog::bestFitSlot() {
    this->close();
}

void BindDialog::worstFitSlot() {
    this->close();
}

void BindDialog::quickFitSlot() {
    this->close();
}

