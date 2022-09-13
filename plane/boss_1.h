#ifndef BOSS_1_H
#define BOSS_1_H
#include <QPixmap>
#include <QTimer>
#include <QProgressBar>
#include <QLabel>

class Boss_1
{
public:
    Boss_1();
    QPixmap plane;
    int x,y,health;
    QTimer tm,t,warn;
    bool is,die_is;
    QPixmap fire;
    double fire_x[5],fire_y[5];
    double getx[5],a[5],b[5];
    double findx(int ,int ,int);
    void init();
    QTimer firet,diet;
    QPixmap bombs[10];
    int bx[10],by[10];
    void bomb(int);
    QTimer bmt[6];
    QProgressBar health_display;
};

#endif // BOSS_1_H
