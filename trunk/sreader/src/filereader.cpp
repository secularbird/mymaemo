#include "filereader.h"
#include <QtGui/QFontMetrics>


#include <QtCore/QDebug>


fileReader* fileReader::filereader = NULL;

fileReader::fileReader()
{
	file = new QFile;
	in = new QTextStream;
	area = QSize(800,480);
}

fileReader::~fileReader()
{
	delete file;
	delete in;
}

fileReader* fileReader::instance()
{
	if(NULL == filereader)
	{
		filereader = new fileReader();
	}
	return filereader;
}

bool fileReader::openFile(const QString &filePath)
{

	if (file->isOpen())
	{
		file->close();
	}
	file->setFileName(filePath);
	if (!file->open(QIODevice::ReadOnly))
	{
		qDebug()<<"open failed";
		return false;
	}

	in->setDevice(file);

	return true;

}

void fileReader::setShowArea(int height, int width)
{
	area.setHeight(height);
	area.setWidth(width);
}

qint64 fileReader::getShowNum(const QFont &font)
{
	qint64 curPos;
	qint64 lastPos;
	int i = 0;
	contentBuffer.clear();
	if(in->atEnd())
	{
		return 0;
	}

	lastPos = in->pos();
	QFontMetrics fontmetrics(font);
	int rowMax = area.height() / fontmetrics.height();
	int colWidth = area.width();

	qDebug()<<area.height()<<"\t"<<area.width();
	qDebug()<<fontmetrics.height();
	qDebug()<<rowMax;
/*
	for(i = 0; i< rowMax; ++i)
	{
		contentBuffer += in->readLine()+QString('\n');
	}
	qDebug()<<contentBuffer;
*/
	contentBuffer += in->read(1024);

	int bufSize = contentBuffer.size();
	int currentrow = 0 ;
	int colSize = 0 ;
	int fontNum = 0;
	for(i=0; i<bufSize; ++i)
	{
		if(currentrow >= rowMax)
		{
			break;
		}
		if(contentBuffer[i] == '\n')
		{
			currentrow++;
			qDebug()<<"current row"<<currentrow;
			fontNum++;
			colSize = 0;
		}
		else{
			colSize += fontmetrics.width(contentBuffer[i]);
			if (colSize <= colWidth){
				fontNum++;
				qDebug()<<contentBuffer[i];
			}
			else{
				i--;
				currentrow++;
				qDebug()<<"current row"<<currentrow;
				colSize = 0;
			}
		}
	}
	in->seek(lastPos);
	qDebug()<<"real num"<<fontNum;
	return fontNum;
}

QString & fileReader::getShowContent(const QFont &font)
{
	qint64 showNum = getShowNum(font);
	contentBuffer.clear();
	contentBuffer = in->read(showNum);
	return contentBuffer;
}



