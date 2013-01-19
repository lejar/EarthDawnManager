#include <QComboBox>
#include <QSpinBox>
#include <QStringList>

#include "twoinputdialog.h"
#include "ui_twoinputdialog.h"


TwoInputDialog::TwoInputDialog(QWidget *parent, QString* comboString, int* spinInt) :
    QDialog(parent),
    ui(new Ui::TwoInputDialog)
{
    ui->setupUi(this);

    QDialogButtonBox* qb = this->findChild<QDialogButtonBox*>("buttonBox");
    connect(qb, SIGNAL(accepted()), this, SLOT(buttonPress()));

    this->comboString = comboString;
    this->spinInt = spinInt;

}

TwoInputDialog::~TwoInputDialog()
{
    delete ui;
}

void TwoInputDialog::buttonPress()
{
    QComboBox* cb = this->findChild<QComboBox*>("comboBox");
    QSpinBox* sb = this->findChild<QSpinBox*>("spinBox");

    *(this->comboString) = cb->currentText();
    *(this->spinInt) = sb->value();
}

void TwoInputDialog::fillComboBox(QStringList list)
{
    QComboBox* cb = this->findChild<QComboBox*>("comboBox");
    cb->addItems(list);
}
