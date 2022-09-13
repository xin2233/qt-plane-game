#ifndef MAP_1_H
#define MAP_1_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QProgressBar>
#include "player.h"
#include "enemy.h"
#include "boss_1.h"

namespace Ui {
class Map_1;
}

class Map_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Map_1(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    int getRandom(int min,int max);
    void Init();
    ~Map_1();

private:
    Ui::Map_1 *ui;
    QPixmap map1,map2;
    Player mine;
    int map1_x,map1_y,map2_x,map2_y;
    enemy enemy_plane[20];
    QTimer enemyt;
    int a;
    QTimer firet;
    bool is,isis,dieis;
    QTimer mapt;
    qint64 score;
    Boss_1 boss;
    QLabel *warn,win;
    QTimer diet,boss_bombt[10],bd;
    QProgressBar *health_display;
};

#endif // MAP_1_H
