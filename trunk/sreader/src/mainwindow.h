#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "textbrowzerview.h"

class QScrollBar;
class QTextStream;

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
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);

private:
    Ui::MainWindow *ui;

    void updatefile();
    void nextPage();

    static int bufferSize;
    QString contentBuffer;
    QTextStream *in;
    QFile file;
//    int lastPos;
//   QScrollBar *vScrollBar;
    QPoint startPoint;
    TextBrowzerView *textbrowzerview;

private slots:
    void on_actionFont_Setting_triggered();
    void on_actionOpen_triggered();
 //   void scrollchanged(int value);
    void fontChanged(QFont &font);
    void orientationChanged();
};

#endif // MAINWINDOW_H
