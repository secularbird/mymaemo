#ifndef MMM_FONTDIALOG_H
#define MMM_FONTDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QListWidget>


class mmm_fontDialog : public QDialog
{
    Q_OBJECT
public:
    mmm_fontDialog();
    void setDefaultFont(QFont &font);
    const QFont &getFont() const;

signals:
    void fontChanged(QFont &font);

protected:
    void closeEvent ( QCloseEvent * e ) ;


private slots:
    void updateFontStyle();
    void updateFontsize();
    void updateFont();

private:
    QListWidget *fontFamilyList;
    QListWidget *fontStyleList;
    QListWidget *fontSizeList;

    QString fontFamily;
    QString fontStyle;
    int fontPointSize;
    QFont mFont;
};

#endif // MMM_FONTDIALOG_H
