#ifndef JUMPTODIALOG_H
#define JUMPTODIALOG_H

#include <QtGui/QDialog>
#include "ui_jumptodialog.h"

class JumpToDialog : public QDialog
{
    Q_OBJECT

public:
    JumpToDialog(QWidget *parent = 0);
    ~JumpToDialog();

    void setMaxValue(const int max);
    void setCurValue(const int cur);

signals:
	void valueChanged(int value);

private:
    Ui::JumpToDialogClass *ui;
    int curValue;
    int maxValue;

private slots:
    void on_prepushButton_pressed();
    void on_nextpushButton_pressed();
    void on_okpushButton_pressed();
};

#endif // JUMPTODIALOG_H
