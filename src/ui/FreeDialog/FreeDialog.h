#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "../../OS.h"

namespace Ui {
    class FreeDialog;
}

class FreeDialog : public QDialog {
Q_OBJECT

public:
    explicit FreeDialog(QWidget *parent = nullptr);

    FreeDialog(OS *os, QWidget *parent = nullptr);

    ~FreeDialog();
private slots:
    void acceptSlot();
private:
    Ui::FreeDialog *_ui;
    OS *_os;
};

#endif // MAINDIALOG_H
