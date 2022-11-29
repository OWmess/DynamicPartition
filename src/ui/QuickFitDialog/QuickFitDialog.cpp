#include <QIntValidator>
#include <QPainter>
#include "QuickFitDialog.h"
#include "ui_QuickFitDialog.h"

QuickFitDialog::QuickFitDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::QuickFitDialog)
{
    _ui->setupUi(this);
    _ui->lineEdit->setValidator(new QIntValidator(_ui->lineEdit));
    connect(_ui->bindButton, &QPushButton::clicked, this, &QuickFitDialog::bindSlot);
    connect(_ui->exitButton, &QPushButton::clicked, this, &QuickFitDialog::exitSlot);
    const int MAX_SIZE=1024;
    _os=new OS(MAX_SIZE);
    _os->quickFitInit();


    //图注
    auto *label1=new QLabel(this);
    label1->setText("未使用");
    label1->setGeometry(QRect{35, 10, 60, 30});
    label1->show();
    auto *label2=new QLabel(this);
    label2->setText("已使用");
    label2->setGeometry(QRect{135, 10, 60, 30});
    label2->show();
}

QuickFitDialog::~QuickFitDialog()
{
    delete _os;
    delete _ui;
}

void QuickFitDialog::bindSlot() {
    int size = _ui->lineEdit->text().toInt();
    _os->quickFit(size);
    this->update();
}

void QuickFitDialog::exitSlot() {
    this->close();
}

void QuickFitDialog::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    const QPoint tl = {_x, _y};
    const QPoint br = {_x + _w, _y + _h};

    //图注
    painter.fillRect(QRect{10, 10,20,20},QBrush(Qt::green));
    painter.fillRect(QRect{110, 10,20,20},QBrush(Qt::darkGray));

    //颜色填充
    painter.fillRect(QRect{tl, br}, QBrush(Qt::green));


    for(const auto& i:_os->getQFList()){
        for(const auto j:i.second){
            painter.drawLine(QPoint(_x + j._begin, _y), QPoint(_x + j._begin, _y + _h));
        }
//        painter.drawLine(QPoint(_x + bind._begin, _y), QPoint(_x + bind._begin, _y + _h));
    }


}
