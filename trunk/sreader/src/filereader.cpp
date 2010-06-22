#include "filereader.h"
#include <QtGui/QFontMetrics>

#include <QtCore/QDebug>


fileReader* fileReader::filereader = NULL;

fileReader::fileReader()
{
	file = new QFile;
	in = new QTextStream;
	area = QSize(800,480);

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
	//read all file content line by line
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

const QStringList &fileReader::getShowContentList(const QFont &font)
{
	//avoid invaild curindex
	if((curIndex > filecontent.size())
		||(curIndex < 0))
	{
		curIndex = 0;
	}
	lastIndex = curIndex;

	contentlist.clear();
	curIndex = readFrom(lastIndex, contentlist, font);

	return contentlist;
}

const QStringList &fileReader::getCurShowContentList(const QFont &font)
{
	//to avoid invaild lastIndex
	if((lastIndex > filecontent.size())
		||(lastIndex < 0 ))
	{
		lastIndex = 0;
	}
	contentlist.clear();
	curIndex = readFrom(lastIndex, contentlist, font);

	return contentlist;
}

const int fileReader::readFrom(const int start, QStringList &conlist, const QFont &font)
{
	QFontMetrics fontmetrics(font);
	int rowMax = area.height() / fontmetrics.height();
	int colWidth = area.width();

	qDebug()<<area.height()<<"\t"<<area.width();
	qDebug()<<fontmetrics.height();
	qDebug()<<rowMax;

	int i = 0;
	int bufSize = filecontent.size();
	int currentrow = 0 ;
	int colSize = 0 ;
	int linestart = start;
	for(i=start; i<bufSize; ++i)
	{
		if(currentrow >= rowMax)
		{
			break;
		}
		if(filecontent[i] == '\n')
		{
			currentrow++;
			conlist.append(filecontent.mid(linestart,i-linestart+1));
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
				conlist.append(filecontent.mid(linestart,i-linestart+1));
				linestart = i+1;
				colSize = 0;
			}
		}
	}

	return linestart;
}


