#include "Widget.h"
#include "./ui_Widget.h"
#include "InitDialog.h"
#include "BindDialog.h"
#include "FreeDialog.h"
#include <QPainter>
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
    auto *dialog = new InitDialog(_os,this);
    exec(dialog);
}

void Widget::bindDialog() {
    auto *dialog=new BindDialog(_os,this);
    exec(dialog);
}

void Widget::freeDialog() {
    auto *dialog=new FreeDialog(_os,this);
    exec(dialog);
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    const int w=512;
    const int h=200;
    const int x=150;
    const int y=25;
    const int secy=2*y+h;
    painter.drawRect(x,y,w,h);
    painter.drawRect(x,secy,w,h);
    for(int i=1;i<=5;i++) {
        painter.drawLine(QPoint(x + 100 * i, y), QPoint(x + 100 * i, y + h));

        painter.drawLine(QPoint(x + 100 * i, secy), QPoint(x + 100 * i, secy + h));
    }

}





