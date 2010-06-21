#include "mmm_configuremanager.h"
#include <QtCore/QFile>
#include <QtGui/QFontDatabase>
#include <QtCore/QDir>

mmm_configuremanager::mmm_configuremanager()
:setting(new QSettings())
{

}

mmm_configuremanager::~mmm_configuremanager()
{
	delete setting;
}

mmm_configuremanager* mmm_configuremanager::instance()
{
	static mmm_configuremanager cm;
	return &cm;
}

void mmm_configuremanager::init()
{
	//if configure file not exist
	QFile file(QDir::homePath()+"/.config/secularbird/sreader.conf");
	if(!file.exists()) {
		//then restore
		restore();
	}
	else {
		if(setting != NULL)
		{
			delete setting;
		}
		setting = new QSettings();
		setting->setPath(QSettings::NativeFormat,QSettings::UserScope,"$HOME/.config");
	}
}

void mmm_configuremanager::restore()
{
	if (setting != NULL)
	{
		delete setting;
	}
	setting = new QSettings();
	setting->setPath(QSettings::NativeFormat,QSettings::UserScope,"$HOME/.config");
	setting->beginGroup("mainwindow");
	setting->setValue("fullScreen", 1);
	setting->endGroup();

	setting->beginGroup("Font");
	setting->setValue("family", "Helvetica [Cronyx]");
	setting->setValue("style", "Normal");
	setting->setValue("size", 18);
	setting->endGroup();

	setting->beginGroup("File");
	setting->setValue("filepath", QDir::homePath());
	setting->setValue("startpostion", 0);
	setting->endGroup();
}

QString mmm_configuremanager::getFilePath()
{
	if (setting == NULL){
		init();
	}
	QString filePath = setting->value("File/filepath").toString();

	return filePath;
}

void mmm_configuremanager::setFilePath(const QString &filePath)
{
	if(setting == NULL){
		init();
	}
	setting->setValue("File/filepath",filePath);
}

QFont mmm_configuremanager::getFont()
{
	if (setting == NULL){
		init();
	}
	QString fontFamily = setting->value("Font/family").toString();
	QString fontStyle = setting->value("Font/style").toString();
	int fontSize = setting->value("Font/size").toInt();
	QFontDatabase fontDatabase;
	QFont font = fontDatabase.font(fontFamily, fontStyle, fontSize);

	return font;
}

void mmm_configuremanager::setFont(const QFont &font)
{
	if (setting == NULL){
		init();
	}

	setting->setValue("Font/family",font.family());
	setting->setValue("Font/style", font.style());
	setting->setValue("Font/size", font.pointSize());

}

void mmm_configuremanager::setFileStartPos(int pos)
{
	if (setting == NULL){
			init();
	}
	setting->setValue("File/startpostion",pos);
}

int mmm_configuremanager::getFileStartPos()
{
	return setting->value("File/startpostion").toInt();
}
