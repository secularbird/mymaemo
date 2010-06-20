#include "textbrowzerview.h"
#include <QtGui/QFont>
#include <QtCore/QDebug>

TextBrowzerView::TextBrowzerView(QWidget *parent)
    : QWidget(parent)
{
	font.setFamily("Arial");
	font.setPointSize(18);
}

TextBrowzerView::~TextBrowzerView()
{

}


void TextBrowzerView::paintEvent(QPaintEvent *)
{
	QFontMetrics fontmetrics(font);
    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.setFont(font);
    int size = showcontent.size();
    qDebug()<<"start draw-----------------------------------------------------------";
    for(int i=0;i<size; i++)
    {
    	painter.drawText(0,i*fontmetrics.height(), this->width(), fontmetrics.height(),
    			Qt::AlignLeft,
    			showcontent.at(i));

    	qDebug()<<i*fontmetrics.height()<<"\t"<<this->width();
    	qDebug()<<showcontent.at(i);
    }
    qDebug()<<"end draw-----------------------------------------------------------";
}

void TextBrowzerView::setContent(const QStringList &content)
{
	showcontent = content;
	update();
}

void TextBrowzerView::setFont(const QFont &font)
{
	this->font = font;
}

const QFont& TextBrowzerView::getFont() const
{
	return font;
}

void TextBrowzerView::setArea(const QSize &area)
{
	this->area = area;
}
