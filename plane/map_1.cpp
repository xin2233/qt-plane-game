#include "map_1.h"
#include "ui_map_1.h"
#include <QDebug>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QRandomGenerator>

Map_1::Map_1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map_1)
{
    ui->setupUi(this);
    health_display = new QProgressBar(this);
    health_display->setMaximum(boss.health);
    health_display->setMinimum(0);
    health_display->setValue(boss.health);
    health_display->resize(400,15);
    health_display->move((500 -  400)/2, 20);
    health_display->setStyleSheet("QProgressBar{color:rgb(255,255,255);}"
                                      "QProgressBar::chunk{background-color:rgb(255,10,10);}");
    health_display->hide();
    boss.health_display.setParent(this);
    boss.health_display.hide();
    boss.health_display.setMaximum(boss.health);
    boss.health_display.setValue(boss.health);
    boss.health_display.setMinimum(0);
    boss.health_display.resize(400,15);
    boss.health_display.move((500 -  400)/2, 20);
    boss.health_display.setStyleSheet("QProgressBar{color:rgb(255,255,255);}"
                                      "QProgressBar::chunk{background-color:rgb(255,10,10);}");
    win.setPixmap(QPixmap(":/image/win.png"));
    win.setParent(this);
    win.setScaledContents(true);
    win.resize(360,200);
    win.move((width()-360)/2.0,300);
    win.hide();
    a=1;
    is = true;
    isis = 0;
    dieis = 0;
    score = 0;
    setMaximumSize(500,700);
    setMinimumSize(500,700);
    map1.load(":/image/back_1.jpg");
    map1 = map1.scaled(500, 700);
    map2.load(":/image/back_1.jpg");
    map2 = map2.scaled(500, 700);
    ui->score->move(0,0);
    ui->score->resize(80,20);
    ui->score->setText(QString("得分:%1").arg(score));
    ui->score->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    ui->score->setFont(QFont("Timers" , 15 , 0));

    ui->left->move(100-50,500);
    ui->left->resize(80,80);
    ui->left->setStyleSheet("QPushButton{border-image:url(:/image/left.png);border-style:outset;background-color:transparent;}");

    ui->right->move(width()-100-80+50,500);
    ui->right->resize(80,80);
    ui->right->setStyleSheet("QPushButton{border-image:url(:/image/right.png);border-style:outset;background-color:transparent;}");

    ui->st->resize(200,80);
    ui->st->move((width()-200)/2,height()/2-40);
    ui->st->setStyleSheet("QPushButton{border-image:url(:/image/lk.png);border-style:outset;background-color:transparent;}");

    connect(ui->left,&QPushButton::clicked,[=]()
    {
        a++;
        QString str = ":/image/mineplane_";
        if(a==4)a=1;
        mine.plane.load(str.append(QString("%1.png").arg(a)));
        mine.plane = mine.plane.scaled(100,80);
    });
    connect(ui->right,&QPushButton::clicked,[=]()
    {
        a--;
        QString str = ":/image/mineplane_";
        if(a==0)a=3;
        mine.plane.load(str.append(QString("%1.png").arg(a)));
        mine.plane = mine.plane.scaled(100,80);
    });
    mapt.start(10);
    map1_x = 0;
    map2_x = 0;
    map1_y = 0;
    map2_y = 699;
    connect(&mapt,&QTimer::timeout,[=]()
    {
        map1_y++;map2_y++;
        if(map1_y >= 699)
            map1_y = -699;
        if(map2_y >= 699)
            map2_y = -699;
        update();
    });
    firet .start(100);
    connect(&firet,&QTimer::timeout,[=]()
    {
        static int n = 0;
        if(n>=100)n=0;
        mine.fire_x[n] = mine.x;
        mine.fire_y[n] = mine.y;
        mine.fire_x[++n] = mine.x+100-40;
        mine.fire_y[n++] = mine.y;
    });

    connect(&enemyt,&QTimer::timeout,[=]()
    {
        static int m = 0;
        if(m>=20) m = 0;
        int x = getRandom(0,400);
        enemy_plane[m].choice();
        enemy_plane[m].health = 10;
        enemy_plane[m].x = x;
        enemy_plane[m++].y = -80;
    });
    connect(ui->st,&QPushButton::clicked,[=]()
    {
        int time = 20;
        enemyt.start(300);
        boss.tm.start(1000 * time);
        boss.warn.start(1000 * time - 1000 * 3);
        ui->right->hide();
        ui->left->hide();
        ui->st->hide();

        is =
                false;
    });

    connect(&boss.tm,&QTimer::timeout,[=]()
    {
        boss.t.start(1);
        warn->hide();
        health_display->show();
        boss.is = 1;
        enemyt.start(1500);
        boss.warn.stop();
        boss.firet.start(1500);
        boss.tm.stop();
    });
    connect(&boss.firet,&QTimer::timeout,[=]()
    {
        int f = 20;
        static int l = 0;
        if(l>=5) l = 0;
        double x = mine.x + 50;
        double y = mine.y + 80;
        boss.fire_x[l] = 250;
        boss.fire_y[l] = 300-f;
        if(250 - x == 0 || 300-f - y == 0)
        {
            if(mine.x<width()/2) boss.a[l] = -4;
            else boss.a[l] = 4;
        }
        else boss.a[l] = (300-f - y)/(250 - x);
        boss.b[l] = 300-f - 250 * boss.a[l];
        boss.firet.start(650);
        l++;
    });
    connect(&boss.t,&QTimer::timeout,[=]()
    {
        boss.y++;
        if(boss.y>=0) boss.t.stop();
    });
    warn = new QLabel(this);
    connect(&boss.warn,&QTimer::timeout,[=]()
    {
       QMovie *movie = new QMovie(":/gif/warn.gif");
       warn->move(0,100);
       warn->resize(500,100);
       warn->setScaledContents(true);
       warn->show();
       movie->start();
       warn->setMovie(movie);
    });

    connect(&diet,&QTimer::timeout,[=]()
    {
        Init();
    });

    /*for(int g = 0;g<10;g++)
        connect(boss_bombt+g,&QTimer::timeout,[=]()
        {
            boss.bomb(g);
            switch (g) {case 0: boss.bx[g] = 100,boss.by[g] = 0; break;
            case 1: boss.bx[g] = 200,boss.by[g] = 0;break;
                case 2: boss.bx[g] = 150,boss.by[g] = 100;break;
                case 3: boss.bx[g] = 250,boss.by[g] = 150;break;
                case 4: boss.bx[g] = 400,boss.by[g] = 200;break;
                case 5: boss.bx[g] = 300,boss.by[g] = 170;break;
                case 6: boss.bx[g] = 0,boss.by[g] = 150;break;
                case 7: boss.bx[g] = 250,boss.by[g] = 170;break;
                case 8: boss.bx[g] = 400,boss.by[g] = 50;break;
                case 9: boss.bx[g] = 100,boss.by[g] = 200;break;
            }

        });*/
    connect(&bd,&QTimer::timeout,[=]()
    {
        /*for(int sd = 0;sd<10;sd++)
        {
            boss.by[sd]-=1;
        }*/
        boss.y -= 1;
    });
}
void Map_1::paintEvent(QPaintEvent *e)
{
    QPainter* p = new QPainter(this);
    p->drawPixmap(map1_x,map1_y,map1);
    p->drawPixmap(map2_x,map2_y,map2);
    if(mine.x <=0) mine.x = 0;
    if(mine.x >= 400)mine.x = 400;
    if(mine.y <=0) mine.y = 0;
    if(mine.y >= 620)mine.y = 620;
    p->drawPixmap(mine.x,mine.y,mine.plane);

    if(is == 0)
    {
        p->drawPixmap(boss.x,boss.y,boss.plane);
        //for(int bb = 0;bb<10;bb++)
            //p->drawPixmap(boss.bx[bb],boss.by[bb],boss.bombs[bb]);

        if(boss.is == 1)
        {
            for(int v = 0;v<100;v++)
            {
                if(mine.fire_y[v]<=boss.y + 300 - 50&&mine.fire_y[v]>100
                        &&mine.fire_x[v]>=0&&mine.fire_x[v]<=width())
                {
                    boss.health -= 1;
                    if(boss.health > 0)
                        health_display->setValue(boss.health);
                    mine.fire_y[v] = -150;
                    if(boss.health <= 0)
                    {
                        win.show();
                        /*boss_bombt[0].start(500);
                        boss_bombt[1].start(500);
                        boss_bombt[2].start(500);
                        boss_bombt[3].start(500);
                        boss_bombt[4].start(500);
                        boss_bombt[5].start(500);
                        boss_bombt[6].start(500);
                        boss_bombt[7].start(500);
                        boss_bombt[8].start(500);
                        boss_bombt[9].start(500);*/
                        win.move((width()-360)/2.0,300);
                        boss.is = 0;
                        for(int p1 = 0;p1<20;p1++)
                        {
                            enemy_plane[p1].bomb();
                        }
                        for(int bf = 0;bf<5;bf++)
                        {
                            boss.fire_y[bf] = -100.0;
                        }
                        enemyt.stop();
                        boss.health_display.hide();
                        bd.start(2);
                        break;
                    }
                }
            }
            if(mine.y<boss.y+300-30&&dieis == 0)
            {
                    isis = 1;
                    firet.stop();
                    mine.bomb();
                    diet.start(1 * 1000);
                    dieis = 1;
            }
            for(int i = 0;i<5;i++)
            {
                if(boss.fire_y[i]>=0&&boss.fire_y[i]<=750)
                {
                    p->drawPixmap(boss.fire_x[i],boss.fire_y[i],boss.fire);
                    boss.fire_y[i]+=3;
                    boss.fire_x[i] = boss.findx(i,boss.fire_y[i],mine.x);
                }
                if(mine.x<boss.fire_x[i]+25&&mine.x+100>boss.fire_x[i]
                        &&mine.y<boss.fire_y[i]+25&&mine.y+80>boss.fire_y[i]&&dieis == 0)
                {
                    int c = 2;
                    if((boss.fire_x[i]+25-c<mine.x+45&&(boss.fire_y[i]+25-c<mine.y+35||boss.fire_y[i]>mine.y+45-c))
                            ||(boss.fire_x[i]>mine.x+55-c&&(boss.fire_y[i]+25-c<mine.y+35||boss.fire_y[i]>mine.y+45-c))
                            );
                    else
                    {
                        isis = 1;
                        firet.stop();
                        mine.bomb();
                        diet.start(1 * 1000);
                        dieis = 1;
                    }
                }
            }
        }
        for(int aa=0;aa<100;aa++)
        {
            p->drawPixmap(mine.fire_x[aa],mine.fire_y[aa],mine.fire[aa]);
            mine.fire_y[aa]-=5;
        }
        for(int aa = 0;aa<20;aa++)
        {
            int s = 5;
            p->drawPixmap(enemy_plane[aa].x,enemy_plane[aa].y,enemy_plane[aa].plane);
            if(enemy_plane[aa].x<mine.x+100 - s&&enemy_plane[aa].x+100>mine.x + s
                    &&enemy_plane[aa].y+80 - s>mine.y&&enemy_plane[aa].y<mine.y+80 - s
                    &&dieis == 0&&enemy_plane[aa].health>0)
            {
                int c = 10;
                if((enemy_plane[aa].x+100-c<mine.x+45&&(enemy_plane[aa].y+80-c<mine.y+35||enemy_plane[aa].y>mine.y+45-c))
                        ||(enemy_plane[aa].x>mine.x+55-c&&(enemy_plane[aa].y+80-c<mine.y+35||enemy_plane[aa].y>mine.y+45-c))
                        );
                else{
                    qDebug()<<"die";
                    isis = 1;
                    diet.start(1 * 1000);
                    firet.stop();
                    mine.bomb();
                    enemy_plane[aa].bomb();
                    dieis = 1;
                }
            }

            for(int bb = 0;bb<100;bb++)
            {
                int c = 10;
                if(mine.fire_x[bb]<enemy_plane[aa].x+100-c&&mine.fire_x[bb]+40-c>enemy_plane[aa].x
                        &&mine.fire_y[bb]+50>enemy_plane[aa].y&&mine.fire_y[bb]+30<enemy_plane[aa].y+80
                        &&enemy_plane[aa].y>=0&&enemy_plane[aa].health>0)
                {
                    mine.fire_y[bb] = -150;
                    enemy_plane[aa].health--;
                    if(enemy_plane[aa].health<=0)
                    {
                        enemy_plane[aa].bomb();
                        ui->score->setText(QString("得分:%1").arg(++score));
                    }
                }
            }
            if(enemy_plane[aa].y >= -80)
                enemy_plane[aa].y += 2;
        }
    }
    p->end();
}
void Map_1::mouseMoveEvent(QMouseEvent *e)
{
    if(is == 0 && isis == 0)
    {
        mine.x = e->x()-50;
        mine.y = e->y()-40;
    }
}
int Map_1::getRandom(int min,int max)
{
//    QTime time= QTime::currentTime();
//    qsrand(time.msec()+time.second()*1000);
//    int num = rand()%max;
    // 弃用
    int num = QRandomGenerator::global()->bounded(0, max);
    if(num>=min)
    {
        return num;
    }
    else return getRandom(min,max);
}
void Map_1::Init()
{
    boss.init();
    boss.health_display.hide();
    for(int h = 0;h<20;h++)
    {
        enemy_plane[h].init();
    }
    mine.init();
    a=1;
    is = true;
    isis = 0;
    dieis = 0;
    score = 0;
    ui->score->setText(QString("得分:%1").arg(score));
    ui->left->show();
    ui->st->show();
    ui->right->show();
    enemyt.stop();
    diet.stop();
    firet .start(100);
    warn->hide();
    win.resize(360,200);
    win.move((width()-360)/2.0,300);
    win.hide();
    health_display->setMaximum(boss.health);
    health_display->setMinimum(0);
    health_display->setValue(boss.health);
    health_display->resize(400,15);
    health_display->hide();
    health_display->move((500 -  400)/2, 20);
}
Map_1::~Map_1()
{
    delete ui;
}
