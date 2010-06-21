#include "filereader.h"
#include <QtGui/QFontMetrics>


#include <QtCore/QDebug>


fileReader* fileReader::filereader = NULL;

fileReader::fileReader()
{
	file = new QFile;
	in = new QTextStream;
	area = QSize(800,480);
//	curpos = 0;
	lastIndex = 0;
	curIndex = 0;
}

fileReader::~fileReader()
{
	delete in;
	if (file->isOpen())
	{
		file->close();
	}
	delete file;
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
		filecontent.clear();
		file->close();
	}
	file->setFileName(filePath);
	if (!file->open(QIODevice::ReadOnly))
	{
		qDebug()<<"open failed";
		return false;
	}

	in->setDevice(file);
	while(!in->atEnd())
	{
		filecontent += in->readLine()+"\n";
	}
	return true;

}

void fileReader::setShowArea(int height, int width)
{
	area.setHeight(height);
	area.setWidth(width);
}

void fileReader::setStartPoint(int index)
{
	lastIndex = index;
	curIndex = index;
}

int fileReader::getStartPoint()
{
	return lastIndex;
}

QStringList &fileReader::getShowContentList(const QFont &font)
{
	int i = 0;
	contentlist.clear();
	if(curIndex > filecontent.size())
	{
		return contentlist;
	}
	lastIndex = curIndex;
	QFontMetrics fontmetrics(font);
	int rowMax = area.height() / fontmetrics.height();
	int colWidth = area.width();

	qDebug()<<area.height()<<"\t"<<area.width();
	qDebug()<<fontmetrics.height();
	qDebug()<<rowMax;

	int bufSize = filecontent.size();
	int currentrow = 0 ;
	int colSize = 0 ;
	int linestart = curIndex;
	for(i=curIndex; i<bufSize; ++i)
	{
		if(currentrow >= rowMax)
		{
			break;
		}
		if(filecontent[i] == '\n')
		{
			currentrow++;
			contentlist.append(filecontent.mid(linestart,i-linestart+1));
			linestart = i+1;
			colSize = 0;
		}
		else{
			colSize += fontmetrics.width(filecontent[i]);
			if (colSize <= colWidth){

			}
			else{
				i--;
				currentrow++;
				contentlist.append(filecontent.mid(linestart,i-linestart+1));
				linestart = i+1;
				colSize = 0;
			}
		}
	}

	curIndex = linestart;
	return contentlist;
}

QStringList &fileReader::getCurShowContentList(const QFont &font)
{
	int i = 0;
	contentlist.clear();
	if(curIndex > filecontent.size())
	{
		return contentlist;
	}
	curIndex = lastIndex;

	QFontMetrics fontmetrics(font);
	int rowMax = area.height() / fontmetrics.height();
	int colWidth = area.width();

	qDebug()<<area.height()<<"\t"<<area.width();
	qDebug()<<fontmetrics.height();
	qDebug()<<rowMax;

	int bufSize = filecontent.size();
	int currentrow = 0 ;
	int colSize = 0 ;
	int linestart = curIndex;
	for(i=curIndex; i<bufSize; ++i)
	{
		if(currentrow >= rowMax)
		{
			break;
		}
		if(filecontent[i] == '\n')
		{
			currentrow++;
			contentlist.append(filecontent.mid(linestart,i-linestart+1));
			linestart = i+1;
			colSize = 0;
		}
		else{
			colSize += fontmetrics.width(filecontent[i]);
			if (colSize <= colWidth){

			}
			else{
				i--;
				currentrow++;
				contentlist.append(filecontent.mid(linestart,i-linestart+1));
				linestart = i+1;
				colSize = 0;
			}
		}
	}
	curIndex = linestart;
	return contentlist;
}



