#include "mypushbutton.h"
#include<QtDebug>
#include<QPropertyAnimation>
myPushButton::myPushButton(QString normalImg, QString pressImg)
{
    this->normalImg = normalImg;
    this->pressImg = pressImg;

    QPixmap pix;
    if(!pix.load(normalImg)) qDebug() << "开始按钮图片加载失败";
    else
    {
        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());
        //设置不规则图片样式 边框像素为0
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));

    }
}

void myPushButton::press_zoom()
{
    //创建动态对象 (特效施加对象，特效方式)
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //终止位置
    animation->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //设置缓和曲线 弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void myPushButton::release_zoom()
{
    //创建动态对象 (特效施加对象，特效方式)
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
    //终止位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置缓和曲线 弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void myPushButton::mousePressEvent(QMouseEvent* e)
{
    //传入按下图片不为空，点击时切换图片
    if(this->pressImg != "")
    {
        QPixmap pix;
        if(!pix.load(this->pressImg)) qDebug() << "开始按钮图片加载失败";
        else
        {
            //设置图片固定大小
            this->setFixedSize(pix.width(), pix.height());
            //设置不规则图片样式 边框像素为0
            this->setStyleSheet("QPushButton{border:0px;}");
            //设置图标
            this->setIcon(pix);
            //设置图标大小
            this->setIconSize(QSize(pix.width(), pix.height()));
        }
    }
    //让父类执行其它内容 动画特效等
    return QPushButton::mousePressEvent(e);
}
void myPushButton::mouseReleaseEvent(QMouseEvent* e)
{
    //传入按下图片不为空，点击时切换图片
    if(this->pressImg != "")
    {
        QPixmap pix;
        if(!pix.load(this->normalImg)) qDebug() << "开始按钮图片加载失败";
        else
        {
            //设置图片固定大小
            this->setFixedSize(pix.width(), pix.height());
            //设置不规则图片样式 边框像素为0
            this->setStyleSheet("QPushButton{border:0px;}");
            //设置图标
            this->setIcon(pix);
            //设置图标大小
            this->setIconSize(QSize(pix.width(), pix.height()));
        }
    }
    //让父类执行其它内容
    return QPushButton::mouseReleaseEvent(e);
}
