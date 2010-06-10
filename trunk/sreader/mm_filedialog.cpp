#include "mm_filedialog.h"
#include <QDir>
#include <QTableView>

mm_filedialog::mm_filedialog(QWidget *parent) :
    QDialog(parent)
{
    QDir dir("/home");
    QTableView tabeView(this);
    tabeView.setModel(dir);
}
