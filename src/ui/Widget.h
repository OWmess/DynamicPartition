#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "../OS.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);

    Widget(OS *os, QWidget *parent = nullptr);

    ~Widget();

private:
    void paintEvent(QPaintEvent *) override;

    template<class Dialog>
    inline void exec(Dialog *dialog) {
        dialog->exec();
        this->update();
    }

private slots:

    void initDialog();

    void bindDialog();

    void freeDialog();

private:
    Ui::Widget *_ui;
    OS *_os;
};

#endif // WIDGET_H
