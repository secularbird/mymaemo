#ifndef MMM_SETTINGDIALOG_H
#define MMM_SETTINGDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QListWidget>


class mmm_settingDialog : public QDialog
{
    Q_OBJECT
public:
    mmm_settingDialog();
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

#endif // mmm_settingDialog_H
