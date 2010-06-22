#include "jumptodialog.h"

JumpToDialog::JumpToDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::JumpToDialogClass)
{
	ui->setupUi(this);
	curValue = 0;
	maxValue = 0;
}

JumpToDialog::~JumpToDialog()
{
	delete ui;
}

void JumpToDialog::setMaxValue(int max)
{
	maxValue = max;
	ui->horizontalSlider->setRange(0, max);
	ui->spinBox->setRange(0,max);
}

void JumpToDialog::setCurValue(int cur)
{
	curValue = cur;
	ui->spinBox->setValue(cur);
}

void JumpToDialog::on_prepushButton_pressed()
{
	curValue = ui->spinBox->value();
	if(curValue-200 < 0)
	{
		curValue = 0;
	}
	else
	{
		curValue = curValue -200;
	}

	ui->spinBox->setValue(curValue);
}

void JumpToDialog::on_nextpushButton_pressed()
{
	curValue = ui->spinBox->value();
	if(curValue+200 > maxValue)
	{
		curValue = maxValue;
	}
	else
	{
		curValue = curValue + 200;
	}

	ui->spinBox->setValue(curValue);
}

void JumpToDialog::on_okpushButton_pressed()
{
	curValue = ui->spinBox->value();
	emit valueChanged(curValue);

	this->accept();
}
