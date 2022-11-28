#include "Widget.h"
#include "./ui_Widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->initButton,&QPushButton::clicked,this,&Widget::initDialog);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initDialog() {
}

void Widget::bindDialog() {

}

void Widget::freeDialog() {

}

