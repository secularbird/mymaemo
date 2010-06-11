#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    void updatefile(QFile &file);

    int wordSpacing;
    static int bufferSize;
    QString contentBuffer;
    QFile file;

private slots:
    void on_actionFont_Setting_triggered();
    void on_actionOpen_triggered();
    void scrollchanged(int value);
    void fontChanged(QFont &font);

};

#endif // MAINWINDOW_H
