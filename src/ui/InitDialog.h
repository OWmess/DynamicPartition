#ifndef INITDIALOG_H
#define INITDIALOG_H

#include <QDialog>
#include "../OS.h"
namespace Ui {
class InitDialog;
}

class InitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitDialog(QWidget *parent = nullptr);
    InitDialog(OS *os,QWidget *parent = nullptr);
    ~InitDialog();

private:
    Ui::InitDialog *_ui;
    OS *_os;
};

#endif // INITDIALOG_H
