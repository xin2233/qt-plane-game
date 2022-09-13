#include "enemy.h"
#include <QTime>
#include <QRandomGenerator>

enemy::enemy()
{
    plane.load(":/image/enemy_1.png");
    plane = plane.scaled(100,80);
    x = 100;
    y =-150;
    health = 50;
}

void enemy::choice()
{
    int n;
    do{
//        warning: 'void qsrand(uint)' is deprecated: use QRandomGenerator instead [-Wdeprecated-declarations],
        //先通过 qsrand 设置seed， seed 是初始值，例如 seed 是5 ，qsrand（5），那么，调用qrand()生成的随数为5-RAND_MAX之间
        // rand_max == 32767，然后通过qrand生成数据，通过qrand%5，取模操作，这样得到0-5的随机数。
        // 目前通过QRandomGenerator 来进行生成，
//        QTime time= QTime::currentTime();
//
//        qsrand(time.msec()+time.second()*1000);
//        n = qrand()%5;

        n = QRandomGenerator::global()->bounded(0, 5);	//生成一个0和5之间的整数

    }while(n<=0||n>4);

    plane.load(QString(":/image/enemy_%1.png").arg(n));
}
void enemy::init()
{
    plane.load(":/image/enemy_1.png");
    plane = plane.scaled(100,80);
    x = 100;
    y =-150;
    health = 50;
    for(int a = 0;a<6;a++)
    {
        bmt[a].stop();
    }
}
void enemy::bomb()
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
