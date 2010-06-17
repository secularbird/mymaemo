#include <QtCore/QSettings>
#include <QtGui/QFont>


class mmm_configuremanager :public QSettings
{
	Q_OBJECT
public:
	static mmm_configuremanager* instance();

	void init();

	void restore();

	QString getFilePath();

	QFont getFont();

	void setFont(const QFont &font);
	void setFilePath(const QString &filepath);

private:
	mmm_configuremanager();
	~mmm_configuremanager();

	QSettings *setting;

};
