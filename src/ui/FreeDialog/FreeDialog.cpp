#include <QIntValidator>
#include "FreeDialog.h"
#include "ui_FreeDialog.h"
#include "../ErrorMessage.h"
FreeDialog::FreeDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::FreeDialog) {
    _ui->setupUi(this);
    _ui->lineEdit->setValidator(new QIntValidator(_ui->lineEdit));
    connect(_ui->buttonBox, &QDialogButtonBox::accepted, this, &FreeDialog::acceptSlot);
}

FreeDialog::~FreeDialog() {
    delete _ui;
}

FreeDialog::FreeDialog(OS *os, QWidget *parent) : FreeDialog(parent) {
    _os = os;
}

void FreeDialog::acceptSlot() {
    int begin = _ui->lineEdit->text().toInt();
    if(!_os->mergePartition(begin)){
        ErrorMessage::msg("释放失败，请检查输入",this);
    }


}
