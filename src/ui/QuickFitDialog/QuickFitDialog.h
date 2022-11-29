#ifndef QUICKFITDIALOG_H
#define QUICKFITDIALOG_H

#include <QDialog>
#include "../../OS.h"
namespace Ui {
class QuickFitDialog;
}

class QuickFitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuickFitDialog(QWidget *parent = nullptr);
    ~QuickFitDialog();
private:
    void paintEvent(QPaintEvent *) override;
private slots:
    void bindSlot();

    void exitSlot();
private:
    Ui::QuickFitDialog *_ui;
    OS *_os;
    const int _w = 1024;
    const int _h = 200;
    const int _x = 40;
    const int _y = 80;
};

#endif // QUICKFITDIALOG_H
