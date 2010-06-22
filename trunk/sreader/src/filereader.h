#ifndef MMM_FILEREADER_H
#define MMM_FILEREADER_H

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QSize>
#include <QtGui/QFont>
#include <QtCore/QStringList>

class fileReader:public QObject
{
	Q_OBJECT
public:
	static fileReader* instance();
	bool openFile(const QString &filePath);
	void setShowArea(int height, int width);
	void setStartPoint(int index);
	int getStartPoint();

	const QStringList &getShowContentList(const QFont &font);

	const QStringList &getCurShowContentList(const QFont &font);


private:
	fileReader();
	fileReader(const fileReader&);
	~fileReader();

	fileReader& operator =(const fileReader& );

	const int readFrom(const int start, QStringList &conlist, const QFont &font);

	static fileReader* filereader;

	QFile *file;
	QTextStream *in;
	QSize area;

	QStringList contentlist;

	QString filecontent;

	int lastIndex;
	int curIndex;
};


#endif
