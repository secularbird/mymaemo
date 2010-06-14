#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mmm_fontdialog.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QFont>
#include <QtGui/QFileDialog>
#include <QtGui/QScrollBar>

#include <QtCore/QtGlobal>

#include <QtCore/QDebug>

int MainWindow::bufferSize = 10240;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("sreader"));
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
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"), QDir::homePath(), tr("Text Files (*.txt)"));
    if (file.isOpen())
    {
        contentBuffer.clear();
        file.close();
    }
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    updatefile(file);
    QFileInfo fi(filePath);
    this->setWindowTitle(fi.baseName());
}


void MainWindow::updatefile(QFile &file)
{
    QTextStream in(&file);

    contentBuffer += in.read(bufferSize);

    ui->textBrowser->setPlainText(contentBuffer);

}


void MainWindow::scrollchanged(int value)
{
    qDebug()<<"valuechange"<<value;

    QScrollBar *vScrollBar = ui->textBrowser->verticalScrollBar();
    int length =  vScrollBar->maximum() - vScrollBar->minimum() + vScrollBar->pageStep();
    qDebug()<<"lenght is "<<length;

    /*reach more than half
      and the file is not end*/
    if ((value > 0.7*length)
    &&!file.atEnd())
    {
        updatefile(file);
        vScrollBar->setValue(value);
        qDebug()<<"refresh";
    }
}

void MainWindow::on_actionFont_Setting_triggered()
{
    mmm_fontDialog fontDialog;
    connect(&fontDialog, SIGNAL(fontChanged(QFont&)), this, SLOT(fontChanged(QFont&)));
    fontDialog.exec();
}

void MainWindow::fontChanged(QFont &font)
{
    ui->textBrowser->setFont(font);
}
