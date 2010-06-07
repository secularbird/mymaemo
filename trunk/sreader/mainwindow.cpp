#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QFont>
#include <QFileDialog>

#include <QtGlobal>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wordSpacing = 20;

    QFont sansFont("Helvetica [Cronyx]", 20);
    wordSpacing = sansFont.weight()+sansFont.wordSpacing();
    ui->textBrowser->setFont(sansFont);
    ui->textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

    updatefile(fileName);
}

void MainWindow::updatefile(QString &filePath)
{

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    QString pageContent ;
    QString pageBuffer;
    int charNum = ui->textBrowser->size().width() * ui->textBrowser->size().height()
                  / wordSpacing/ wordSpacing;
    int lineCharNum = ui->textBrowser->size().width()/wordSpacing;
    int lineNum = ui->textBrowser->size().height()/wordSpacing;
    int realLineNum=0;
    int charCount=0;
    pageContent = in.readAll();
//   pageBuffer = in.read(charNum);
/*    for (int i = 0; i<pageBuffer.length(); i++)
    {
        if(realLineNum == lineNum)
        {
            break;
        }
        if(pageBuffer[i] == '\n')
        {
            realLineNum ++;
            charCount = 0;
        }
        else {
            charCount ++;
            if (charCount == lineCharNum)
            {
                realLineNum++;
                charCount = 0;
            }
        }
        qDebug() <<"i \t"<< pageBuffer[i];
        pageContent.append(pageBuffer[i]);
    }
*/
    ui->textBrowser->setPlainText(pageContent);

}
