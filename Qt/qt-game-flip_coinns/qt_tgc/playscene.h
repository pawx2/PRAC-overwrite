#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelNum);
    //成员 记录所选关卡
    int levelIndex;
    //成员 维护每关数据
    int gameArray[4][4];
    MyCoin* coins[4][4];

    //是否胜利的标志
    bool isWin;

    //重写paintEvent事件
    void paintEvent(QPaintEvent*);

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
