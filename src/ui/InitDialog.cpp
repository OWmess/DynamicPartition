#include "InitDialog.h"
#include "ui_InitDialog.h"
#include <QDebug>
#include "ErrorMessage.h"

InitDialog::InitDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::InitDialog) {
    _ui->setupUi(this);
    connect(_ui->buttonBox, &QDialogButtonBox::accepted, this, &InitDialog::acceptSlot);
}

InitDialog::~InitDialog() {
    delete _ui;
}

InitDialog::InitDialog(OS *os, QWidget *parent) : InitDialog(parent) {
    _os = os;
}

void InitDialog::acceptSlot() {
    int start = _ui->startEdit->text().toInt();
    int end = _ui->endEdit->text().toInt();
    if (!_os->createPartition(start, end)) {
        ErrorMessage::msg("输入的作业地址有误", this);
    }
}
