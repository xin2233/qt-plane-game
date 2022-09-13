#ifndef ENEMY_H
#define ENEMY_H
#include <QPixmap>
#include <QTimer>

class enemy
{
public:
    enemy();
    void choice();
    void bomb();
    QPixmap plane;
    int x,y,health;
    QTimer bmt[6];
    void init();
};

#endif // ENEMY_H
