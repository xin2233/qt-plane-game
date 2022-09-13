#include "player.h"
#include <QObject>
#include <QMovie>

Player::Player()
{
    num = ":/image/mineplane_1.png";
    plane.load(num);
    plane = plane.scaled(100,80);
    x=500/2-100/2;
    y=500;
    for(int a = 0;a<100;a++)
    {
        fire[a].load(":/image/fire.png");
        fire[a] = fire[a].scaled(40,50);
        fire_x[a] = 500/2-20;
        fire_y[a] = -60;
    }

}
void Player::init()
{
    num = ":/image/mineplane_1.png";
    plane.load(num);
    plane = plane.scaled(100,80);
    x=500/2-100/2;
    y=500;
    for(int a = 0;a<100;a++)
    {
        fire[a].load(":/image/fire.png");
        fire[a] = fire[a].scaled(40,50);
        fire_x[a] = 500/2-20;
        fire_y[a] = -60;
    }
    for(int a = 0;a<6;a++)
    {
        bmt[a].stop();
    }
}
void Player::bomb()
{
    int t = 110;
    plane.load(":/image/bomb-1.png");
    bmt[0].start(t*1);
    bmt[1].start(t*2);
    bmt[2].start(t*3);
    bmt[3].start(t*4);
    bmt[4].start(t*5);
    bmt[5].start(t*6);
    for(int a = 0;a<6;a++)
    QObject::connect(bmt+a,&QTimer::timeout,[=]()
    {
        plane.load(QString(":/image/bomb-%1.png").arg(a+2));
        bmt[a].stop();
    });
}
