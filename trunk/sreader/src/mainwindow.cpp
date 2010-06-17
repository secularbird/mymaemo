#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mmm_settingdialog.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QFont>
#include <QtGui/QFileDialog>
#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <QtCore/QSize>
#include <QtCore/QtGlobal>
#include <QtGui/QFontMetrics>

#include <QtCore/QDebug>
#include "mmm_configuremanager.h"

int MainWindow::bufferSize = 1024;

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mmm_configuremanager::instance()->init();
    QString filePath = mmm_configuremanager::instance()->getFilePath();

    this->setWindowTitle(tr("sreader"));
//   vScrollBar = ui->textBrowser->verticalScrollBar();
//    connect(vScrollBar,SIGNAL(valueChanged(int)), this, SLOT(scrollchanged(int)));
    lastPos = 0;
    QFont font = mmm_configuremanager::instance()->getFont();
    ui->textBrowser->setFont(font);
    qDebug()<<font.pointSize();
    ui->mainToolBar->hide();

}

MainWindow::~MainWindow()
{
    if (file.isOpen())
    {
        file.close();
    }
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
    {
    	qDebug()<<"open failed";
        return;
    }
    in = new QTextStream(&file);
    updatefile(file);

    QFileInfo fi(filePath);
    this->setWindowTitle(fi.baseName());
}


void MainWindow::updatefile(QFile &file)
{
//   QTextStream in(&file);

    contentBuffer.clear();
    contentBuffer = in->read(bufferSize);
    int realNum = getShowNum(contentBuffer);
    in->seek(lastPos);

    contentBuffer.clear();
    contentBuffer = in->read(realNum);
    ui->textBrowser->setPlainText(contentBuffer);
    lastPos = in->pos();
}

/*
void MainWindow::scrollchanged(int value)
{
    qDebug()<<"valuechange"<<value;

    int length =  vScrollBar->maximum() - vScrollBar->minimum() + vScrollBar->pageStep();
    qDebug()<<"lenght is "<<length;

    //  reach more than half
    //  and the file is not end
    if ((value > 0.7*length)
    &&!file.atEnd())
    {
        updatefile(file);
        vScrollBar->setValue(value);
        qDebug()<<"refresh";
    }
}
*/
void MainWindow::on_actionFont_Setting_triggered()
{
    mmm_settingDialog settingDialog;
    connect(&settingDialog, SIGNAL(fontChanged(QFont&)), this, SLOT(fontChanged(QFont&)));
    settingDialog.exec();
}

void MainWindow::fontChanged(QFont &font)
{
    ui->textBrowser->setFont(font);
    mmm_configuremanager::instance()->setFont(font);
}

void MainWindow::mousePressEvent (QMouseEvent * event)
{
	startPoint = event->globalPos();
	qDebug()<<"start....";
}

void MainWindow::mouseReleaseEvent (QMouseEvent * event)
{
	QPoint endPoint = event->globalPos();
	qDebug()<<startPoint.x();
	qDebug()<<endPoint.x();
	if(startPoint.x()- endPoint.x() > 10)
	{
		nextPage();
	}
	else if(endPoint.x() - startPoint.x() > 10)
	{
	//	prePage();
	}
}

void MainWindow::prePage()
{
	  if(!in->seek(lastPos)){
		  in->reset();
	  }
	  contentBuffer.clear();
	  contentBuffer = in->read(bufferSize);
	  int realNum = getShowNum(contentBuffer);
	  in->seek(lastPos);

	  contentBuffer.clear();
	  contentBuffer = in->read(realNum);
	  ui->textBrowser->setPlainText(contentBuffer);
	  lastPos = in->pos();
}

void MainWindow::nextPage()
{
    contentBuffer.clear();
    contentBuffer = in->read(bufferSize);

    qDebug()<<"buffer read"<<in->pos();
    int realNum = getShowNum(contentBuffer);
    in->seek(lastPos);
    qDebug()<<"revert"<<in->pos();

    contentBuffer.clear();
    contentBuffer = in->read(realNum);
    ui->textBrowser->setPlainText(contentBuffer);
    lastPos = in->pos();
}

int MainWindow::getShowNum(const QString &buffer)
{
	QFontMetrics fontmetrics(ui->textBrowser->font());
	int rowMax = ui->textBrowser->size().height() / fontmetrics.height();
	int colWidth = ui->textBrowser->size().width();
	qDebug()<<"size"<<ui->textBrowser->size().height()<<"/t"<<ui->textBrowser->size().width();
	qDebug()<<"raw max"<<rowMax;

	int bufSize = buffer.size();
	int currentrow = 0 ;
	int colSize = 0 ;
	int fontNum = 0;
	for(int i=0; i<bufSize; ++i)
	{
		if(currentrow >= rowMax)
		{
			break;
		}
		if(buffer[i] == '\n')
		{
			currentrow++;
			qDebug()<<"current row"<<currentrow;
			fontNum++;
			colSize = 0;
		}
		else{
			colSize += fontmetrics.width(buffer[i]);
			if (colSize <= colWidth){
				fontNum++;
				qDebug()<<buffer[i];
			}
			else{
				i--;
				currentrow++;
				qDebug()<<"current row"<<currentrow;
				colSize = 0;
			}
		}
	}
	qDebug()<<"real num"<<fontNum;
	return fontNum;
}
