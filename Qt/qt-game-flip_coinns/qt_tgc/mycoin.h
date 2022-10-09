#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QPushButton>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //参数代表 传入金币路径/硬币路径
    MyCoin(QString btnImg);

    //改变标志
    void changeFlag();

    //重写鼠标事件，快速连点不打断动画
    void mousePressEvent(QMouseEvent* e);

    //成员 金币属性
    int posX;   //x坐标位置
    int posY;   //y坐标位置
    bool flag;  //正反标识
    bool changable; //是否可翻转
    QTimer* timer;    //定时器
    int min = 1;
    int max = 8;
    //是否胜利的标志
    bool isWin;
signals:

};

#endif // MYCOIN_H
