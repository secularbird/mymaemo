#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QFileDialog>
#include <QScrollBar>


#include <QtGlobal>

#include <QDebug>

int MainWindow::bufferSize = 10240;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScrollBar *vScrollBar = ui->textBrowser->verticalScrollBar();
    connect(vScrollBar,SIGNAL(valueChanged(int)), this, SLOT(scrollchanged(int)));

    wordSpacing = 20;

    QFont sansFont("Helvetica [Cronyx]", 20);
    wordSpacing = sansFont.pointSize()+sansFont.wordSpacing();
    qDebug()<<"word space is "<<wordSpacing;
    ui->textBrowser->setFont(sansFont);
//    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->mainToolBar->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    /*open file dialog*/
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open txt file"), "/home/", tr("txt Files (*.txt)"));
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("text (*.txt)"));

    dialog.setViewMode(QFileDialog::List);

    file.setFileName(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    updatefile(file);
}


void MainWindow::updatefile(QFile &file)
{
    QTextStream in(&file);

    contentBuffer += in.read(bufferSize);

    ui->textBrowser->setPlainText(contentBuffer);

}


void MainWindow::scrollchanged(int value)
{
    Q_UNUSED(value);
    qDebug()<<"valuechange"<<value;

    QScrollBar *vScrollBar = ui->textBrowser->verticalScrollBar();
    int length =  vScrollBar->maximum() - vScrollBar->minimum() + vScrollBar->pageStep();
    qDebug()<<"lenght is "<<length;
    if (value > 0.5*length)
    {
        updatefile(file);
        vScrollBar->setValue(value);
        qDebug()<<"refresh";
    }
}
