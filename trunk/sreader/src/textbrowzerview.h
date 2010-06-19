#ifndef TEXTBROWZERVIEW_H
#define TEXTBROWZERVIEW_H

#include <QtGui/QGraphicsView>
#include <QtCore/QStringList>
#include <QtGui/QFont>

class TextBrowzerView : public QWidget
{
    Q_OBJECT

public:
    TextBrowzerView(QWidget *parent = 0);
    ~TextBrowzerView();

    void setContent(const QStringList &content);
    void setFont(const QFont &font);
    const QFont &getFont() const;

protected:
	void paintEvent(QPaintEvent *);

private:
	QStringList showcontent;
	QFont font;
};

#endif // TEXTBROWZERVIEW_H
