#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include<QPushButton>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    //构造函数 正常图片显示路径 按下图片显示路径
    myPushButton(QString normalImg, QString pressImg = "");
    //按钮弹跳特效
    void press_zoom();
    void release_zoom();
    //成员 默认图片路径 按下图片路径
    QString normalImg;
    QString pressImg;
    //重写按钮 按下 和 释放 事件
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
