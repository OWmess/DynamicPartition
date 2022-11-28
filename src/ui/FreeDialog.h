#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

namespace Ui {
class FreeDialog;
}

class FreeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FreeDialog(QWidget *parent = nullptr);
    ~FreeDialog();

private:
    Ui::FreeDialog *ui;
};

#endif // MAINDIALOG_H
