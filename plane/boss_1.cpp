#include "boss_1.h"

Boss_1::Boss_1()
{
    plane.load(":/image/boss_1.png");
    plane = plane.scaled(500,300);
    fire.load(":/image/boss_fire.png");
    fire = fire.scaled(25,25);
    for(int c = 0;c<5;c++)
    {
        fire_x[c] = fire_y[c] = 900;
        a[c] = b[c] = 0;
    }
    x = 0;
    y = -800;
    is = 0;
    die_is = 0;
    health = 1000;
    health_display.setValue(health);
    health_display.setMaximum(health);
    health_display.setMinimum(0);
    for(int x = 0;x<10;x++)
    {
        bx[x] = by[x] = -100;
    }
}

void Boss_1::bomb(int n)
{
    int t = 80;
    bombs[n].load(":/image/bomb-1.png");
    bombs[n] = bombs[n].scaled(120,120);
    bmt[0].start(t*1);
    bmt[1].start(t*2);
    bmt[2].start(t*3);
    bmt[3].start(t*4);
    bmt[4].start(t*5);
    bmt[5].start(t*6);
    for(int a = 0;a<6;a++)
    QObject::connect(bmt+a,&QTimer::timeout,[=]()
    {
        bombs[n].load(QString(":/image/bomb-%1.png").arg(a+2));
        bmt[a].stop();
    });
}
void Boss_1::init()
{
    plane.load(":/image/boss_1.png");
    plane = plane.scaled(500,300);
    fire.load(":/image/boss_fire.png");
    fire = fire.scaled(25,25);
    for(int c = 0;c<5;c++)
    {
        fire_x[c] = fire_y[c] = 900;
        a[c] = b[c] = 0;
    }

    for(int x = 0;x<10;x++)
    {
        bx[x] = by[x] = -100;
    }
    x = 0;
    y = -800;
    is = 0;
    die_is = 0;
    health = 2000;
    health_display.setValue(health);
    health_display.setMaximum(health);
    health_display.setMinimum(0);
    tm.stop();
    t.stop();
    warn.stop();
    firet.stop();
    diet.stop();
}

double Boss_1::findx(int n, int y,int mine_x)
{
    if(a[n] == 0)
    {
        if(mine_x<250)
        return fire_x[n] - 5;
        else return fire_x[n] + 5;
    }
    else
    return (y - b[n])/a[n];
}
