#include "mmm_fontdialog.h"
#include <QListWidget>
#include <QGridLayout>
#include <QFontDatabase>


mmm_fontDialog::mmm_fontDialog()
{
    QStringList fontFamily;
    QStringList fontStyle;
    QStringList fontSize;

    QListWidget *fontFamilyList = new QListWidget(this);
    QListWidget *fontStyleList = new QListWidget(this);
    QListWidget *fontSizeList = new QListWidget(this);

    QFontDatabase fontDatabase;
    fontFamily = fontDatabase.families();

    fontFamilyList->addItems(fontFamily);


    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(fontFamilyList,0,0);
    gridLayout->addWidget(fontStyleList,0,1);
    gridLayout->addWidget(fontSizeList,0,2);

    this->setLayout(gridLayout);

}
