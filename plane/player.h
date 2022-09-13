#ifndef PLAYER_H
#define PLAYER_H
#include <QPixmap>
#include <QTimer>
#include <QLabel>

class Player
{
public:
    Player();
    void bomb();
    int x,y;
    QPixmap plane;
    QString num;
    QPixmap fire[100];
    QTimer bmt[6];
    void init();
    int fire_x[100],fire_y[100];
};

#endif // PLAYER_H
