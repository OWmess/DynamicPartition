#include <QIntValidator>
#include <QPainter>
#include <QStringListModel>
#include "QuickFitDialog.h"
#include "ui_QuickFitDialog.h"
#include "../ErrorMessage.h"
const int MAX_SIZE=1024;
QuickFitDialog::QuickFitDialog(QWidget *parent) :
        QDialog(parent),
        _ui(new Ui::QuickFitDialog)
{
    _ui->setupUi(this);
    _ui->lineEdit->setValidator(new QIntValidator(_ui->lineEdit));
    connect(_ui->bindButton, &QPushButton::clicked, this, &QuickFitDialog::bindSlot);
    connect(_ui->exitButton, &QPushButton::clicked, this, &QuickFitDialog::exitSlot);

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

    auto *label3=new QLabel(this);
    label3->setText("1");
    label3->setGeometry(QRect{_x-15, _y-35, 60, 30});
    label3->show();

    auto *label4=new QLabel(this);
    label4->setText("1023");
    label4->setGeometry(QRect{_x+_w-15, _y-35, 60, 30});
    label4->show();



}

QuickFitDialog::~QuickFitDialog()
{
    delete _os;
    delete _ui;
}

void QuickFitDialog::bindSlot() {
    int size = _ui->lineEdit->text().toInt();
    if(size>=MAX_SIZE||size<=0){
        ErrorMessage::msg("输入的值有误",this);
    }
    if(!_os->quickFit(size)){
        ErrorMessage::msg("没有足够空间分配作业",this);
    }
    _ui->lineEdit->clear();
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

    //填充绿色
    painter.fillRect(QRect{tl, br}, QBrush(Qt::green));

    //画线
    for(const auto& i:_os->getQFList()){
        for(const auto j:i.second){
            painter.drawLine(QPoint(_x + j._begin, _y), QPoint(_x + j._begin, _y + _h));
        }
//        painter.drawLine(QPoint(_x + bind._begin, _y), QPoint(_x + bind._begin, _y + _h));
    }
    //填充灰色
    for (const auto bind: _os->getBind()) {
        painter.fillRect(QRect{QPoint{_x + bind._begin, _y}, QSize{bind._size + 1, _h + 1}}, QBrush(Qt::darkGray));
    }

    _ui->freeView->reset();
    _ui->bindView->reset();
    QStringList freeList;
    QStringList bindList;
    //已分配作业显示
    int i=0;
    for(const auto bind:_os->getBind()){
        if(bind._begin==0&&bind._end==0)
            continue;
        QString str="作业 "+QString::number(i)+" :["+QString::number(bind._begin)+","+QString::number(bind._end)+"]";
        bindList.append(str);
        i++;
    }
    //空闲分区显示
    for(const auto& free:_os->getQFList()){
        QString str1=QString::number(free.first)+":";
        freeList.append(str1);

        for(const auto& item:free.second){
            if(item._begin==0&&item._end==0)
                continue;
            QString str2="["+QString::number(item._begin)+" , "+ QString::number(item._end) + "]";
            freeList.append(str2);
        }
        freeList.append("  ");
    }


    QStringListModel *freeListModel = new QStringListModel(freeList);
    _ui->freeView->setModel(freeListModel);
    QStringListModel *bindListModel = new QStringListModel(bindList);
    _ui->bindView->setModel(bindListModel);
}
