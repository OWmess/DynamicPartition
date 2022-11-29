#include "Widget.h"
#include "./ui_Widget.h"
#include "../InitDialog/InitDialog.h"
#include "../BindDialog/BindDialog.h"
#include "../FreeDialog/FreeDialog.h"
#include "../QuickFitDialog/QuickFitDialog.h"
#include <QPainter>
#include <QLabel>
#include <QListView>
#include <QStringListModel>

Widget::Widget(QWidget *parent)
        : QWidget(parent), _ui(new Ui::Widget) {
    _ui->setupUi(this);
    connect(_ui->initButton, &QPushButton::clicked, this, &Widget::initDialog);
    connect(_ui->freeButton, &QPushButton::clicked, this, &Widget::freeDialog);
    connect(_ui->bindButton, &QPushButton::clicked, this, &Widget::bindDialog);
    connect(_ui->quickFitButton, &QPushButton::clicked, this, &Widget::quickFitSlot);

    //图注
    auto *label1=new QLabel(this);
    label1->setText("未使用");
    label1->setGeometry(QRect{35, 10, 60, 30});
    label1->show();
    auto *label2=new QLabel(this);
    label2->setText("已使用");
    label2->setGeometry(QRect{135, 10, 60, 30});
    label2->show();

    //绘制数字刻度
    auto drawNumber = [this](int num, int pos, QWidget *parent) {
        auto *label0 = new QLabel(parent);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label0->setText(QString::number(num));
        label0->setGeometry(QRect{_x - 20 + pos, _y - 50, 50, 45});
        label0->setFont(font);
        label0->show();

    };
    drawNumber(1, 0, this);
    for (int i = 1; i <= 10; i++) {
        drawNumber(i * 100, i * 100, this);
    }
    drawNumber(1024, 1050, this);

}

Widget::Widget(OS *os, QWidget *parent) : Widget(parent) {
    _os = os;
}

Widget::~Widget() {
    delete _ui;
}

void Widget::initDialog() {
    exec(new InitDialog(_os, this));
}

void Widget::bindDialog() {
    exec(new BindDialog(_os, this));
}

void Widget::freeDialog() {
    exec(new FreeDialog(_os, this));
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    const QPoint tl = {_x, _y};
    const QPoint br = {_x + _w, _y + _h};

    //图注
    painter.fillRect(QRect{10, 10,20,20},QBrush(Qt::green));
    painter.fillRect(QRect{110, 10,20,20},QBrush(Qt::darkGray));

    //颜色填充
    painter.fillRect(QRect{tl, br}, QBrush(Qt::green));
    for (const auto bind: _os->getBind()) {
        painter.fillRect(QRect{QPoint{_x + bind._begin, _y}, QSize{bind._size + 1, _h + 1}}, QBrush(Qt::darkGray));
    }

    painter.drawRect(QRect{tl, br});
    for (int i = 1; i <= 10; i++) {
        painter.drawLine(QPoint(_x + 100 * i, _y), QPoint(_x + 100 * i, _y + _h));
    }

    //显示进程
    _ui->listView->reset();
    QStringList list;
    int i=0;
    for(const auto bind:_os->getBind()){
        if(bind._begin==0&&bind._end==0)
            continue;
        QString str="thread "+QString::number(i)+" :["+QString::number(bind._begin)+","+QString::number(bind._end)+"]";
        list.append(str);
        i++;
    }

//    for(const auto bind:_os->getFree()){
//        if(bind._begin==0&&bind._end==0)
//            continue;
//        QString str="test "+QString::number(i)+" ：["+QString::number(bind._begin)+","+QString::number(bind._end)+"]";
//        list.append(str);
//        i++;
//    }
    QStringListModel *listmodel = new QStringListModel(list);
    _ui->listView->setModel(listmodel);
}

void Widget::quickFitSlot() {
    QuickFitDialog *dialog = new QuickFitDialog(this);
    dialog->show();
}





