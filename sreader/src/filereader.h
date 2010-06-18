#ifndef MMM_FILEREADER_H
#define MMM_FILEREADER_H

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QSize>
#include <QtGui/QFont>


class fileReader:public QObject
{
	Q_OBJECT
public:
	static fileReader* instance();
	bool openFile(const QString &filePath);
	void setShowArea(int height, int width);

	QString &getShowContent(const QFont &font);

private:
	fileReader();
	fileReader(const fileReader&);
	~fileReader();

	fileReader& operator =(const fileReader& );

	qint64 getShowNum(const QFont &font);

	static fileReader* filereader;
	QFile *file;
	QTextStream *in;
	QSize area;
	QString contentBuffer;
};


#endif
