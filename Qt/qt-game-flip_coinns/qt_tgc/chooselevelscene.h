#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>

#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    //重写绘图事件 制作背景
    void paintEvent(QPaintEvent*);
    //游戏场景对象指针
    PlayScene* play = nullptr;

signals:
    //自定义信号 主场景监听 用于返回主场景 返回信号
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
