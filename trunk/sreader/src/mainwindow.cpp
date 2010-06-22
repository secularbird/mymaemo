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

    textbrowzerview = new TextBrowzerView(this);

    ui->actionFont_Setting->setDisabled(true);

    mmm_configuremanager::instance()->init();
    QString filePath = mmm_configuremanager::instance()->getFilePath();

    this->setWindowTitle(tr("SReader"));

    connect(QApplication::desktop(), SIGNAL(resized(int)), this, SLOT(orientationChanged()));

    QFont font = mmm_configuremanager::instance()->getFont();
    textbrowzerview->setFont(font);
    this->setCentralWidget(textbrowzerview);

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
                                                    tr("Open file"), QDir::homePath(), tr("Text Files (*.[Tt][Xx][Tt])"));

    /* no file was read*/
    if (filePath.isEmpty())
    {
    	return;
    }
    fileReader::instance()->openFile(filePath);
    fileReader::instance()->setShowArea(textbrowzerview->geometry().height(),
    		textbrowzerview->geometry().width());
        qDebug()<<textbrowzerview->geometry().height()<<"\t"<<textbrowzerview->geometry().width();
    QString historypath = mmm_configuremanager::instance()->getFilePath();
    qDebug()<<historypath<<"\t"<<filePath;

    if(historypath == filePath)
    {
    	int pos = mmm_configuremanager::instance()->getFileStartPos();
    	fileReader::instance()->setStartPoint(pos);
    	updatefile();
    }
    else
    {
    	mmm_configuremanager::instance()->setFilePath(filePath);
    	mmm_configuremanager::instance()->setFileStartPos(0);

    	int pos = mmm_configuremanager::instance()->getFileStartPos();
    	fileReader::instance()->setStartPoint(pos);

    	nextPage();
    }

    QFileInfo fi(filePath);
    this->setWindowTitle(fi.baseName());
}


void MainWindow::updatefile()
{
	fileReader::instance()->setShowArea(textbrowzerview->height(),textbrowzerview->width());
	QStringList content = fileReader::instance()->getCurShowContentList(textbrowzerview->getFont());
	int pos = fileReader::instance()->getStartPoint();
	mmm_configuremanager::instance()->setFileStartPos(pos);
	if (content.isEmpty())
	{
		QStringList fileend;
		fileend.append(QString("File End"));
		textbrowzerview->setContent(fileend);
	}
	else
	{
		textbrowzerview->setContent(content);
	}
}

void MainWindow::on_actionFont_Setting_triggered()
{
/*
    mmm_settingDialog settingDialog;
    settingDialog.setDefaultFont(ui->textBrowser->font());
    connect(&settingDialog, SIGNAL(fontChanged(QFont&)), this, SLOT(fontChanged(QFont&)));
    settingDialog.exec();
*/
}

void MainWindow::fontChanged(QFont &font)
{
	if (!file.isOpen())
	{
		return;
	}

	textbrowzerview->setFont(font);
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

	}
}

void MainWindow::nextPage()
{
	fileReader::instance()->setShowArea(textbrowzerview->height(),textbrowzerview->width());
	QStringList content = fileReader::instance()->getShowContentList(textbrowzerview->getFont());
	int pos = fileReader::instance()->getStartPoint();
	mmm_configuremanager::instance()->setFileStartPos(pos);
	if (content.isEmpty())
	{
		QStringList fileend;
		fileend.append(QString("File End"));
		textbrowzerview->setContent(fileend);
	}
	else
	{
		textbrowzerview->setContent(content);
	}
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
