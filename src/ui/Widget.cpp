#include "Widget.h"
#include "./ui_Widget.h"
#include "InitDialog.h"
#include "BindDialog.h"
#include "FreeDialog.h"
#include <QPainter>
#include <QLabel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , _ui(new Ui::Widget)
{
    _ui->setupUi(this);
    connect(_ui->initButton, &QPushButton::clicked, this, &Widget::initDialog);
    connect(_ui->freeButton, &QPushButton::clicked, this, &Widget::freeDialog);
    connect(_ui->bindButton, &QPushButton::clicked, this, &Widget::bindDialog);

}

Widget::Widget(OS *os, QWidget *parent) :Widget(parent){
    _os=os;
}

Widget::~Widget()
{
    delete _ui;
}

void Widget::initDialog() {
    exec(new InitDialog(_os,this));
}

void Widget::bindDialog() {
    exec(new BindDialog(_os,this));
}

void Widget::freeDialog() {
    exec(new FreeDialog(_os,this));
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    const int w=1024;
    const int h=300;
    const int x=70;
    const int y=100;

    const QPoint tl={x, y};
    const QPoint br={x + w, y + h};

    painter.fillRect(QRect{tl, br}, QBrush(Qt::green));
    for(const auto free:_os->getFree()){
        painter.fillRect(QRect{QPoint{x+free._begin,y},QSize{free._size+1,h+1}},QBrush(Qt::darkGray));
    }


    auto drawNumber=[](int num,int pos,QWidget *parent){
        auto *label0=new QLabel(parent);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label0->setText(QString::number(num));
        label0->setGeometry(QRect{x-20+pos,y-50,50,45});
        label0->setFont(font);
        label0->show();

    };

    drawNumber(0,0,this);
    painter.drawRect(QRect{tl, br});
    for(int i=1;i<=10;i++) {
        drawNumber(i*100,i*100,this);
        painter.drawLine(QPoint(x + 100 * i, y), QPoint(x + 100 * i, y + h));
    }
    drawNumber(1023,1050,this);


}





