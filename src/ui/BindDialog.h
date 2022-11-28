#ifndef BINDDIALOG_H
#define BINDDIALOG_H

#include <QDialog>

namespace Ui {
class BindDialog;
}

class BindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BindDialog(QWidget *parent = nullptr);
    ~BindDialog();

private:
    Ui::BindDialog *ui;
};

#endif // BINDDIALOG_H
