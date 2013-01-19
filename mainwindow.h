#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTreeWidgetItem;
struct mob;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void readMobDB(QString);
    void writeMobDB(QString);


public slots:
   // void exitProgram();
    void openGroup();
    void importGroup();
    void saveGroup();
    void newGroup();

    void genNumber();
    void changeDex(int);
    void changeStr(int);
    void changeTou(int);
    void changePer(int);
    void changeWil(int);
    void changeCha(int);
    void changeKarma(int);
    void changeHP(int);
    void changeWounds(int);

    void addMob();
    void addMob(mob*);
    void removeMob();
    void addMobType();
    void mobChanged(QTreeWidgetItem*,QTreeWidgetItem*);
    void editMobLine(QTreeWidgetItem *, int);

    void addMobToDB();
    void removeMobFromDB();
    
private:
    Ui::MainWindow *ui;
    std::vector<mob*> mobTypeList;
    QString DBLocation = QString("mobs.xdb");

};

#endif // MAINWINDOW_H
