#ifndef CHARACTERITEM_H
#define CHARACTERITEM_H

#include <QListWidgetItem>

class CharacterItem : public QListWidgetItem
{
    Q_OBJECT
public:
    explicit CharacterItem(QListWidget *parent = 0, int custom = 0);
    int customInt;
    
signals:
    
public slots:
    
};

#endif // CHARACTERITEM_H
