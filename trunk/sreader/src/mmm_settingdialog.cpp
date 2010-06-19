#include "mmm_settingdialog.h"
#include <QtGui/QGridLayout>
#include <QtGui/QFontDatabase>

#include <QtCore/QDebug>

mmm_settingDialog::mmm_settingDialog()
{
    QStringList fontFamily;

    fontFamilyList = new QListWidget(this);
    fontStyleList = new QListWidget(this);
    fontSizeList = new QListWidget(this);

    QFontDatabase fontDatabase;
    fontFamily = fontDatabase.families();

    fontFamilyList->addItems(fontFamily);

    connect(fontFamilyList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateFontStyle()));
    connect(fontStyleList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateFontsize()));
    connect(fontSizeList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(updateFont()));

    fontFamilyList->setMinimumWidth(400);

    QHBoxLayout *gridLayout = new QHBoxLayout(this);
    gridLayout->addWidget(fontFamilyList);
    gridLayout->addWidget(fontStyleList);
    gridLayout->addWidget(fontSizeList);

    this->setLayout(gridLayout);

}


void mmm_settingDialog::updateFontStyle()
{
    QList<QListWidgetItem *> itemList = fontFamilyList->selectedItems();
    fontFamily = itemList.first()->text();
    QStringList fontStyle;
    QFontDatabase fontDatabase;
    fontStyle = fontDatabase.styles(fontFamily);
    fontStyleList->clear();
    fontStyleList->addItems(fontStyle);
}

void mmm_settingDialog::updateFontsize()
{
    QList<QListWidgetItem *> styleitemList = fontStyleList->selectedItems();
    fontStyle = styleitemList.first()->text();
    QList<int> fontSize;
    QStringList fontSizeStringList;
    QFontDatabase fontDatabase;
    fontSize = fontDatabase.pointSizes(fontFamily,fontStyle);
    fontSizeList->clear();
    if(fontSize.isEmpty())
    {
        mFont.setFamily(fontFamily);
        return;
    }

    QString tmp;
    for (int i=0; i<fontSize.size(); i++)
    {
        fontSizeStringList.append(tmp.setNum(fontSize.at(i),10));
    }

    fontSizeList->addItems(fontSizeStringList);
}

void mmm_settingDialog::setDefaultFont(const QFont &font)
{
	QStringList fontfamily;
	int index=0;
	QFontDatabase fontDatabase;
	fontfamily = fontDatabase.families();
    mFont = font;
    //find the famliy
    index = fontfamily.indexOf(mFont.family());
    QListWidgetItem* item = fontFamilyList->item(index);
    if (NULL == item)
    {
    	return;
    }
    item->setSelected(true);

    //find the style
    //find the size
}


const QFont& mmm_settingDialog::getFont() const
{
    return mFont;
}

void mmm_settingDialog::updateFont()
{
    QList<QListWidgetItem *> sizeitemList = fontSizeList->selectedItems();
    bool ok = true;
    fontPointSize = sizeitemList.first()->text().toInt(&ok,10);
    QFontDatabase fontDatabase;
    mFont = fontDatabase.font(fontFamily, fontStyle, fontPointSize);
}

void mmm_settingDialog::closeEvent ( QCloseEvent * e )
{
    emit fontChanged(mFont);
    QDialog::closeEvent(e);
}
