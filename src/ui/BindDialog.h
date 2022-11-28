#ifndef BINDDIALOG_H
#define BINDDIALOG_H

#include <QDialog>
#include "../OS.h"
namespace Ui {
class BindDialog;
}

class BindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BindDialog(QWidget *parent = nullptr);
    BindDialog(OS *os,QWidget *parent = nullptr);

    ~BindDialog();
private:
    inline void fitExec(ALGO mode);
private slots:
    void firstFitSlot();

    void nextFitSlot();

    void bestFitSlot();

    void worstFitSlot();

    void quickFitSlot();

private:
    Ui::BindDialog *_ui;
    OS *_os;
};

#endif // BINDDIALOG_H
