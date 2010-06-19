#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mmm_settingdialog.h"
#include "filereader.h"

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QFont>
#include <QtGui/QFileDialog>
#include <QtGui/QScrollBar>
#include <QtGui/QMouseEvent>
#include <QtCore/QSize>
#include <QtCore/QtGlobal>
#include <QtGui/QFontMetrics>

#include <QtGui/QDesktopWidget>


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
    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(orientationChanged()));

    lastPos = 0;
    QFont font = mmm_configuremanager::instance()->getFont();
    ui->textBrowser->setFont(font);
    qDebug()<<font.pointSize();

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

    fileReader::instance()->openFile(filePath);
    fileReader::instance()->setShowArea(ui->textBrowser->geometry().height(),
        		ui->textBrowser->geometry().width());
        qDebug()<<ui->textBrowser->geometry().height()<<"\t"<<ui->textBrowser->geometry().width();
    nextPage();

    QFileInfo fi(filePath);
    this->setWindowTitle(fi.baseName());
}


void MainWindow::updatefile()
{
	QString content = fileReader::instance()->getCurShowContent(ui->textBrowser->font());
    ui->textBrowser->setPlainText(content);
}

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

    updatefile();
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

}

void MainWindow::nextPage()
{
	QString content = fileReader::instance()->getShowContent(ui->textBrowser->font());
    ui->textBrowser->setPlainText(content);
}

void MainWindow::orientationChanged()
{
	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	if (screenGeometry.width() > screenGeometry.height())
	{
		updatefile();
	}
	else
	{
		updatefile();
	}
}
