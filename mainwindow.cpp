#include <QTreeWidgetItem>
#include <QtDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include<QStringList>

#include <iostream>

#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enums.h"
#include "twoinputdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Grab the menu actions and set the slots manually
    QAction* currentAction = this->findChild<QAction*>("actionExit");
    connect(currentAction, SIGNAL(activated()), this, SLOT(close()));

    currentAction = this->findChild<QAction*>("actionOpen_Group");
    connect(currentAction, SIGNAL(activated()), this, SLOT(openGroup()));

    currentAction = this->findChild<QAction*>("actionImport_Group");
    connect(currentAction, SIGNAL(activated()), this, SLOT(importGroup()));

    currentAction = this->findChild<QAction*>("actionSave_Group");
    connect(currentAction, SIGNAL(activated()), this, SLOT(saveGroup()));

    currentAction = this->findChild<QAction*>("actionNew_Group");
    connect(currentAction, SIGNAL(activated()), this, SLOT(newGroup()));

    currentAction = this->findChild<QAction*>("actionDice_Roll");
    connect(currentAction, SIGNAL(activated()), this, SLOT(genNumber()));

    currentAction = this->findChild<QAction*>("actionAdd_Mob");
    connect(currentAction, SIGNAL(activated()), this, SLOT(addMob()));

    currentAction = this->findChild<QAction*>("actionRemove_Mob");
    connect(currentAction, SIGNAL(activated()), this, SLOT(removeMob()));

    currentAction = this->findChild<QAction*>("actionAdd_Mob_Type");
    connect(currentAction, SIGNAL(activated()), this, SLOT(addMobType()));

    currentAction = this->findChild<QAction*>("actionAdd_Mob_to_DB");
    connect(currentAction, SIGNAL(activated()), this, SLOT(addMobToDB()));

    currentAction = this->findChild<QAction*>("actionRemove_Mob_from_DB");
    connect(currentAction, SIGNAL(activated()), this, SLOT(removeMobFromDB()));

    //The mob list
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    connect(tw, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(mobChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(tw, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(editMobLine(QTreeWidgetItem*, int)));

    //Push Buttons
    QPushButton* pb = this->findChild<QPushButton*>("randomButton");
    connect(pb, SIGNAL(pressed()), this, SLOT(genNumber()));

    //Handle the stats
    QSpinBox* sb = this->findChild<QSpinBox*>("dexIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeDex(int)));
    changeDex(1);

    sb = this->findChild<QSpinBox*>("strIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeStr(int)));
    changeStr(1);

    sb = this->findChild<QSpinBox*>("touIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeTou(int)));
    changeTou(1);

    sb = this->findChild<QSpinBox*>("perIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changePer(int)));
    changePer(1);

    sb = this->findChild<QSpinBox*>("wilIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeWil(int)));
    changeWil(1);

    sb = this->findChild<QSpinBox*>("chaIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeCha(int)));
    changeCha(1);

    sb = this->findChild<QSpinBox*>("karmaIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeKarma(int)));

    sb = this->findChild<QSpinBox*>("hpIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeHP(int)));

    sb = this->findChild<QSpinBox*>("woundIs");
    connect(sb, SIGNAL(valueChanged(int)), this, SLOT(changeWounds(int)));

    readMobDB(DBLocation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openGroup()
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    if(tw->topLevelItemCount() != 0)
        newGroup();
    importGroup();
}

void MainWindow::importGroup()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("XML files (*.xml)"));
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
         << ": " << qPrintable(file.errorString())
         << std::endl;
    }
    QXmlStreamReader xmlReader(&file);

    QTreeWidget* tlist = this->findChild<QTreeWidget*>("mobTree");
    std::vector<QTreeWidgetItem*> ti;

    while(!xmlReader.atEnd())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if(token == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "MOBS")
            {
               continue;
            }
            else if(xmlReader.name() == "MOB")
            {
                ti.push_back(new QTreeWidgetItem(tlist));
                ti.back()->setFlags(ti.back()->flags() | Qt::ItemIsEditable);
                continue;

            }
            else if(xmlReader.name() == "NAME")
            {
                QString name(xmlReader.readElementText());
                ti.back()->setData(0, NAME, name);
                ti.back()->setText(0, name);
            }
            else if(xmlReader.name() == "DEX")
            {
                ti.back()->setData(0, DEX, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "STR")
            {
                ti.back()->setData(0, STR, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "TOU")
            {
                ti.back()->setData(0, TOU, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "PER")
            {
                ti.back()->setData(0, PER, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "WIL")
            {
                ti.back()->setData(0, WIL, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "CHA")
            {
                ti.back()->setData(0, CHA, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "KARMA")
            {
                ti.back()->setData(0, KARMA, xmlReader.readElementText());
            }
            else if(xmlReader.name() == "HP")
            {
                int hp = xmlReader.readElementText().toInt();
                ti.back()->setData(0, HP, hp);
                ti.back()->setText(1, QString(std::to_string(hp).c_str()));
            }
            else if(xmlReader.name() == "WOUNDS")
            {
                ti.back()->setData(0, WOUNDS, xmlReader.readElementText());
            }
            else
            {
              xmlReader.raiseError(QObject::tr("Not a bookindex file"));
            }
        }
    }
    file.close();
    if (xmlReader.hasError())
    {
      std::cerr << "Error: Failed to parse file "
                << qPrintable(fileName) << ": "
                << qPrintable(xmlReader.errorString()) << std::endl;
    }
    else if (file.error() != QFile::NoError)
    {
      std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                << ": " << qPrintable(file.errorString())
                << std::endl;
    }

    //Go over all of the mobs read in the file and add them to the list
    for(auto m : ti)
    {
        tlist->addTopLevelItem(m);
    }
}

void MainWindow::saveGroup()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"),
                                                     "",
                                                     tr("XML files (*.xml)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("MOBS");

    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    int numItems = tw->topLevelItemCount();
    for(int i = 0; i < numItems; i++)
    {
        QString name(("MOB"));
        xmlWriter.writeStartElement(name);
        xmlWriter.writeTextElement("NAME", tw->topLevelItem(i)->data(0, NAME).toString());
        xmlWriter.writeTextElement("STR", tw->topLevelItem(i)->data(0, STR).toString());
        xmlWriter.writeTextElement("TOU", tw->topLevelItem(i)->data(0, TOU).toString());
        xmlWriter.writeTextElement("DEX", tw->topLevelItem(i)->data(0, DEX).toString());
        xmlWriter.writeTextElement("PER", tw->topLevelItem(i)->data(0, PER).toString());
        xmlWriter.writeTextElement("WIL", tw->topLevelItem(i)->data(0, WIL).toString());
        xmlWriter.writeTextElement("CHA", tw->topLevelItem(i)->data(0, CHA).toString());
        xmlWriter.writeTextElement("KARMA", tw->topLevelItem(i)->data(0, KARMA).toString());
        xmlWriter.writeTextElement("HP", tw->topLevelItem(i)->data(0, HP).toString());
        xmlWriter.writeTextElement("WOUNDS", tw->topLevelItem(i)->data(0, WOUNDS).toString());
        xmlWriter.writeEndElement();


        //qDebug() << tw->topLevelItem(i)->text(0);
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
    statusBar()->showMessage(tr("Group Saved"));
}

void MainWindow::newGroup()
{
    QMessageBox msgBox;
    msgBox.setText("All unsaved data will be lost.");
    msgBox.setInformativeText("Are you sure you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret == QMessageBox::Ok)
    {
        this->findChild<QTreeWidget*>("mobTree")->clear();
    }
}

void MainWindow::genNumber()
{
    QSpinBox* sb = this->findChild<QSpinBox*>("randomStep");
    QLineEdit* o = this->findChild<QLineEdit*>("randomNumber");
    int ranNum = rollStep(sb->value());

    QCheckBox* cb = this->findChild<QCheckBox*>("karmaCheck");
    if(cb->isChecked())
    {
        ranNum += rollDice(6);
    }

    o->setText(std::to_string(ranNum).c_str());
}

void MainWindow::changeDex(int newDex)
{
    int step = 0;

    //Physical Defense
    if(newDex < 2)
        step = 2;
    else if(newDex < 4)
        step = 3;
    else if(newDex < 7)
        step = 4;
    else if(newDex < 9)
        step = 5;
    else if(newDex < 11)
        step = 6;
    else if(newDex < 14)
        step = 7;
    else if(newDex < 16)
        step = 8;
    else if(newDex < 18)
        step = 9;
    else if(newDex < 21)
        step = 10;
    else if(newDex < 23)
        step = 11;
    else if(newDex < 25)
        step = 12;
    else if(newDex < 28)
        step = 13;
    else if(newDex < 30)
        step = 14;
    else if(newDex == 30)
        step = 15;

    QSpinBox* sb = this->findChild<QSpinBox*>("pDef");
    sb->setValue(step);

    //Initiative
    if(newDex < 4)
        step = 2;
    else if(newDex < 7)
        step = 3;
    else if(newDex < 10)
        step = 4;
    else if(newDex < 13)
        step = 5;
    else if(newDex < 16)
        step = 6;
    else if(newDex < 19)
        step = 7;
    else if(newDex < 22)
        step = 8;
    else if(newDex < 25)
        step = 9;
    else if(newDex < 28)
        step = 10;
    else if(newDex < 31)
        step = 11;

    sb = this->findChild<QSpinBox*>("initIs");
    sb->setValue(step);


    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
        ti->setData(0, DEX, this->findChild<QSpinBox*>("dexIs")->value());
}

void MainWindow::changeStr(int newStr)
{
    int step = 0;

    //Encumbrance
    for(int i = 1; i <= newStr; i++)
    {
        if(i < 7)
            step += 5;
        else if(i < 12)
            step += 10;
        else if(i < 16)
            step += 15;
        else if(i < 19)
            step += 20;
        else if(i < 22)
            step += 30;
        else if(i < 25)
            step += 40;
        else if(i < 28)
            step += 50;
        else if(i < 31)
            step += 60;
    }

    QSpinBox* sb = this->findChild<QSpinBox*>("encumIs");
    sb->setValue(step);

    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
        ti->setData(0, STR, this->findChild<QSpinBox*>("strIs")->value());
}

void MainWindow::changeTou(int newTou)
{
    int step = 18;
    for(int i = 1; i <= newTou; i++)
    {
        if(i%3 == 0)
            step += 2;
        else
            step += 1;
    }
    QSpinBox* sb = this->findChild<QSpinBox*>("deathIs");
    sb->setValue(step);

    step = 9;
    for(int i = 1; i <= newTou; i++)
    {
        if(i%3 == 0)
            step += 2;
        else
            step += 1;
        if(i == 11 || i == 21)
            step++;
    }
    sb = this->findChild<QSpinBox*>("unconIs");
    sb->setValue(step);

    step = 3;
    for(int i = 1; i <= newTou; i++)
    {
        if(i < 22)
        {
            if(i%2 == 0)
                step++;
        }
        else if(i == 23 || i == 25 || i == 28 || i == 30)
        {
            step++;
        }
    }
    sb = this->findChild<QSpinBox*>("woundThreshIs");
    sb->setValue(step);

    //set max hp to death threshold
    this->findChild<QSpinBox*>("hpIs")->setMaximum(this->findChild<QSpinBox*>("deathIs")->value());

    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
        ti->setData(0, TOU, this->findChild<QSpinBox*>("touIs")->value());
}

void MainWindow::changePer(int newPer)
{
    int step = 2;
    for(int i = 1; i <= newPer; i++)
    {
        if(i == 2)
            step++;
        else if(i == 4)
            step++;
        else if(i == 7)
            step++;
        else if(i == 9)
            step++;
        else if(i == 11)
            step++;
        else if(i == 14)
            step++;
        else if(i == 16)
            step++;
        else if(i == 18)
            step++;
        else if(i == 21)
            step++;
        else if(i == 23)
            step++;
        else if(i == 25)
            step++;
        else if(i == 28)
            step++;
        else if(i == 30)
            step++;
    }
    QSpinBox* sb = this->findChild<QSpinBox*>("spDef");
    sb->setValue(step);

    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
        ti->setData(0, PER, this->findChild<QSpinBox*>("perIs")->value());
}

void MainWindow::changeWil(int newWil)
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
        ti->setData(0, WIL, this->findChild<QSpinBox*>("wilIs")->value());

    //compiler warning and I can't remove it from the function
    if(false)
        qDebug() << newWil;
}

void MainWindow::changeCha(int newCha)
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
        ti->setData(0, CHA, this->findChild<QSpinBox*>("chaIs")->value());

    //compiler warning and I can't remove it from the function
    if(false)
        qDebug() << newCha;
}

void MainWindow::changeKarma(int newKarma)
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
    {
        ti->setData(0, KARMA, newKarma);
    }
}

void MainWindow::changeHP(int newHP)
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* ti = tw->currentItem();
    if(ti != nullptr)
    {
        QSpinBox* sb = this->findChild<QSpinBox*>("hpIs");
        newHP = (newHP>sb->maximum())?sb->maximum():newHP;
        sb->setValue(newHP);
        ti->setText(1, QString(std::to_string(newHP).c_str()));
        ti->setData(0, HP, newHP);
    }
}

void MainWindow::changeWounds(int newWounds)
{
    QTreeWidgetItem* item = this->findChild<QTreeWidget*>("mobTree")->currentItem();
    if(item != nullptr)
    {
        item->setData(0, WOUNDS, newWounds);
    }
}

void MainWindow::addMob()
{
    //qt doesn't like passing slots that have default arguments...
    this->addMob(nullptr);
}

void MainWindow::addMob(mob* mobType = nullptr)
{
    //Set up the mob viewing list
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");

    QTreeWidgetItem* titem = new QTreeWidgetItem(tw);

    QString name = (mobType==nullptr)?"New Mob":mobType->name;
    int dex = (mobType==nullptr)?1:mobType->dex;
    int str = (mobType==nullptr)?1:mobType->str;
    int tou = (mobType==nullptr)?1:mobType->tou;
    int per = (mobType==nullptr)?1:mobType->per;
    int wil = (mobType==nullptr)?1:mobType->wil;
    int cha = (mobType==nullptr)?1:mobType->cha;
    int karma = (mobType==nullptr)?0:mobType->karma;
    int hp = (mobType==nullptr)?1:mobType->hp;
    int wounds = (mobType==nullptr)?0:mobType->wounds;


    titem->setFlags(titem->flags() | Qt::ItemIsEditable);
    titem->setText(0, name);
    titem->setText(1, QString(std::to_string(hp).c_str()));
    titem->setData(0, NAME, "New Mob");
    titem->setData(0, DEX, dex);
    titem->setData(0, STR, str);
    titem->setData(0, TOU, tou);
    titem->setData(0, PER, per);
    titem->setData(0, WIL, wil);
    titem->setData(0, CHA, cha);
    titem->setData(0, KARMA, karma);
    titem->setData(0, HP, hp);
    titem->setData(0,WOUNDS, wounds);

    tw->addTopLevelItem(titem);


    tw->resizeColumnToContents(0);
    tw->resizeColumnToContents(1);
    tw->resizeColumnToContents(2);

}

void MainWindow::removeMob()
{
    //Set up the mob viewing list
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");

    QTreeWidgetItem* item = tw->currentItem();

    if(item != nullptr)
        delete item;

    tw->resizeColumnToContents(0);
    tw->resizeColumnToContents(1);
    tw->resizeColumnToContents(2);

}

void MainWindow::addMobType()
{
    bool ok = true;
    QString text;
    int numMobs;
    QStringList list;

    for(mob* mobType : mobTypeList)
    {
        list << mobType->name;
    }

    TwoInputDialog dialog(this, &text, &numMobs);


    dialog.fillComboBox(list);
    int ret = dialog.exec();
    if (ok)
        ok = !!ret;
    if (ret) {

    } else {
        text = QString();
    }

    if (ok && text != QString())
        for(mob* mobType : mobTypeList)
        {
            if(text == mobType->name)
            {
                for(int i = 0; i < numMobs; i++)
                {
                    addMob(mobType);
                }
                break;
            }
        }
}

void MainWindow::mobChanged(QTreeWidgetItem* newI, QTreeWidgetItem* oldI)
{
    //Set the spinbox values to the mob's values
    if(newI != nullptr)
    {
        this->findChild<QSpinBox*>("dexIs")->setValue(newI->data(0, DEX).toInt());
        this->findChild<QSpinBox*>("strIs")->setValue(newI->data(0, STR).toInt());
        this->findChild<QSpinBox*>("touIs")->setValue(newI->data(0, TOU).toInt());
        this->findChild<QSpinBox*>("perIs")->setValue(newI->data(0, PER).toInt());
        this->findChild<QSpinBox*>("wilIs")->setValue(newI->data(0, WIL).toInt());
        this->findChild<QSpinBox*>("chaIs")->setValue(newI->data(0, CHA).toInt());
        this->findChild<QSpinBox*>("karmaIs")->setValue(newI->data(0, KARMA).toInt());
        this->findChild<QSpinBox*>("hpIs")->setValue(newI->data(0, HP).toInt());
        this->findChild<QSpinBox*>("woundIs")->setValue(newI->data(0, WOUNDS).toInt());

        //set max hp to death threshold
        this->findChild<QSpinBox*>("hpIs")->setMaximum(this->findChild<QSpinBox*>("deathIs")->value());
    }

    //compiler warning and I can't remove it from the function
    if(false)
        qDebug() << oldI;
    //qDebug() << "mob changed";
}

void MainWindow::editMobLine(QTreeWidgetItem* item, int column)
{
    if(column == 0)
    {
        //change name
        item->setData(0, NAME, item->text(0));
    }
    else if(column == 1)
    {
        //set HP
        QSpinBox* sb = this->findChild<QSpinBox*>("hpIs");
        int maxValue = sb->maximum();
        bool validValue;
        int changedValue = item->text(1).toInt(&validValue);
        if(validValue)
        {
            //if the value is too high, reduce it to the max value
            changedValue = (changedValue>maxValue)?maxValue:changedValue;
            item->setText(1, QString(std::to_string(changedValue).c_str()));
            item->setData(0, HP, changedValue);

            //only change the spinbox if we're looking at the mob being changed
            if(this->findChild<QTreeWidget*>("mobTree")->currentItem() == item)
            {
                sb->setValue(changedValue);
            }
        }
        else
        {
            item->setText(1, item->data(0, HP).toString());
        }
    }
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    tw->resizeColumnToContents(0);
    tw->resizeColumnToContents(1);
    tw->resizeColumnToContents(2);
}

void MainWindow::readMobDB(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
         << ": " << qPrintable(file.errorString())
         << std::endl;
    }
    QXmlStreamReader xmlReader(&file);

    while(!xmlReader.atEnd())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        if(token == QXmlStreamReader::StartElement)
        {
            if(xmlReader.name() == "MOBTYPES")
            {
               continue;
            }
            else if(xmlReader.name() == "MOBTYPE")
            {
                mobTypeList.push_back(new mob());
                continue;

            }
            else if(xmlReader.name() == "NAME")
            {
                mobTypeList.back()->name = xmlReader.readElementText();
            }
            else if(xmlReader.name() == "DEX")
            {
                mobTypeList.back()->dex = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "STR")
            {
                mobTypeList.back()->str = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "TOU")
            {
                mobTypeList.back()->tou = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "PER")
            {
                mobTypeList.back()->per = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "WIL")
            {
                mobTypeList.back()->wil = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "CHA")
            {
                mobTypeList.back()->cha = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "KARMA")
            {
                mobTypeList.back()->karma = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "HP")
            {
                mobTypeList.back()->hp = xmlReader.readElementText().toInt();
            }
            else if(xmlReader.name() == "WOUNDS")
            {
                mobTypeList.back()->wounds = xmlReader.readElementText().toInt();
            }
            else
            {
              xmlReader.raiseError(QObject::tr("Not a bookindex file"));
            }
        }
    }
    file.close();
    if (xmlReader.hasError())
    {
      std::cerr << "Error: Failed to parse file "
                << qPrintable(fileName) << ": "
                << qPrintable(xmlReader.errorString()) << std::endl;
    }
    else if (file.error() != QFile::NoError)
    {
      std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                << ": " << qPrintable(file.errorString())
                << std::endl;
    }
}

void MainWindow::writeMobDB(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("MOBTYPES");

    for(mob* mobType : mobTypeList)
    {
        xmlWriter.writeStartElement("MOBTYPE");
        xmlWriter.writeTextElement("NAME", mobType->name);
        xmlWriter.writeTextElement("STR", QString(std::to_string(mobType->str).c_str()));
        xmlWriter.writeTextElement("TOU", QString(std::to_string(mobType->tou).c_str()));
        xmlWriter.writeTextElement("DEX", QString(std::to_string(mobType->dex).c_str()));
        xmlWriter.writeTextElement("PER", QString(std::to_string(mobType->per).c_str()));
        xmlWriter.writeTextElement("WIL", QString(std::to_string(mobType->wil).c_str()));
        xmlWriter.writeTextElement("CHA", QString(std::to_string(mobType->cha).c_str()));
        xmlWriter.writeTextElement("KARMA", QString(std::to_string(mobType->karma).c_str()));
        xmlWriter.writeTextElement("HP", QString(std::to_string(mobType->hp).c_str()));
        xmlWriter.writeTextElement("WOUNDS", QString(std::to_string(mobType->wounds).c_str()));
        xmlWriter.writeEndElement();
        //qDebug() << tw->topLevelItem(i)->text(0);
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    file.close();
    statusBar()->showMessage(tr("Mob DB Saved"));
}

void MainWindow::addMobToDB()
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* item = tw->currentItem();

    QString text(item->data(0, NAME).toString());
    bool unique = uniqueName(item->data(0, NAME).toString(), mobTypeList);
    while(!unique)
    {
        bool ok;
        text = QInputDialog::getText(this, tr("Pick a new name."),
                                          tr("Please chose a unique name:"), QLineEdit::Normal,
                                             "", &ok);
        if (ok && !text.isEmpty())
        {
            if(uniqueName(text, mobTypeList))
            {
                unique = true;
                item->setData(0, NAME, text);
                item->setText(0, text);
            }
        }
        else if(!ok)
        {
            return;
        }
    }

    mobTypeList.push_back(new mob());
    mobTypeList.back()->name = text;
    mobTypeList.back()->str = item->data(0, STR).toInt();
    mobTypeList.back()->tou = item->data(0, TOU).toInt();
    mobTypeList.back()->dex = item->data(0, DEX).toInt();
    mobTypeList.back()->per = item->data(0, PER).toInt();
    mobTypeList.back()->wil = item->data(0, WIL).toInt();
    mobTypeList.back()->cha = item->data(0, CHA).toInt();
    mobTypeList.back()->karma = item->data(0, KARMA).toInt();
    mobTypeList.back()->hp = item->data(0, HP).toInt();
    mobTypeList.back()->wounds = item->data(0, WOUNDS).toInt();

    writeMobDB(DBLocation);
}

void MainWindow::removeMobFromDB()
{
    QTreeWidget* tw = this->findChild<QTreeWidget*>("mobTree");
    QTreeWidgetItem* item = tw->currentItem();
    QString name = item->data(0, NAME).toString();

    QMessageBox msgBox;
    msgBox.setText("Erasing " + name);
    msgBox.setInformativeText("Are you sure you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if(ret != QMessageBox::Ok)
    {
        return;
    }

    auto element = mobTypeList.begin();
    for(auto iter = element; iter != mobTypeList.end(); iter++)
    {
        if((*iter)->name == name)
        {
            element = iter;
            break;
        }
    }
    mobTypeList.erase(element);

    writeMobDB(DBLocation);
}








