#ifndef TWOINPUTDIALOG_H
#define TWOINPUTDIALOG_H

#include <QDialog>

namespace Ui {
class TwoInputDialog;
}

class TwoInputDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit TwoInputDialog(QWidget *parent = 0, QString* comboString=0, int* spinInt=0);
    ~TwoInputDialog();

    void fillComboBox(QStringList);

signals:
    void returnResults(QString, int);
    
public slots:
    void buttonPress();

private:
    Ui::TwoInputDialog *ui;
    QString* comboString;
    int* spinInt;
};

#endif // TWOINPUTDIALOG_H
